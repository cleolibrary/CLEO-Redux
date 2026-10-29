#pragma once

#include <string>

#include "commands/CommandDispatcher.h"
#include "engine/Config.h"
#include "engine/SoundSystem.h"
#include "host/HostFactory.h"

// Owns the sound engine, the game reader and the command handlers. dllmain drives it
// from two CLEO callbacks: the per-frame tick (runs even while paused) and runtime
// init. Only the command handlers talk to the SDK.

namespace audio
{
    class AudioPlugin
    {
      public:
        AudioPlugin(const Config& config, std::string asiFolder);

        AudioPlugin(const AudioPlugin&)            = delete;
        AudioPlugin& operator=(const AudioPlugin&) = delete;

        // Called by the SDK callback of whichever command was registered.
        CommandDispatcher& Commands() { return dispatcher; }

        void Tick(unsigned int currentTimeMs, float frameTimeMs, bool isPaused, bool isRestarting);

        void OnRuntimeInit();

      private:
        // The streams are cleared first, because each 3D stream reads the pools of the
        // host that is replaced here.
        void RebuildHostContext();

        SoundSystem soundSystem;
        Config config;
        std::string asiFolder;
        host::GameHost host;
        CommandDispatcher dispatcher;

        // A missing bass.dll must not be retried (and re-logged) every frame.
        bool initAttempted = false;
    };
} // namespace audio
