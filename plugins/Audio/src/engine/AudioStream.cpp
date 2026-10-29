#include "AudioStream.h"

#include <algorithm>
#include <cmath>
#include <cstring>

#include "Log.h"
#include "SoundSystem.h"

namespace audio
{
    AudioStream::AudioStream(const char* filepath)
    {
        Open(filepath, 0);
    }

    AudioStream::~AudioStream()
    {
        if (streamInternal)
        {
            BASS_StreamFree(streamInternal);
            streamInternal = 0;
        }
    }

    bool AudioStream::Open(const char* filepath, unsigned extraFlags)
    {
        if (filepath == nullptr || filepath[0] == '\0')
        {
            LogWarning("Audiostream with an empty source path was not created");
            return false;
        }

        unsigned flags = BASS_SAMPLE_SOFTWARE | BASS_STREAM_PRESCAN | extraFlags;
        if (SoundSystem::useFloatAudio) flags |= BASS_SAMPLE_FLOAT;

        // The source kind follows the prefix only: a missing local file must not
        // trigger network I/O.
        if (IsNetworkSource(filepath))
            streamInternal = BASS_StreamCreateURL(filepath, 0, flags, nullptr, nullptr);
        else
            streamInternal = BASS_StreamCreateFile(FALSE, filepath, 0, 0, flags);

        if (!streamInternal)
        {
            LogWarning("Loading of audiostream '%s' failed. Error code: %d", filepath, BASS_ErrorGetCode());
            return false;
        }

        BASS_ChannelGetAttribute(streamInternal, BASS_ATTRIB_FREQ, &rate);
        ok = true;
        return true;
    }

    void AudioStream::Play()
    {
        if (state == Stopped) BASS_ChannelSetPosition(streamInternal, 0, BASS_POS_BYTE); // rewind
        state = PlayingInactive;                                                         // Process() starts the channel
    }

    void AudioStream::Pause(bool changeState)
    {
        if (GetState() != Playing) return;

        BASS_ChannelPause(streamInternal);
        state = changeState ? Paused : PlayingInactive;
    }

    void AudioStream::Stop()
    {
        BASS_ChannelPause(streamInternal);
        state = Stopped;

        speed.finish();
        volume.finish();
    }

    void AudioStream::Resume()
    {
        Play();
    }

    void AudioStream::Process()
    {
        if (state == PlayingInactive)
        {
            if (BASS_ChannelPlay(streamInternal, FALSE)) state = Playing;
        }
        else if (state == Playing && BASS_ChannelIsActive(streamInternal) == BASS_ACTIVE_STOPPED)
        {
            state = Stopped; // end reached
        }

        const float prevSpeed = speed.value();

        speed.update(SoundSystem::timeStep);
        volume.update(SoundSystem::timeStep);

        // Transitioning the speed to 0 pauses playback.
        if (prevSpeed > 0.0f && speed.value() <= 0.0f) Pause();

        if (state != Playing) return;

        BASS_ChannelSetAttribute(streamInternal, BASS_ATTRIB_VOL, CalculateVolume());

        float freq = rate * CalculateSpeed();
        freq       = std::max(freq, 0.000001f); // 0 would mean the original speed
        BASS_ChannelSetAttribute(streamInternal, BASS_ATTRIB_FREQ, freq);
    }

    float AudioStream::CalculateVolume()
    {
        return volume.value() * MasterVolume(type);
    }

    float AudioStream::MasterVolume(StreamType type)
    {
        switch (type)
        {
        case StreamType::Sfx:
        case StreamType::UserInterface:
            return SoundSystem::masterVolumeSfx;
        case StreamType::Music:
            return SoundSystem::masterVolumeMusic;
        default:
            return 1.0f;
        }
    }

    float AudioStream::CalculateSpeed()
    {
        // Sfx and Music follow the game speed, so slow motion sounds slow.
        switch (type)
        {
        case StreamType::Sfx:
        case StreamType::Music:
            return speed.value() * SoundSystem::masterSpeed;
        default:
            return speed.value();
        }
    }

    AudioStream::StreamState AudioStream::GetState() const
    {
        return (state == PlayingInactive) ? Playing : state;
    }

    float AudioStream::GetLength() const
    {
        return static_cast<float>(
            BASS_ChannelBytes2Seconds(streamInternal, BASS_ChannelGetLength(streamInternal, BASS_POS_BYTE))
        );
    }

    void AudioStream::SetProgress(float value)
    {
        if (GetState() == Stopped) state = Paused; // resume from the new position

        value              = std::clamp(value, 0.0f, 1.0f);
        const auto bytePos = BASS_ChannelSeconds2Bytes(streamInternal, GetLength() * value);

        BASS_ChannelSetPosition(streamInternal, bytePos, BASS_POS_BYTE);
    }

    float AudioStream::GetProgress() const
    {
        auto bytePos = BASS_ChannelGetPosition(streamInternal, BASS_POS_BYTE);
        if (bytePos == static_cast<QWORD>(-1)) bytePos = 0; // query error or not available yet

        const auto pos = BASS_ChannelBytes2Seconds(streamInternal, bytePos);
        const auto total =
            BASS_ChannelBytes2Seconds(streamInternal, BASS_ChannelGetLength(streamInternal, BASS_POS_BYTE));

        if (total <= 0.0) return 0.0f; // e.g. a live URL stream without a known length

        return static_cast<float>(pos / total);
    }

    void AudioStream::SetLooping(bool enable)
    {
        BASS_ChannelFlags(streamInternal, enable ? BASS_SAMPLE_LOOP : 0, BASS_SAMPLE_LOOP);
    }

    bool AudioStream::GetLooping() const
    {
        return (BASS_ChannelFlags(streamInternal, 0, 0) & BASS_SAMPLE_LOOP) != 0;
    }

    void AudioStream::SetVolume(float value, float transitionTime)
    {
        volume.setValue(std::max(value, 0.0f), transitionTime);
    }

    float AudioStream::GetVolume() const
    {
        return volume.value();
    }

    void AudioStream::SetSpeed(float value, float transitionTime)
    {
        if (value > 0.0f && transitionTime > 0.0f) Resume();
        speed.setValue(std::max(value, 0.0f), transitionTime);
    }

    float AudioStream::GetSpeed() const
    {
        return speed.value();
    }

    void AudioStream::SetType(StreamType value)
    {
        switch (value)
        {
        case StreamType::Sfx:
        case StreamType::Music:
        case StreamType::UserInterface:
            type = value;
            break;

        default:
            type = StreamType::None;
        }
    }

    StreamType AudioStream::GetType() const
    {
        return type;
    }

    bool AudioStream::IsOk() const
    {
        return ok;
    }

    HSTREAM AudioStream::GetInternal()
    {
        return streamInternal;
    }

    // 2D streams ignore the 3D calls.
    void AudioStream::Set3dPosition(const Vec3&) {}

    void AudioStream::Set3dSourceSize(float) {}

    void AudioStream::SetHostOwned(std::unique_ptr<IPlaceable>, const Vec3&) {}

    bool IsNetworkSource(const char* path)
    {
        if (path == nullptr) return false;

        return _strnicmp("http:", path, 5) == 0 || _strnicmp("https:", path, 6) == 0;
    }
} // namespace audio
