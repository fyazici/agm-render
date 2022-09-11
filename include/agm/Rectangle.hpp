#pragma once

namespace agm
{

template<typename T>
struct Rectangle
{
    T left, top, right, bottom;

    constexpr static auto from_size(const Vec3<T> &center, const T &width, const T &height) noexcept -> Rectangle
    {
        return { }; // TODO: is this needed?
    }
};

} // namespace agm
