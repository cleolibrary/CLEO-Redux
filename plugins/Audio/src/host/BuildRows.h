#pragma once

#include <cstdint>
#include "AudioManagers.h"
#include "CameraView.h"
#include "EntityPools.h"
#include "HostTypes.h"

namespace audio::host
{
    struct ClassicPreset
    {
        const char* name;
        ClassicAudio::Addresses audio;
        CameraView::Addresses camera;
        EntityPools::Addresses pools;
        EntityLayout entities;
    };

    // The remaster sliders live in the audio settings object instead of the SampleManager.
    struct RemasterBuildRow
    {
        const char* name;
        uintptr_t scriptVmRva;
        uintptr_t moduleSize;
        RemasterAudio::Addresses audio;
        CameraView::Addresses camera;
        EntityPools::Addresses pools;
        EntityLayout entities;
    };

    inline constexpr ClassicPreset kIiiClassic = {
        "III 1.0 EN", ClassicAudio::kIii, CameraView::kIii10, EntityPools::kIii10, kEntityInline,
    };

    inline constexpr ClassicPreset kVcClassic = {
        "VC 1.0 US", ClassicAudio::kVc, CameraView::kVc10, EntityPools::kVc10, kEntityInline,
    };

    inline constexpr ClassicPreset kClassicPresets[] = {kIiiClassic, kVcClassic};

    inline constexpr RemasterBuildRow kIiiDeBuilds[] = {
        {"III DE 1.0.113.21181 (Steam)", 0x10310F0, 0, RemasterAudio::kIiiDeSteam, CameraView::kIiiDeSteam,
         EntityPools::kIiiDeSteam, kEntityInlineRemaster},
        {"III DE 1.0.112.6680 (Epic)", 0x10303D0, 0, RemasterAudio::kIiiDeEpic, CameraView::kIiiDeEpic,
         EntityPools::kIiiDeEpic, kEntityInlineRemaster},
        {"III DE 1.0.112.6680 (RGL)", 0x102F5C0, 0, RemasterAudio::kIiiDeRgl, CameraView::kIiiDeRgl,
         EntityPools::kIiiDeRgl, kEntityInlineRemaster},
    };

    inline constexpr RemasterBuildRow kVcDeBuilds[] = {
        {"VC DE 1.0.113.21181 (Steam)", 0x104C160, 0, RemasterAudio::kVcDeSteam, CameraView::kVcDeSteam,
         EntityPools::kVcDeSteam, kEntityInlineRemaster},
        {"VC DE 1.0.112.6680 (Epic)", 0x104B7C0, 0, RemasterAudio::kVcDeEpic, CameraView::kVcDeEpic,
         EntityPools::kVcDeEpic, kEntityInlineRemaster},
        {"VC DE 1.0.112.6680 (RGL)", 0x104AD20, 0, RemasterAudio::kVcDeRgl, CameraView::kVcDeRgl, EntityPools::kVcDeRgl,
         kEntityInlineRemaster},
    };

    inline constexpr RemasterBuildRow kSaDeBuilds[] = {
        {"SA DE 1.0.113.21181 (Steam)", 0x10B7680, 89497064, RemasterAudio::kSaDeSteam, CameraView::kSaDeSteam,
         EntityPools::kSaDeSteam, kEntityPointer},
        {"SA DE 1.0.112.6680 (Steam)", 0x10B7680, 89496560, RemasterAudio::kSaDeSteam, CameraView::kSaDeSteam,
         EntityPools::kSaDeSteam, kEntityPointer},
        {"SA DE 1.0.112.6680 (Epic)", 0x10B6F60, 89496048, RemasterAudio::kSaDeEpic, CameraView::kSaDeEpic,
         EntityPools::kSaDeEpic, kEntityPointer},
        {"SA DE 1.0.112.6680 (RGL)", 0x10B61F0, 89492464, RemasterAudio::kSaDeRgl, CameraView::kSaDeRgl,
         EntityPools::kSaDeRgl, kEntityPointer},
    };
} // namespace audio::host
