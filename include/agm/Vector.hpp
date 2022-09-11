#pragma once

#include <cmath>

namespace agm
{

template<typename T = float>
struct Vec2
{
    T x, y;
};

template<typename T = float>
struct Vec3
{
    T x, y, z;

    auto norm2() const noexcept -> T
    {
        return x * x + y * y + z * z; 
    }

    auto norm() const noexcept -> T
    { 
        return sqrt(norm2());
    }

    auto normalize() const noexcept -> Vec3<T>
    {
        auto d = norm();
        return { x / d, y / d, z / d };
    }

    template<typename T2>
    auto dot(const Vec3<T2> &rhs) const noexcept -> T
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    template<typename T2>
    auto reflect(const Vec3<T2> &rhs) const noexcept -> Vec3<T>
    {
        // assume *this is normalized
        auto d = dot(rhs);
        if (d < 1e-6)
            return -(rhs.normalize());
        auto p = rhs / dot(rhs);
        auto q = (*this) * 2 - p;
        return q.normalize();
    }

    template<typename T2>
    auto rotate_x(const T2 angle) const noexcept -> Vec3<T>
    {
        auto c = std::cos(angle), s = std::sin(angle);
        return { x, y * c + z * s, z * c - y * s};
    }

    template<typename T2>
    auto operator+(const Vec3<T2> &rhs) const noexcept -> Vec3<T>
    {
        return { x + rhs.x, y + rhs.y, z + rhs.z };
    }

    template<typename T2>
    auto operator-(const Vec3<T2> &rhs) const noexcept -> Vec3<T>
    {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }

    auto operator-() const noexcept -> Vec3<T>
    {
        return { -x, -y, -z };
    }

    template<typename T2>
    auto operator*(const T2 &rhs) const noexcept -> Vec3<T>
    {
        return { x * rhs, y * rhs, z * rhs };
    }

    template<typename T2>
    auto operator/(const T2 &rhs) const noexcept -> Vec3<T>
    {
        return { x / rhs, y / rhs, z / rhs };
    }
};

} // namespace agm
