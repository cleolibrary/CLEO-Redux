#include "AudioManagers.h"

#include <algorithm>
#include <cmath>
#include "Memory.h"

namespace audio::host
{
    namespace
    {
        float ReadMasterGain(uintptr_t address);
        std::optional<float> ReadAppliedVolume(uintptr_t device, size_t submixOffset);

        // 0 is a real value (the game is muted), so only a bad read falls back to 1.0.
        float ReadMasterGain(uintptr_t address)
        {
            const float gain = *At<float>(address);
            if (!std::isfinite(gain) || gain < 0.0f || gain > kUnrealAudioCurveMax) return 1.0f;

            return gain;
        }

        std::optional<float> ReadAppliedVolume(uintptr_t device, size_t submixOffset)
        {
            if (device == 0) return std::nullopt;

            const uintptr_t list = ReadPointer(device + submixOffset);
            if (list == 0) return std::nullopt;

            const auto count = *reinterpret_cast<const int32_t*>(list + kUnrealAudioSubmixCount);
            if (count <= 0 || count > kMaxSubmixEntries) return std::nullopt;

            const uintptr_t entries = ReadPointer(list + kUnrealAudioSubmixEntries);
            if (entries == 0) return std::nullopt;

            const float value = *At<float>(entries + kUnrealAudioSubmixValue);
            if (!std::isfinite(value) || value < 0.0f || value > kUnrealAudioCurveMax) return std::nullopt;

            return value;
        }
    } // namespace

    std::optional<AudioMix> AudioManager::GetVolume() const
    {
        float sfx   = 0.0f;
        float music = 0.0f;
        if (!ReadSliders(sfx, music)) return std::nullopt;

        AudioMix mix;
        mix.sfxVolume   = Shape(sfx, false);
        mix.musicVolume = Shape(music, true);
        return mix;
    }

    float AudioManager::GetTimeScale() const
    {
        const uintptr_t address = Addr(a.timeScale);
        if (address == 0) return 1.0f;

        const float scale = *At<float>(address);

        // Anything outside 0..10 is a bad read, not a game speed.
        if (!std::isfinite(scale) || scale < 0.0f || scale > 10.0f) return 1.0f;

        return scale;
    }

    float AudioManager::ApplyCurve(float value, float offset)
    {
        // 0, negative or NaN: the game's logf(0) is -inf, i.e. silence.
        if (!(value > 0.0f)) return 0.0f;

        const float input  = (std::min)(value, 1.0f);
        const float curved = std::pow(2.0f, std::log(input) * kUnrealAudioCurveExponent + offset);

        if (!std::isfinite(curved) || curved < 0.0f) return 0.0f;
        return (std::min)(curved, kUnrealAudioCurveMax);
    }

    float AudioManager::DetectCurveOffset(float value, std::optional<float> appliedVolume)
    {
        if (!appliedVolume || !(value > 0.0f)) return 0.0f;

        const float input    = (std::min)(value, 1.0f);
        const float exponent = std::log(input) * kUnrealAudioCurveExponent;
        const float offset   = std::log2(*appliedVolume) - exponent;

        if (!std::isfinite(offset)) return 0.0f;

        // Snapped to the nearest of the three the game can pick; anything else means
        // the submix read did not match this build, so no gain is used.
        static constexpr float kOffsets[] = {0.0f, -0.5f, 1.0f / 3.0f};

        float best      = 0.0f;
        float bestDelta = kUnrealAudioCurveOffsetTolerance;

        for (float candidate : kOffsets)
        {
            const float delta = std::fabs(offset - candidate);
            if (delta <= bestDelta)
            {
                best      = candidate;
                bestDelta = delta;
            }
        }

        return best;
    }

    bool ClassicAudio::ReadSliders(float& sfx, float& music) const
    {
        const uintptr_t sampleManager = Addr(a.sampleManager);
        if (sampleManager == 0) return false;

        const uint8_t sfxByte   = *At<uint8_t>(sampleManager + a.sfxOffset);
        const uint8_t musicByte = *At<uint8_t>(sampleManager + a.musicOffset);

        // 127 is the sample manager's maximum; a bigger byte means the offsets do
        // not match this build.
        if (sfxByte > 127 || musicByte > 127) return false;

        sfx   = static_cast<float>(sfxByte) / kSampleManagerVolumeScale;
        music = static_cast<float>(musicByte) / kSampleManagerVolumeScale;
        return true;
    }

    bool RemasterAudio::ReadSliders(float& sfx, float& music) const
    {
        const uintptr_t settings = Settings();
        if (settings == 0) return false;

        const float sfxPercent   = *At<float>(settings + kUnrealAudioSfxOffset);
        const float musicPercent = *At<float>(settings + kUnrealAudioMusicOffset);

        // A value outside 0..100 means the chain points somewhere else in this build.
        if (!std::isfinite(sfxPercent) || !std::isfinite(musicPercent)) return false;
        if (sfxPercent < 0.0f || sfxPercent > kUnrealMaxVolumePercent) return false;
        if (musicPercent < 0.0f || musicPercent > kUnrealMaxVolumePercent) return false;

        sfx   = sfxPercent * kUnrealAudioVolumeScale;
        music = musicPercent * kUnrealAudioVolumeScale;
        return true;
    }

    float RemasterAudio::Shape(float slider, bool music) const
    {
        const uintptr_t device = Device();

        // No audio device yet (front end, device switch)
        if (device == 0)
        {
            const float input = (std::min)(slider, 1.0f);
            return ApplyCurve(input, 0.0f);
        }

        const size_t gainOffset   = music ? kUnrealAudioMasterGainMusic : kUnrealAudioMasterGainSfx;
        const size_t submixOffset = music ? kUnrealAudioSubmixMusic : kUnrealAudioSubmixSfx;

        const float input = (std::min)(slider * ReadMasterGain(device + gainOffset), 1.0f);

        return ApplyCurve(input, DetectCurveOffset(input, ReadAppliedVolume(device, submixOffset)));
    }

    uintptr_t RemasterAudio::Device() const
    {
        const uintptr_t root = Addr(a.settingsRoot);
        if (root == 0) return 0;

        const uintptr_t engine = ReadPointer(root);
        if (engine == 0) return 0;

        return ReadPointer(engine + kUnrealAudioDeviceOffset);
    }

    uintptr_t RemasterAudio::Settings() const
    {
        const uintptr_t device = Device();
        return device == 0 ? 0 : ReadPointer(device + kUnrealAudioSettingsOffset);
    }
} // namespace audio::host
