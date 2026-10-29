#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include <cstdio>
#include <cstdint>
#include <iterator>
#include <string>

#include "cleo_redux_sdk.h"

#include "AudioPlugin.h"
#include "engine/Log.h"

// The only file that talks to CLEO directly: it builds the plugin, reads audio.ini and
// registers one callback per script command. The rest of the plugin uses the SDK only
// for the script parameter accessors.

namespace
{
    struct SdkCommand
    {
        const char* name;
        CommandHandler handler;
    };

    // At load: registers the commands and the two engine callbacks, then logs the
    // unload.
    struct PluginInit
    {
        PluginInit();

        ~PluginInit() { Log("Audio plugin: unloading"); }
    };

    audio::Config LoadConfig();
    std::string AsiFolder();

    // Built on first use, so the config, the game-build check and the ASI folder are
    // read only after the SDK is up.
    audio::AudioPlugin& Plugin();

    void __cdecl OnAfterGameProcessTick(unsigned int currentTime, int timeStep, bool isPaused, bool isRestarting);
    void __cdecl OnRuntimeInitCallback();

    // One small function per command. CLEO hands a callback only the script context, so
    // the handler to run has to be baked in - which is what this template does, once per
    // table entry below.
    template <auto Handler> HandlerResult __cdecl CommandThunk(Context context)
    {
        (Plugin().Commands().*Handler)(context);
        return HandlerResult::CONTINUE;
    }

    // The script names, and the handler each one runs.
    const SdkCommand kCommands[] = {
        {"LOAD_AUDIO_STREAM", &CommandThunk<&audio::CommandDispatcher::LoadAudioStream>},
        {"LOAD_3D_AUDIO_STREAM", &CommandThunk<&audio::CommandDispatcher::Load3dAudioStream>},
        {"SET_AUDIO_STREAM_STATE", &CommandThunk<&audio::CommandDispatcher::SetStreamState>},
        {"REMOVE_AUDIO_STREAM", &CommandThunk<&audio::CommandDispatcher::RemoveStream>},
        {"GET_AUDIO_STREAM_LENGTH", &CommandThunk<&audio::CommandDispatcher::GetStreamLength>},
        {"GET_AUDIO_STREAM_STATE", &CommandThunk<&audio::CommandDispatcher::GetStreamState>},
        {"GET_AUDIO_STREAM_VOLUME", &CommandThunk<&audio::CommandDispatcher::GetStreamVolume>},
        {"SET_AUDIO_STREAM_VOLUME", &CommandThunk<&audio::CommandDispatcher::SetStreamVolume>},
        {"SET_AUDIO_STREAM_LOOPED", &CommandThunk<&audio::CommandDispatcher::SetStreamLooped>},
        {"IS_AUDIO_STREAM_PLAYING", &CommandThunk<&audio::CommandDispatcher::IsStreamPlaying>},
        {"GET_AUDIO_STREAM_DURATION", &CommandThunk<&audio::CommandDispatcher::GetStreamDuration>},
        {"GET_AUDIO_STREAM_SPEED", &CommandThunk<&audio::CommandDispatcher::GetStreamSpeed>},
        {"SET_AUDIO_STREAM_SPEED", &CommandThunk<&audio::CommandDispatcher::SetStreamSpeed>},
        {"SET_AUDIO_STREAM_VOLUME_WITH_TRANSITION",
         &CommandThunk<&audio::CommandDispatcher::SetStreamVolumeWithTransition>},
        {"SET_AUDIO_STREAM_SPEED_WITH_TRANSITION",
         &CommandThunk<&audio::CommandDispatcher::SetStreamSpeedWithTransition>},
        {"GET_AUDIO_STREAM_PROGRESS", &CommandThunk<&audio::CommandDispatcher::GetStreamProgress>},
        {"SET_AUDIO_STREAM_PROGRESS", &CommandThunk<&audio::CommandDispatcher::SetStreamProgress>},
        {"GET_AUDIO_STREAM_PROGRESS_SECONDS", &CommandThunk<&audio::CommandDispatcher::GetStreamProgressSeconds>},
        {"SET_AUDIO_STREAM_PROGRESS_SECONDS", &CommandThunk<&audio::CommandDispatcher::SetStreamProgressSeconds>},
        {"GET_AUDIO_STREAM_TYPE", &CommandThunk<&audio::CommandDispatcher::GetStreamType>},
        {"SET_AUDIO_STREAM_TYPE", &CommandThunk<&audio::CommandDispatcher::SetStreamType>},
        {"SET_PLAY_3D_AUDIO_STREAM_AT_COORDS", &CommandThunk<&audio::CommandDispatcher::SetPlayAtCoords>},
        {"SET_PLAY_3D_AUDIO_STREAM_AT_OBJECT", &CommandThunk<&audio::CommandDispatcher::SetPlayAtObject>},
        {"SET_PLAY_3D_AUDIO_STREAM_AT_CHAR", &CommandThunk<&audio::CommandDispatcher::SetPlayAtChar>},
        {"SET_PLAY_3D_AUDIO_STREAM_AT_CAR", &CommandThunk<&audio::CommandDispatcher::SetPlayAtCar>},
        {"SET_AUDIO_STREAM_SOURCE_SIZE", &CommandThunk<&audio::CommandDispatcher::SetSourceSize>},
    };

    PluginInit::PluginInit()
    {
        char version[64] = {0};
        GetCLEOVersion(version);

        char message[256];
        std::snprintf(
            message, sizeof(message), "Audio plugin: SDK v%ld, CLEO %s, host id %d", GetSDKVersion(), version,
            static_cast<int>(GetHostId())
        );
        Log(message);

        for (const SdkCommand& command : kCommands)
            RegisterCommand(command.name, command.handler);
        OnAfterGameProcess(&OnAfterGameProcessTick);
        OnRuntimeInit(&OnRuntimeInitCallback);

        std::snprintf(message, sizeof(message), "Audio plugin: registered %zu commands", std::size(kCommands));
        Log(message);
    }

    // CLEO calls this from inside the game's own frame loop, so it also runs while
    // paused and reports the game's real time and pause state.
    void __cdecl OnAfterGameProcessTick(unsigned int currentTime, int timeStep, bool isPaused, bool isRestarting)
    {
        Plugin().Tick(currentTime, static_cast<float>(timeStep), isPaused, isRestarting);
    }

    void __cdecl OnRuntimeInitCallback()
    {
        Plugin().OnRuntimeInit();
    }

    audio::AudioPlugin& Plugin()
    {
        static audio::AudioPlugin instance(LoadConfig(), AsiFolder());
        return instance;
    }

    audio::Config LoadConfig()
    {
        char plugins[MAX_PATH] = {0};
        GetDirectoryPath(Directory::PLUGINS, plugins);

        char path[MAX_PATH] = {0};
        std::snprintf(path, sizeof(path), "%s\\audio.ini", plugins);

        audio::Config config;
        config.Load(path);
        return config;
    }

    // An ASI loader may place the ASI in a subfolder, so ask the SDK for its
    // directory (Directory::ASI, SDK v8) instead of assuming the host folder.
    std::string AsiFolder()
    {
        char path[MAX_PATH] = {0};
        GetDirectoryPath(Directory::ASI, path);
        return std::string(path);
    }

    PluginInit g_init;
} // namespace
