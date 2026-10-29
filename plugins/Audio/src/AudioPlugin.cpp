#include "AudioPlugin.h"

#include <utility>

namespace audio
{
    AudioPlugin::AudioPlugin(const Config& configuration, std::string asiFolder)
        : config(configuration), asiFolder(std::move(asiFolder)), dispatcher(soundSystem)
    {
        RebuildHostContext();
    }

    void AudioPlugin::Tick(unsigned int currentTimeMs, float frameTimeMs, bool isPaused, bool isRestarting)
    {
        if (!initAttempted)
        {
            // The first frame can arrive before OnRuntimeInit (or after it ran without an
            // audio device), so try once here as well.
            initAttempted = true;
            soundSystem.Init(config, asiFolder.c_str());
        }

        // While the runtime restarts, the host and the streams are being rebuilt.
        if (isRestarting) return;

        if (soundSystem.Initialized()) soundSystem.Process(host, isPaused, currentTimeMs, frameTimeMs);
    }

    void AudioPlugin::OnRuntimeInit()
    {
        soundSystem.Clear();
        RebuildHostContext();

        initAttempted = true;
        soundSystem.Init(config, asiFolder.c_str());
    }

    void AudioPlugin::RebuildHostContext()
    {
        host = host::CreateHost();
        dispatcher.SetEntityResolver(host.Entities());
    }
} // namespace audio
