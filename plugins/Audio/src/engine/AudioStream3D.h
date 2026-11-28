#pragma once

#include "AudioStream.h"

namespace audio
{
    // CLEO5's C3DAudioStream over the engine's placement wrapper (IPlaceable) instead of
    // CPools/CEntity, and without the SA camera globals.
    class AudioStream3D : public AudioStream
    {
      public:
        explicit AudioStream3D(const char* filepath);

        bool Is3d() const override { return true; }
        void Set3dPosition(const Vec3& pos) override;
        void Set3dSourceSize(float radius) override;
        void SetHostOwned(std::unique_ptr<IPlaceable> placeable, const Vec3& offset) override;
        void Process() override;
        float CalculateVolume() override;

      protected:
        static constexpr float Volume3DAdjust = 0.5f; // match ingame sound sources

        static double CalculateDistanceDecay(float radius, float distance);
        static float CalculateDirectionDecay(const Vec3& listenerDir, const Vec3& relativePos);

        // source position relative to the listener
        struct SourceFrame
        {
            Vec3 relative;
            float distance = 0.0f;
            float blend    = 1.0f;
        };
        SourceFrame EvaluateSource() const;

        void UpdatePosition();

        IPlaceable* host = nullptr;
        std::unique_ptr<IPlaceable> ownedHost; // keeps the game-memory reader alive
        Vec3 offset   = {0.0f, 0.0f, 0.0f};    // relative to host, or the world position
        float radius  = 0.5f;
        bool placed   = false;
        Vec3 position = {0.0f, 0.0f, 0.0f};
        Vec3 velocity = {0.0f, 0.0f, 0.0f};
    };
} // namespace audio
