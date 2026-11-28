#include "AudioStream3D.h"

#include <algorithm>
#include <cmath>

#include "Log.h"
#include "SoundSystem.h"

namespace audio
{
    AudioStream3D::AudioStream3D(const char* filepath)
    {
        if (!Open(filepath, BASS_SAMPLE_3D | BASS_SAMPLE_MONO)) return;

        BASS_ChannelSet3DAttributes(streamInternal, BASS_3DMODE_NORMAL, -1.0f, -1.0f, -1, -1, -1.0f);
        BASS_ChannelSetAttribute(streamInternal, BASS_ATTRIB_VOL, 0.0f); // muted until placed
    }

    void AudioStream3D::Set3dPosition(const Vec3& pos)
    {
        host = nullptr;
        ownedHost.reset();
        offset = pos;
    }

    void AudioStream3D::Set3dSourceSize(float newRadius)
    {
        radius = std::max(newRadius, 0.01f);
    }

    void AudioStream3D::SetHostOwned(std::unique_ptr<IPlaceable> placeable, const Vec3& newOffset)
    {
        ownedHost = std::move(placeable);
        host      = ownedHost.get();
        offset    = newOffset;
    }

    void AudioStream3D::Process()
    {
        UpdatePosition();
        AudioStream::Process();

        const SourceFrame source = EvaluateSource();

        // Pan towards whichever side of the listener the source is on.
        const float sign     = Dot(SoundSystem::direction, source.relative) > 0.0f ? 1.0f : -1.0f;
        const Vec3 centerPos = SoundSystem::position + SoundSystem::direction * source.distance * sign;

        const Vec3 percPos = Lerp(position, centerPos, source.blend);
        const Vec3 percVel = Lerp(velocity, SoundSystem::velocity, source.blend);

        auto bassPercPos = ToBass(percPos);
        auto bassPercVel = ToBass(percVel);
        BASS_ChannelSet3DPosition(streamInternal, &bassPercPos, nullptr, &bassPercVel);
    }

    float AudioStream3D::CalculateVolume()
    {
        if (!placed) return 0.0f;

        const SourceFrame source = EvaluateSource();

        double vol = Volume3DAdjust * MasterVolume(type);

        vol *= CalculateDistanceDecay(radius, source.distance);
        vol *= Lerp(CalculateDirectionDecay(SoundSystem::direction, source.relative), 1.0f, source.blend);
        vol *= volume.value();

        return static_cast<float>(vol);
    }

    AudioStream3D::SourceFrame AudioStream3D::EvaluateSource() const
    {
        SourceFrame source;
        source.relative = position - SoundSystem::position;
        source.distance = source.relative.normalizeAndMagnitude();

        // Blends the source from inside its radius (0) to fully outside (1); the same
        // factor softens the volume and the panning.
        source.blend = static_cast<float>(CalculateDistanceDecay(radius * 5.0f, source.distance * 5.0f));
        return source;
    }

    double AudioStream3D::CalculateDistanceDecay(float radius, float distance)
    {
        distance = std::max<float>(distance - radius, 0.0f);

        // More natural feeling than the inverse-square ingame curve.
        return exp(-0.013 * pow(distance, 1.4));
    }

    float AudioStream3D::CalculateDirectionDecay(const Vec3& listenerDir, const Vec3& relativePos)
    {
        return 0.6f + 0.4f * Dot(listenerDir, relativePos); // 0.2 to 1.0
    }

    void AudioStream3D::UpdatePosition()
    {
        const Vec3 prevPos = position;

        if (host != nullptr)
        {
            if (!host->valid())
            {
                host = nullptr;
                ownedHost.reset();
                placed = false;
                Stop();
                return;
            }

            position = host->transformPoint(offset);
        }
        else
        {
            position = offset;
        }

        if (prevPos.magnitude() > 0.0f)
        {
            if (SoundSystem::timeStep > 0.0f)
            {
                velocity = position - prevPos;
                velocity /= SoundSystem::timeStep;
            }
            placed = true;
        }
        else
        {
            placed = false;
        }
    }
} // namespace audio
