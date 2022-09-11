#pragma once

namespace agm
{

template<typename T = double>
struct Color3
{
    T r, g, b;

    template<typename T2>
    auto operator+(const Color3<T2> &rhs) const noexcept -> Color3<T>
    {
        return { r + rhs.r, g + rhs.g, b + rhs.b };
    }

    template<typename T2>
    auto operator*(const T2 &rhs) const noexcept -> Color3<T>
    {
        return { r * rhs, g * rhs, b * rhs };
    }

    template<typename T2>
    auto operator*(const Color3<T2> &rhs) const noexcept -> Color3<T>
    {
        return { r * rhs.r, g * rhs.g, b * rhs.b };
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
