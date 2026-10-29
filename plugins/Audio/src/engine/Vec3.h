#pragma once

#include <cmath>

namespace audio
{
    // Game coordinates: meters, X = right, Y = forward, Z = up.
    struct Vec3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vec3() = default;
        Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

        Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
        Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
        Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
        Vec3 operator/(float scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }

        Vec3& operator+=(const Vec3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        float magnitudeSquared() const { return x * x + y * y + z * z; }
        float magnitude() const { return std::sqrt(magnitudeSquared()); }

        // Returns the previous magnitude; a zero-length vector is left untouched.
        float normalizeAndMagnitude()
        {
            const float length = magnitude();
            if (length > 0.0f)
            {
                x /= length;
                y /= length;
                z /= length;
            }
            return length;
        }
    };

    inline float Dot(const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    inline Vec3 Lerp(const Vec3& a, const Vec3& b, float progress)
    {
        return a * (1.0f - progress) + b * progress;
    }

    inline float Lerp(float a, float b, float progress)
    {
        return a * (1.0f - progress) + b * progress;
    }
} // namespace audio
