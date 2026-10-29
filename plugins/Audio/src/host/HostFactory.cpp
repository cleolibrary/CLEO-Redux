#include "HostFactory.h"
#include <windows.h>
#include <iterator>
#include "engine/Log.h"
#include "cleo_redux_sdk.h"

namespace audio::host
{
    namespace
    {
        struct DetectedRemaster
        {
            const RemasterBuildRow* row = nullptr;
            uintptr_t imageBase         = 0;
        };

        // Unique marker per host
        constexpr const char* kScriptVmSymbol = "CRunningScript::ProcessCommands100To199";

        GameHost MakeClassic(const ClassicPreset& preset);
        GameHost MakeRemaster(const RemasterBuildRow& row, uintptr_t imageBase);
        GameHost MakeDetected(const RemasterBuildRow* rows, size_t count);
        GameHost MakeT0();

        DetectedRemaster DetectRemaster(const RemasterBuildRow* rows, size_t count);

        uintptr_t ModuleBase();
        uintptr_t HostExecutableSize();
        uintptr_t Rebase(uintptr_t address, uintptr_t imageBase);
        void LogTier(const GameHost& host);

        GameHost MakeClassic(const ClassicPreset& preset)
        {
            GameHost host = AssembleHost(preset);

            LogInfo(
                "Audio plugin: build '%s' (TheCamera %p, pools object/ped/vehicle %p/%p/%p)", host.name.c_str(),
                reinterpret_cast<void*>(Rebase(preset.camera.camera, 0)),
                reinterpret_cast<void*>(Rebase(preset.pools.objectGlobal, 0)),
                reinterpret_cast<void*>(Rebase(preset.pools.pedGlobal, 0)),
                reinterpret_cast<void*>(Rebase(preset.pools.vehicleGlobal, 0))
            );
            LogTier(host);

            return host;
        }

        GameHost MakeRemaster(const RemasterBuildRow& row, uintptr_t imageBase)
        {
            GameHost host = AssembleHost(row, imageBase);

            LogInfo(
                "Audio plugin: build '%s' (TheCamera %p, CCamera %p, pools object/ped/vehicle %p/%p/%p)",
                host.name.c_str(), reinterpret_cast<void*>(Rebase(row.camera.camera, imageBase)),
                reinterpret_cast<void*>(Rebase(row.camera.cameraObject, imageBase)),
                reinterpret_cast<void*>(Rebase(row.pools.objectGlobal, imageBase)),
                reinterpret_cast<void*>(Rebase(row.pools.pedGlobal, imageBase)),
                reinterpret_cast<void*>(Rebase(row.pools.vehicleGlobal, imageBase))
            );
            LogInfo(
                "Audio plugin: pool sizes object/ped/vehicle %d/%d/%d", host.pools->Count(EntityKind::Object),
                host.pools->Count(EntityKind::Ped), host.pools->Count(EntityKind::Vehicle)
            );
            LogTier(host);

            return host;
        }

        GameHost MakeDetected(const RemasterBuildRow* rows, size_t count)
        {
            const DetectedRemaster detected = DetectRemaster(rows, count);
            if (detected.row != nullptr) return MakeRemaster(*detected.row, detected.imageBase);

            LogWarning("Audio plugin: no known Definitive Edition build matched (%zu tried); staying at T0", count);
            return MakeT0();
        }

        GameHost MakeT0()
        {
            GameHost host;
            LogTier(host);

            return host;
        }

        DetectedRemaster DetectRemaster(const RemasterBuildRow* rows, size_t count)
        {
            DetectedRemaster detected;

            const auto symbol = reinterpret_cast<uintptr_t>(GetSymbolAddress(kScriptVmSymbol));
            if (symbol == 0)
            {
                LogWarning("Audio plugin: '%s' is not in the host symbol table; staying at T0", kScriptVmSymbol);
                return detected;
            }

            const uintptr_t imageBase = ModuleBase();
            if (imageBase == 0 || symbol < imageBase)
            {
                LogWarning("Audio plugin: cannot derive a build id from '%s'; staying at T0", kScriptVmSymbol);
                return detected;
            }

            const uintptr_t moduleSize = HostExecutableSize();
            const uintptr_t rva        = symbol - imageBase;

            for (size_t i = 0; i < count; ++i)
            {
                if (!BuildRowMatches(rows[i], rva, moduleSize)) continue;

                detected.row       = &rows[i];
                detected.imageBase = imageBase;
                return detected;
            }

            LogWarning(
                "Audio plugin: no table for '%s' RVA 0x%llX (executable size %llu); staying at T0", kScriptVmSymbol,
                static_cast<unsigned long long>(rva), static_cast<unsigned long long>(moduleSize)
            );
            return detected;
        }

        uintptr_t ModuleBase()
        {
            return reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
        }

        // On-disk size, the value CLEO's own locators key on. The in-memory PE headers
        // are not enough: IMAGE_NT_HEADERS only carry SizeOfImage, and the section table
        // leaves out whatever the linker or a signature appended. 0 disables the
        // size-specific rows.
        uintptr_t HostExecutableSize()
        {
            wchar_t path[MAX_PATH];
            const DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
            if (length == 0 || length == MAX_PATH) return 0;

            WIN32_FILE_ATTRIBUTE_DATA attributes{};
            if (GetFileAttributesExW(path, GetFileExInfoStandard, &attributes) == 0) return 0;

            return (static_cast<uintptr_t>(attributes.nFileSizeHigh) << 32) | attributes.nFileSizeLow;
        }

        uintptr_t Rebase(uintptr_t address, uintptr_t imageBase)
        {
            return address == 0 ? 0 : imageBase + address;
        }

        void LogTier(const GameHost& host)
        {
            LogInfo("Audio plugin: tier %s", TierName(host.tier));
        }
    } // namespace

    GameHost CreateHost()
    {
        const HostId hostId = GetHostId();
        LogInfo("Audio plugin: host id %d", static_cast<int>(hostId));

        switch (hostId)
        {
        case HostId::GTA3:
            return MakeClassic(kIiiClassic);
        case HostId::VC:
            return MakeClassic(kVcClassic);
        case HostId::GTA3_UNREAL:
            return MakeDetected(kIiiDeBuilds, std::size(kIiiDeBuilds));
        case HostId::VC_UNREAL:
            return MakeDetected(kVcDeBuilds, std::size(kVcDeBuilds));
        case HostId::SA_UNREAL:
            return MakeDetected(kSaDeBuilds, std::size(kSaDeBuilds));
        default:
            // Classic SA, IV, Bully, re3/reVC, custom hosts.
            return MakeT0();
        }
    }
} // namespace audio::host
