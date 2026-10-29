#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

#include "HostTypes.h"

// Game speed and the in-game SFX/music sliders. The classic games keep two bytes
// in the SampleManager; the remasters keep percent floats in the audio settings
// object, behind the master gain and the curve documented below.

namespace audio::host
{
    // The remaster volume curve, taken from the game's own apply function:
    //
    //   x   = slider * 0.01 * device[+0xCC (sfx) / +0xD0 (music)]
    //   out = min(2^(ln(clamp(x, 0, 1)) * 1.4476483 + offset), 2)
    //
    // `offset` is the output-device correction: -0.5 for device types 0 and 1, +1/3
    // for type 2, 0 otherwise.

    inline constexpr size_t kUnrealAudioDeviceOffset    = 0x280;
    inline constexpr size_t kUnrealAudioSettingsOffset  = 0x28;
    inline constexpr size_t kUnrealAudioMusicOffset     = 0x248;
    inline constexpr size_t kUnrealAudioSfxOffset       = 0x24C;
    inline constexpr float kUnrealAudioVolumeScale      = 0.01f;
    inline constexpr size_t kUnrealAudioMasterGainSfx   = 0xCC;
    inline constexpr size_t kUnrealAudioMasterGainMusic = 0xD0;
    inline constexpr float kUnrealAudioCurveExponent    = 1.4476483f;
    inline constexpr float kUnrealAudioCurveMax         = 2.0f;
    inline constexpr size_t kUnrealAudioSubmixMusic     = 0x30;
    inline constexpr size_t kUnrealAudioSubmixSfx       = 0x38;
    inline constexpr size_t kUnrealAudioSubmixEntries   = 0x70;
    inline constexpr size_t kUnrealAudioSubmixCount     = 0x78;
    inline constexpr size_t kUnrealAudioSubmixStride    = 0x20;
    inline constexpr size_t kUnrealAudioSubmixValue     = 0x08;

    // A recovered offset has to be within this distance of one of the three above.
    inline constexpr float kUnrealAudioCurveOffsetTolerance = 0.05f;
    inline constexpr float kUnrealMaxVolumePercent          = 100.0f;
    // The SampleManager mixes `byte / 128` for its own sounds. Not 127: the byte 64
    // has to read as 0.5.
    inline constexpr float kSampleManagerVolumeScale = 128.0f;
    inline constexpr int32_t kMaxSubmixEntries       = 64;

    // Shared half: the game speed and the remaster curve maths.
    class AudioManager : public IAudioManager, protected HostModule
    {
      public:
        float GetTimeScale() const final;
        std::optional<AudioMix> GetVolume() const final;

        static float ApplyCurve(float value, float offset);
        static float DetectCurveOffset(float value, std::optional<float> appliedVolume);

      protected:
        struct Addresses
        {
            uintptr_t timeScale = 0; // CTimer::ms_fTimeScale
        };

        AudioManager(Addresses addresses, uintptr_t imageBase) : HostModule(imageBase), a(addresses) {}

        // 0..1, or false when this host has no mixer or the value looks wrong.
        virtual bool ReadSliders(float& sfx, float& music) const = 0;
        // Slider value -> what the game feeds its mixer; the classics pass it through.
        virtual float Shape(float slider, bool /*music*/) const { return slider; }

      private:
        Addresses a;
    };

    class ClassicAudio final : public AudioManager
    {
      public:
        struct Addresses
        {
            uintptr_t sampleManager;
            uintptr_t sfxOffset;   // m_nEffectsVolume (uint8)
            uintptr_t musicOffset; // m_nMusicVolume (uint8)
            uintptr_t timeScale;
        };

        static constexpr Addresses kIii = {0x7341E0, 0x0, 0x1, 0x8F2C20};
        static constexpr Addresses kVc  = {0x983B90, 0x0, 0x1, 0x97F264};

        explicit ClassicAudio(Addresses addresses, uintptr_t imageBase = 0)
            : AudioManager({addresses.timeScale}, imageBase), a(addresses)
        {
        }

      protected:
        bool ReadSliders(float& sfx, float& music) const override;

      private:
        Addresses a;
    };

    class RemasterAudio final : public AudioManager
    {
      public:
        struct Addresses
        {
            uintptr_t settingsRoot; // RVA of the global the settings handler loads
            uintptr_t timeScale;
        };

        static constexpr Addresses kIiiDeSteam = {0x5483708, 0x5042F50};
        static constexpr Addresses kIiiDeEpic  = {0x547B768, 0x503AF98};
        static constexpr Addresses kIiiDeRgl   = {0x547A6E0, 0x5039F54};
        static constexpr Addresses kVcDeSteam  = {0x550A458, 0x5120D48};
        static constexpr Addresses kVcDeEpic   = {0x55094D0, 0x5120398};
        static constexpr Addresses kVcDeRgl    = {0x5508460, 0x511F2A8};
        static constexpr Addresses kSaDeSteam  = {0x57D7F70, 0x523A2DC};
        static constexpr Addresses kSaDeEpic   = {0x57D8010, 0x523A398};
        static constexpr Addresses kSaDeRgl    = {0x57D6FC0, 0x5239678};

        explicit RemasterAudio(Addresses addresses, uintptr_t imageBase)
            : AudioManager({addresses.timeScale}, imageBase), a(addresses)
        {
        }

      protected:
        bool ReadSliders(float& sfx, float& music) const override;
        float Shape(float slider, bool music) const override;

      private:
        // Re-resolved per frame: null in the front end, back on level load.
        uintptr_t Device() const;
        uintptr_t Settings() const;

        Addresses a;
    };

} // namespace audio::host
