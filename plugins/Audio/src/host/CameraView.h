#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "HostTypes.h"

namespace audio::host
{
    class CameraView final : protected HostModule
    {
      public:
        // One CCamera instance per game, described two ways: III and Vice City keep the
        // placed matrix inline (cameraMatrix), everything newer fills m_aCams[3] and
        // points at the active entry (cam). `camera` is the instance itself: an absolute
        // address on the 32-bit games, an RVA on the remasters.
        struct Addresses
        {
            uintptr_t camera    = 0; // CCamera instance (TheCamera)
            size_t cameraMatrix = 0; // CMatrix offset inside it (III has a vptr first)
            size_t justSwitched = 0; // m_bJust_Switched
            size_t justRestored = 0; // m_bCameraJustRestored
            CamArrayLayout cam{};
        };

        static constexpr Addresses kIii10      = {0x6FACF8, 0x4, 0x5D, 0x50, {}};
        static constexpr Addresses kVc10       = {0x7E4688, 0x0, 0x5A, 0x4C, {}};
        static constexpr Addresses kSa10       = {0xB6F028, 0x0, 0x2A, 0x1C, {0x59, 0x174, 0x238, 0x190, 0x19C, 0x1B4}};
        static constexpr Addresses kIiiDeSteam = {0x4D9F880, 0, 0, 0, {0x7A, 0x1A0, 0x140, 0xDC, 0xE8, 0x100}};
        static constexpr Addresses kIiiDeEpic  = {0x4D978B0, 0, 0, 0, {0x7A, 0x1A0, 0x140, 0xDC, 0xE8, 0x100}};
        static constexpr Addresses kIiiDeRgl   = {0x4D96890, 0, 0, 0, {0x7A, 0x1A0, 0x140, 0xDC, 0xE8, 0x100}};
        static constexpr Addresses kVcDeSteam  = {0x4E2A200, 0, 0, 0, {0x74, 0x190, 0x158, 0xF4, 0x100, 0x118}};
        static constexpr Addresses kVcDeEpic   = {0x4E29230, 0, 0, 0, {0x74, 0x190, 0x158, 0xF4, 0x100, 0x118}};
        static constexpr Addresses kVcDeRgl    = {0x4E28200, 0, 0, 0, {0x74, 0x190, 0x158, 0xF4, 0x100, 0x118}};
        static constexpr Addresses kSaDeSteam  = {0x53E23D0, 0, 0, 0, {0x5B, 0x188, 0x1B8, 0x110, 0x11C, 0x134}};
        static constexpr Addresses kSaDeEpic   = {0x53E2410, 0, 0, 0, {0x5B, 0x188, 0x1B8, 0x110, 0x11C, 0x134}};
        static constexpr Addresses kSaDeRgl    = {0x53E13E0, 0, 0, 0, {0x5B, 0x188, 0x1B8, 0x110, 0x11C, 0x134}};

        explicit CameraView(Addresses addresses, uintptr_t imageBase = 0) : HostModule(imageBase), a(addresses) {}

        // std::nullopt while the frame is not initialised yet.
        std::optional<Camera> GetFrame() const;
        bool JustChanged() const;

      private:
        std::optional<Camera> ReadPlacedMatrix() const;
        std::optional<Camera> ReadActiveCam() const;

        Addresses a;
    };
} // namespace audio::host
