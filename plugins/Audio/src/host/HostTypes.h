#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "engine/GameState.h"

namespace audio::host
{
    enum class HostTier
    {
        T0, // no camera (2D only)
        T1, // entity pools only
        T2, // camera + entity pools
    };

    // The listener frame is read out of the active CCam entry, whose layout differs
    // per game: III's entry is 0x140 bytes and its members sit 0x18 lower than Vice
    // City's 0x158-byte entry.
    struct UnrealCamLayout
    {
        size_t activeCam; // m_nActiveCam (uint8), index into the CCam array
        size_t array;     // m_asCams[0]
        size_t stride;    // sizeof(CCam)
        size_t front;     // m_vecFront, unit look direction
        size_t source;    // m_vecSource, camera position
        size_t up;        // m_vecUp, unit up
    };

    inline constexpr size_t kUnrealCamCount = 3;
    inline constexpr size_t kMatrixRight    = 0x00;
    inline constexpr size_t kMatrixForward  = 0x10;
    inline constexpr size_t kMatrixUp       = 0x20;
    inline constexpr size_t kMatrixPosition = 0x30;

    class IAudioManager
    {
      public:
        virtual ~IAudioManager() = default;

        virtual float GetTimeScale() const                = 0;
        virtual std::optional<AudioMix> GetVolume() const = 0;
    };

    // Classic presets hold absolute addresses, the remasters hold RVAs. `Addr()`
    // keeps 0 meaning "this host has no such address"; field offsets (matrix,
    // sliders, cam layout, strides) never go through it.
    class HostModule
    {
      protected:
        explicit HostModule(uintptr_t imageBase = 0) : imageBase(imageBase) {}

        uintptr_t Addr(uintptr_t offsetOrAbsolute) const
        {
            return offsetOrAbsolute == 0 ? 0 : imageBase + offsetOrAbsolute;
        }

      private:
        uintptr_t imageBase;
    };

    inline const char* TierName(HostTier tier)
    {
        switch (tier)
        {
        case HostTier::T2:
            return "T2 (camera + pools)";
        case HostTier::T1:
            return "T1 (pools; no camera)";
        default:
            return "T0 (no camera; 2D only)";
        }
    }
} // namespace audio::host
