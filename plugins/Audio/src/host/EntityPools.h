#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "HostTypes.h"

#include "engine/Placement.h"

// The game's object, ped and vehicle pools: the pool layout, how a script handle maps to
// an entity, and where that entity keeps its matrix.

namespace audio::host
{
    // Where an entity keeps its placed matrix. `matrixPointer == 0` means inline.
    struct EntityLayout
    {
        size_t matrixOffset  = 0;
        size_t matrixPointer = 0; // CMatrix*, null until the entity is in the world
        size_t placement     = 0; // CSimpleTransform: Vec3 position + float heading
    };

    // 0x4: III/VC classic (vptr first). 0x8: III/VC DE. SA DE kept the classic
    // pointer + simple transform instead of an inline matrix.
    inline constexpr EntityLayout kEntityInline         = {0x4, 0, 0};
    inline constexpr EntityLayout kEntityInlineRemaster = {0x8, 0, 0};
    inline constexpr EntityLayout kEntityPointer        = {0, 0x18, 0x8};

    class EntityPools final : public IEntityResolver, protected HostModule
    {
      public:
        struct Addresses
        {
            uintptr_t objectGlobal;
            uintptr_t pedGlobal;
            uintptr_t vehicleGlobal;
            size_t objectStride; // CObject / CPed / CVehicle
            size_t pedStride;
            size_t vehicleStride;
        };

        static constexpr Addresses kIii10      = {0x880E28, 0x8F2C60, 0x9430DC, 0x19C, 0x5F0, 0x5A8};
        static constexpr Addresses kVc10       = {0x94DBE0, 0x97F2AC, 0xA0FDE4, 0x1A0, 0x6D8, 0x5DC};
        static constexpr Addresses kIiiDeSteam = {0x53D74B8, 0x53D7470, 0x53D74A8, 0x2B0, 0x920, 0x7A0};
        static constexpr Addresses kIiiDeEpic  = {0x53CF518, 0x53CF4D0, 0x53CF508, 0x2B0, 0x920, 0x7A0};
        static constexpr Addresses kIiiDeRgl   = {0x53CE4E0, 0x53CE4A8, 0x53CE4E8, 0x2B0, 0x920, 0x7A0};
        static constexpr Addresses kVcDeSteam  = {0x545DE48, 0x545DE38, 0x545DE30, 0x270, 0xB78, 0x7B8};
        static constexpr Addresses kVcDeEpic   = {0x545CEA8, 0x545CE98, 0x545CE90, 0x270, 0xB78, 0x7B8};
        static constexpr Addresses kVcDeRgl    = {0x545BE30, 0x545BE28, 0x545BE40, 0x270, 0xB78, 0x7B8};
        static constexpr Addresses kSaDeSteam  = {0x572B588, 0x572B5A0, 0x572B598, 0x248, 0xB10, 0xDB8};
        static constexpr Addresses kSaDeEpic   = {0x572B5B0, 0x572B5C8, 0x572B5C0, 0x248, 0xB10, 0xDB8};
        static constexpr Addresses kSaDeRgl    = {0x572A580, 0x572A598, 0x572A590, 0x248, 0xB10, 0xDB8};

        EntityPools(Addresses addresses, EntityLayout layout, uintptr_t imageBase = 0)
            : HostModule(imageBase), a(addresses), layout(layout)
        {
        }

        // 0 when the pool is not ready.
        int Count(EntityKind kind) const;

        // The entity itself for a live handle, or nullptr.
        void* Get(EntityKind kind, int handle) const;

        std::unique_ptr<IPlaceable> Resolve(EntityKind kind, int handle) const override;

      private:
        uintptr_t GlobalFor(EntityKind kind) const;
        size_t StrideFor(EntityKind kind) const;

        Addresses a;
        EntityLayout layout;
    };

    class EntityPlaceable final : public IPlaceable
    {
      public:
        EntityPlaceable(const EntityPools& pools, EntityLayout layout, EntityKind kind, int handle)
            : pools(pools), layout(layout), kind(kind), handle(handle)
        {
        }

        bool valid() const override;
        Vec3 transformPoint(const Vec3& offset) const override;

      private:
        const EntityPools& pools;
        EntityLayout layout;
        EntityKind kind;
        int handle;
    };
} // namespace audio::host
