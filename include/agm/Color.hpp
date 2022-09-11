#pragma once

namespace agm
{

template<typename T = float>
struct Color3
{
    T r, g, b;

    typedef T value_type;

    auto operator+(const Color3<T> &rhs) const noexcept -> Color3<T>
    {
        return { r + rhs.r, g + rhs.g, b + rhs.b };
    }

    auto operator*(const T &rhs) const noexcept -> Color3<T>
    {
        return { r * rhs, g * rhs, b * rhs };
    }

    auto operator*(const Color3<T> &rhs) const noexcept -> Color3<T>
    {
        return { r * rhs.r, g * rhs.g, b * rhs.b };
    }

    auto operator+=(const Color3<T> &rhs) noexcept -> Color3<T>&
    {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }

    operator Color3<unsigned char>() const noexcept 
    {
        return {
            (unsigned char)std::clamp(r * 255.0, 0.0, 255.0),
            (unsigned char)std::clamp(g * 255.0, 0.0, 255.0),
            (unsigned char)std::clamp(b * 255.0, 0.0, 255.0)
        };
    }
};

} // namespace agm
