#pragma once

#include <memory>
#include <optional>
#include <string>

#include "AudioManagers.h"
#include "BuildRows.h"
#include "CameraView.h"
#include "EntityPools.h"
#include "HostTypes.h"
#include "engine/GameState.h"

namespace audio::host
{
    class GameHost final : public IGameState
    {
      public:
        std::unique_ptr<IAudioManager> audio;
        std::unique_ptr<CameraView> view;
        std::unique_ptr<EntityPools> pools;

        HostTier tier = HostTier::T0; // used by the log only
        std::string name;

        // Non-null whenever pools exist, on every host.
        IEntityResolver* Entities() const { return pools.get(); }

        std::optional<Camera> camera() const override { return view == nullptr ? std::nullopt : view->GetFrame(); }
        bool cameraJustChanged() const override { return view != nullptr && view->JustChanged(); }
        float timeScale() const override { return audio == nullptr ? 1.0f : audio->GetTimeScale(); }
        std::optional<AudioMix> mix() const override { return audio == nullptr ? std::nullopt : audio->GetVolume(); }
    };

    // III, VC, SA
    inline GameHost AssembleHost(const ClassicPreset& preset)
    {
        GameHost host;
        host.audio = std::make_unique<ClassicAudio>(preset.audio);
        host.view  = std::make_unique<CameraView>(preset.camera);
        host.pools = std::make_unique<EntityPools>(preset.pools, preset.entities);
        host.tier  = HostTier::T2;
        host.name  = preset.name != nullptr ? preset.name : "";
        return host;
    }

    // DE
    inline GameHost AssembleHost(const RemasterBuildRow& row, uintptr_t imageBase)
    {
        GameHost host;
        host.audio = std::make_unique<RemasterAudio>(row.audio, imageBase);
        host.view  = std::make_unique<CameraView>(row.camera, imageBase);
        host.pools = std::make_unique<EntityPools>(row.pools, row.entities, imageBase);
        host.tier  = row.camera.cameraObject != 0 ? HostTier::T2 : HostTier::T1;
        host.name  = row.name != nullptr ? row.name : "";
        return host;
    }

    inline bool BuildRowMatches(const RemasterBuildRow& row, uintptr_t scriptVmRva, uintptr_t moduleSize)
    {
        if (row.scriptVmRva != scriptVmRva) return false;
        return row.moduleSize == 0 || row.moduleSize == moduleSize;
    }
} // namespace audio::host
