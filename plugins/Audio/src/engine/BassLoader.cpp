#include "BassLoader.h"

#include <cstdio>
#include <cstring>
#include <string>

#include "Log.h"

namespace audio
{
    BassApi g_bass;

    namespace
    {
        // 2.4.18.3 (2025-12-15), the floor CLEO5's SA.Audio plugin enforces.
        constexpr DWORD BASS_VER_MIN = 0x02041203;

        char g_loadedPath[MAX_PATH] = {0};

        void ClearBindings();
        const char* BassVersionToString(DWORD version);
        bool BindSymbols(HMODULE module);
        bool TryLoad(const char* path);

        void ClearBindings()
        {
            g_bass = BassApi{};
        }

        // BASS versions are laid out as bytes: major.minor.build.sub
        const char* BassVersionToString(DWORD version)
        {
            static char buffer[32];
            const auto* bytes = reinterpret_cast<const unsigned char*>(&version);
            std::snprintf(
                buffer, sizeof(buffer), "%u.%u.%u.%u", static_cast<unsigned>(bytes[3]), static_cast<unsigned>(bytes[2]),
                static_cast<unsigned>(bytes[1]), static_cast<unsigned>(bytes[0])
            );
            return buffer;
        }

        bool BindSymbols(HMODULE module)
        {
            const char* missing = nullptr;

#define BIND(name)                                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        g_bass.name = reinterpret_cast<decltype(g_bass.name)>(GetProcAddress(module, "BASS_" #name));                  \
        if (g_bass.name == nullptr)                                                                                    \
        {                                                                                                              \
            missing = "BASS_" #name;                                                                                   \
            goto bind_failed;                                                                                          \
        }                                                                                                              \
    } while (0)

            BIND(GetVersion);
            BIND(ErrorGetCode);
            BIND(SetConfig);
            BIND(GetDeviceInfo);
            BIND(Init);
            BIND(Free);
            BIND(GetInfo);
            BIND(Set3DFactors);
            BIND(Set3DPosition);
            BIND(Apply3D);
            BIND(StreamCreate);
            BIND(StreamCreateFile);
            BIND(StreamCreateURL);
            BIND(StreamFree);
            BIND(ChannelGetAttribute);
            BIND(ChannelSetAttribute);
            BIND(ChannelFlags);
            BIND(ChannelBytes2Seconds);
            BIND(ChannelSeconds2Bytes);
            BIND(ChannelGetLength);
            BIND(ChannelSetPosition);
            BIND(ChannelGetPosition);
            BIND(ChannelPlay);
            BIND(ChannelPause);
            BIND(ChannelIsActive);
            BIND(ChannelSet3DAttributes);
            BIND(ChannelSet3DPosition);

#undef BIND

            return true;

        bind_failed:
            LogError("BASS library does not export %s; treating it as absent", missing);
            return false;
        }

        bool TryLoad(const char* path)
        {
            HMODULE module = LoadLibraryA(path);
            if (module == nullptr)
            {
                const DWORD error = GetLastError();
                if (error == ERROR_MOD_NOT_FOUND)
                    LogInfo("BASS library '%s' not found", path);
                else
                    LogWarning("BASS library '%s' could not be loaded (error %lu)", path, error);

                return false;
            }

            if (!BindSymbols(module))
            {
                FreeLibrary(module);
                ClearBindings();
                return false;
            }

            const DWORD version = g_bass.GetVersion();
            if (version < BASS_VER_MIN)
            {
                LogError(
                    "BASS library '%s' is too old: %s, at least %s required", path, BassVersionToString(version),
                    BassVersionToString(BASS_VER_MIN)
                );
                FreeLibrary(module);
                ClearBindings();
                return false;
            }

            g_bass.module  = module;
            g_bass.version = version;

            std::snprintf(g_loadedPath, sizeof(g_loadedPath), "%s", path);

            LogInfo(
                "BASS library loaded: %s (version %s, minimum %s)", path, BassVersionToString(version),
                BassVersionToString(BASS_VER_MIN)
            );
            return true;
        }
    } // namespace

    bool BassLoad(const char* asiFolder)
    {
        if (BassLoaded()) return true;

        const std::string asiDir = asiFolder != nullptr ? asiFolder : "";

#if defined(_WIN64)
        const char* names[] = {"bass64.dll", "bass.dll"};
#else
        const char* names[] = {"bass.dll"};
#endif

        // 1. next to cleo_redux.asi (the packaged layout)
        for (const char* name : names)
        {
            if (asiDir.empty()) break;

            const std::string candidate = asiDir + "\\" + name;
            if (TryLoad(candidate.c_str())) return true;
        }

        // 2. the standard search order: application directory, system, CWD, PATH
        for (const char* name : names)
        {
            if (TryLoad(name)) return true;
        }

        LogError("BASS library could not be loaded; audio playback is unavailable");
        return false;
    }

    bool BassLoaded()
    {
        return g_bass.module != nullptr;
    }

    void BassUnload()
    {
        if (!BassLoaded()) return;

        FreeLibrary(g_bass.module);
        ClearBindings();
        g_loadedPath[0] = '\0';
    }
} // namespace audio
