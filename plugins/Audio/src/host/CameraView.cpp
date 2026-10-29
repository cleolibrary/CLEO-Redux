#include "CameraView.h"

#include <cmath>
#include "Memory.h"

namespace audio::host
{
    namespace
    {
        bool IsUnitVector(const Vec3& v);

        bool IsUnitVector(const Vec3& v)
        {
            const float lengthSquared = v.magnitudeSquared();
            return lengthSquared > 0.9f && lengthSquared < 1.1f;
        }
    } // namespace

    std::optional<Camera> CameraView::GetFrame() const
    {
        if (a.cameraObject != 0) return ReadActiveCam();
        if (a.camera != 0) return ReadPlacedMatrix();

        return std::nullopt;
    }

    bool CameraView::JustChanged() const
    {
        const uintptr_t camera = Addr(a.camera);
        if (camera == 0) return false;

        return *At<bool>(camera + a.justSwitched) || *At<bool>(camera + a.justRestored);
    }

    std::optional<Camera> CameraView::ReadPlacedMatrix() const
    {
        const uintptr_t matrix = Addr(a.camera) + a.cameraMatrix;

        Camera camera;
        camera.position = *At<Vec3>(matrix + kMatrixPosition);
        camera.forward  = *At<Vec3>(matrix + kMatrixForward);
        camera.up       = *At<Vec3>(matrix + kMatrixUp);

        if (!IsUnitVector(camera.forward) || !IsUnitVector(camera.up)) return std::nullopt;

        return camera;
    }

    std::optional<Camera> CameraView::ReadActiveCam() const
    {
        const UnrealCamLayout& cam   = a.cam;
        const uintptr_t cameraObject = Addr(a.cameraObject);

        if (cam.array == 0 || cam.stride == 0) return std::nullopt;

        const uint8_t activeCam = *reinterpret_cast<const uint8_t*>(cameraObject + cam.activeCam);
        if (activeCam >= kUnrealCamCount) return std::nullopt;

        const uintptr_t entry = cameraObject + cam.array + cam.stride * activeCam;
        const Vec3 position   = *At<Vec3>(entry + cam.source);
        Vec3 forward          = *At<Vec3>(entry + cam.front);
        const Vec3 up         = *At<Vec3>(entry + cam.up);

        if (!IsFiniteVector(position) || !IsFiniteVector(up)) return std::nullopt;

        // m_vecFront is the unit look direction; a zero-length one means the frame is
        // not ready (mode switch, front end).
        const float frontLength = forward.normalizeAndMagnitude();
        if (!std::isfinite(frontLength) || frontLength < 0.5f) return std::nullopt;

        // BASS wants a unit up perpendicular to the direction, and some modes leave
        // m_vecUp at zero.
        Vec3 right        = Cross(forward, up);
        float rightLength = right.normalizeAndMagnitude();
        if (!std::isfinite(rightLength) || rightLength < 0.01f)
        {
            right       = Cross(forward, Vec3(0.0f, 0.0f, 1.0f));
            rightLength = right.normalizeAndMagnitude();
            if (!std::isfinite(rightLength) || rightLength < 0.01f) return std::nullopt;
        }

        Camera camera;
        camera.position = position;
        camera.forward  = forward;
        camera.up       = Cross(right, forward);
        return camera;
    }
} // namespace audio::host
