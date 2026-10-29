#pragma once

#include <memory>
#include "GameState.h"

namespace audio
{
    enum class EntityKind
    {
        Object,
        Ped,
        Vehicle,
    };

    class IEntityResolver
    {
      public:
        virtual ~IEntityResolver() = default;

        // nullptr when the handle is stale, out of range or an empty pool slot.
        virtual std::unique_ptr<IPlaceable> Resolve(EntityKind kind, int handle) const = 0;
    };

    inline const char* EntityKindName(EntityKind kind)
    {
        switch (kind)
        {
        case EntityKind::Object:
            return "object";
        case EntityKind::Ped:
            return "char";
        case EntityKind::Vehicle:
            return "car";
        }

        return "entity";
    }
} // namespace audio
