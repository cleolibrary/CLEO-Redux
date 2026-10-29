#include "EntityPools.h"

#include <cmath>
#include "Memory.h"

namespace audio::host
{
    namespace
    {
        bool IsPoolReady(uintptr_t global);

        bool IsPoolReady(uintptr_t global)
        {
            const uintptr_t pool = ReadPointer(global);
            if (pool == 0) return false;

            const uintptr_t objects = ReadPointer(pool);
            const uintptr_t flags   = ReadPointer(pool + kPointerSize);
            if (objects == 0 || flags == 0) return false;

            const auto size = *reinterpret_cast<const int32_t*>(pool + kPointerSize * 2);
            return size > 0;
        }
    } // namespace

    int EntityPools::Count(EntityKind kind) const
    {
        const uintptr_t global = Addr(GlobalFor(kind));
        if (global == 0 || !IsPoolReady(global)) return 0;

        const uintptr_t pool = ReadPointer(global);
        return *reinterpret_cast<const int32_t*>(pool + kPointerSize * 2);
    }

    void* EntityPools::Get(EntityKind kind, int handle) const
    {
        if (handle < 0) return nullptr;

        const uintptr_t global = Addr(GlobalFor(kind));
        if (global == 0) return nullptr;

        const uintptr_t pool = ReadPointer(global);
        if (pool == 0) return nullptr;

        const uintptr_t objects = ReadPointer(pool);
        const uintptr_t flags   = ReadPointer(pool + kPointerSize);
        if (objects == 0 || flags == 0) return nullptr;

        const auto size = *reinterpret_cast<const int32_t*>(pool + kPointerSize * 2);

        const int index = handle >> 8;
        const int id    = handle & 0xFF;

        if (index < 0 || index >= size) return nullptr;
        if (*reinterpret_cast<const uint8_t*>(flags + index) != static_cast<uint8_t>(id)) return nullptr;

        const size_t stride = StrideFor(kind);
        if (stride == 0) return nullptr;

        return reinterpret_cast<void*>(objects + static_cast<uintptr_t>(index) * stride);
    }

    std::unique_ptr<IPlaceable> EntityPools::Resolve(EntityKind kind, int handle) const
    {
        if (Get(kind, handle) == nullptr) return nullptr;

        return std::make_unique<EntityPlaceable>(*this, layout, kind, handle);
    }

    uintptr_t EntityPools::GlobalFor(EntityKind kind) const
    {
        switch (kind)
        {
        case EntityKind::Object:
            return a.objectGlobal;
        case EntityKind::Ped:
            return a.pedGlobal;
        case EntityKind::Vehicle:
            return a.vehicleGlobal;
        }

        return 0;
    }

    size_t EntityPools::StrideFor(EntityKind kind) const
    {
        switch (kind)
        {
        case EntityKind::Object:
            return a.objectStride;
        case EntityKind::Ped:
            return a.pedStride;
        case EntityKind::Vehicle:
            return a.vehicleStride;
        }

        return 0;
    }

    bool EntityPlaceable::valid() const
    {
        return pools.Get(kind, handle) != nullptr;
    }

    Vec3 EntityPlaceable::transformPoint(const Vec3& offset) const
    {
        void* entity = pools.Get(kind, handle);
        if (entity == nullptr) return Vec3();

        const uintptr_t entityAddress = reinterpret_cast<uintptr_t>(entity);
        uintptr_t matrix              = entityAddress + layout.matrixOffset;

        if (layout.matrixPointer != 0)
        {
            // Like CPlaceable::GetMatrix: follow the CMatrix* once the entity is in the
            // world, otherwise use the placement fallback below.
            matrix = ReadPointer(entityAddress + layout.matrixPointer);
            if (matrix == 0)
            {
                if (layout.placement == 0) return Vec3();

                // CSimpleTransform: forward = (-sin h, cos h, 0), right = (cos h, sin h, 0).
                const Vec3 origin   = *At<Vec3>(entityAddress + layout.placement);
                const float heading = *At<float>(entityAddress + layout.placement + sizeof(Vec3));
                if (!IsFiniteVector(origin) || !std::isfinite(heading)) return Vec3();

                const Vec3 right(std::cos(heading), std::sin(heading), 0.0f);
                const Vec3 forward(-std::sin(heading), std::cos(heading), 0.0f);

                return origin + right * offset.x + forward * offset.y + Vec3(0.0f, 0.0f, offset.z);
            }
        }

        const Vec3 right   = *At<Vec3>(matrix + kMatrixRight);
        const Vec3 forward = *At<Vec3>(matrix + kMatrixForward);
        const Vec3 up      = *At<Vec3>(matrix + kMatrixUp);
        const Vec3 origin  = *At<Vec3>(matrix + kMatrixPosition);

        return origin + right * offset.x + forward * offset.y + up * offset.z;
    }
} // namespace audio::host
