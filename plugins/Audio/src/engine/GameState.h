#pragma once

#include <optional>
#include "Vec3.h"

namespace audio
{
    struct Camera
    {
        Vec3 position;
        Vec3 forward;
        Vec3 up;
    };

    // The game's own SFX/music sliders, 0..1; the plugin multiplies its audio.ini
    // masters by these.
    struct AudioMix
    {
        float sfxVolume   = 1.0f;
        float musicVolume = 1.0f;
    };

    // What the plugin reads from the game every frame.
    class IGameState
    {
      public:
        virtual ~IGameState() = default;
        // std::nullopt when the host cannot provide a listener.
        virtual std::optional<Camera> camera() const = 0;
        // True on the frame the camera was switched/restored, so the listener update
        // can be skipped. Hosts without the information keep false.
        virtual bool cameraJustChanged() const { return false; }
        // 1.0 is normal speed, lower is slow motion.
        virtual float timeScale() const { return 1.0f; }
        // std::nullopt when the host has no mixer; then only audio.ini decides.
        virtual std::optional<AudioMix> mix() const { return std::nullopt; }
    };

    class IPlaceable
    {
      public:
        virtual ~IPlaceable()      = default;
        virtual bool valid() const = 0;
        // Local offset -> world position.
        virtual Vec3 transformPoint(const Vec3& offset) const = 0;
    };
} // namespace audio
