#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include "engine/Vec3.h"

namespace audio::host
{

    inline constexpr size_t kPointerSize = sizeof(uintptr_t);

    template <typename T> inline const T* At(uintptr_t address)
    {
        return reinterpret_cast<const T*>(address);
    }

    inline uintptr_t ReadPointer(uintptr_t address)
    {
        return *At<uintptr_t>(address);
    }

    inline bool IsFiniteVector(const Vec3& v)
    {
        return std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z);
    }
} // namespace audio::host
