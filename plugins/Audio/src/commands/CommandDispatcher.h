#pragma once

#include <cstddef>
#include <cstdint>
#include "cleo_redux_sdk.h"
#include "engine/AudioStream.h"
#include "engine/Placement.h"
#include "engine/SoundSystem.h"

// The script commands. Each handler gets the script's context from CLEO, reads the
// arguments it needs from it and writes the results back.
namespace audio
{
    class CommandDispatcher
    {
      public:
        explicit CommandDispatcher(SoundSystem& soundSystem, const IEntityResolver* entities = nullptr);

        CommandDispatcher(const CommandDispatcher&)            = delete;
        CommandDispatcher& operator=(const CommandDispatcher&) = delete;

        // Replaced on runtime init.
        void SetEntityResolver(const IEntityResolver* resolver) { entities = resolver; }

        static constexpr size_t kPathBufferSize = 512;

        void LoadAudioStream(Context context);
        void Load3dAudioStream(Context context);
        void SetStreamState(Context context);
        void RemoveStream(Context context);
        void GetStreamLength(Context context);
        void GetStreamState(Context context);
        void GetStreamVolume(Context context);
        void SetStreamVolume(Context context);
        void SetStreamLooped(Context context);
        void IsStreamPlaying(Context context);
        void GetStreamDuration(Context context);
        void GetStreamSpeed(Context context);
        void SetStreamSpeed(Context context);
        void SetStreamVolumeWithTransition(Context context);
        void SetStreamSpeedWithTransition(Context context);
        void GetStreamProgress(Context context);
        void SetStreamProgress(Context context);
        void GetStreamProgressSeconds(Context context);
        void SetStreamProgressSeconds(Context context);
        void GetStreamType(Context context);
        void SetStreamType(Context context);
        void SetPlayAtCoords(Context context);
        void SetPlayAtObject(Context context);
        void SetPlayAtChar(Context context);
        void SetPlayAtCar(Context context);
        void SetSourceSize(Context context);

      private:
        void SetPlayAtEntity(Context context, EntityKind kind, const char* commandName);
        void LoadStream(Context context, bool in3d);
        void WriteStreamFloat(Context context, float (AudioStream::*getter)() const);
        AudioStream* ReadStream(Context context);
        AudioStream* Read3dStream(Context context, const char* commandName);

        SoundSystem& soundSystem;
        const IEntityResolver* entities;
        bool warnedUnsupported3d = false;
    };
} // namespace audio
