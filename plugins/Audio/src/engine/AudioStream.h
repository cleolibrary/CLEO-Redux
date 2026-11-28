#pragma once

#include <memory>
#include "BassLoader.h"
#include "GameState.h"
#include "InterpolatedValue.h"

namespace audio
{
    class SoundSystem;

    // Mirrors the enum AudioStreamType.
    enum class StreamType
    {
        None          = 0, // raw stream volume only
        Sfx           = 1, // SoundSystem::masterVolumeSfx
        Music         = 2, // SoundSystem::masterVolumeMusic
        UserInterface = 3, // SoundSystem::masterVolumeSfx
    };

    // CLEO5's CAudioStream with dynamic BASS and no SA globals; the state machine,
    // interpolation and BASS calls are unchanged.
    class AudioStream
    {
      public:
        // Mirrors the enum AudioStreamState.
        enum StreamState
        {
            Stopped         = -1,
            PlayingInactive = 0, // playing, but not processed yet or silenced right now
            Playing         = 1,
            Paused          = 2,
        };

        explicit AudioStream(const char* filepath); // path, or an http:/https: URL
        virtual ~AudioStream();

        bool IsOk() const;
        HSTREAM GetInternal();

        StreamState GetState() const;
        void Play();
        void Pause(bool changeState = true);
        void Stop();
        void Resume();

        void SetLooping(bool enable);
        bool GetLooping() const;

        float GetLength() const; // seconds

        void SetProgress(float value); // 0.0 - 1.0
        float GetProgress() const;     // 0.0 - 1.0

        void SetSpeed(float value, float transitionTime = 0.0f);
        float GetSpeed() const;

        void SetType(StreamType value);
        StreamType GetType() const;

        void SetVolume(float value, float transitionTime = 0.0f);
        float GetVolume() const;

        // No-ops for 2D streams (warning-free, as in CLEO5).
        virtual bool Is3d() const { return false; }
        virtual void Set3dPosition(const Vec3& pos);
        virtual void Set3dSourceSize(float radius);

        // Owning, used by the command handlers: the placeable dies with the stream.
        virtual void SetHostOwned(std::unique_ptr<IPlaceable> placeable, const Vec3& offset);

        virtual void Process();
        virtual float CalculateVolume();
        virtual float CalculateSpeed();

      protected:
        AudioStream()                   = default;
        AudioStream(const AudioStream&) = delete;

        // Opens the BASS stream; false (and logged) on failure.
        bool Open(const char* filepath, unsigned extraFlags);

        // The host's master for a stream type, 1.0 for StreamType::None.
        static float MasterVolume(StreamType type);

        HSTREAM streamInternal    = 0;
        StreamState state         = Paused;
        StreamType type           = StreamType::Sfx;
        bool ok                   = false;
        float rate                = 44100.0f; // the file's sampling rate
        CInterpolatedValue speed  = {1.0f};
        CInterpolatedValue volume = {1.0f};
    };

    // The source kind follows the prefix, never a failed-open fallback.
    bool IsNetworkSource(const char* path);
} // namespace audio
