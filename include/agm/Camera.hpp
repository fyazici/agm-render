#pragma once

#include "Vector.hpp"

namespace agm
{

template<typename T = double>
struct Camera
{
    Vec3<T> position;
    Vec3<T> gaze, up, right;
    T near, far;
    struct {
        T left, top, right, bottom;
    } viewport;

    void rotate_x(T angle) noexcept
    {
        gaze = gaze.rotate_x(angle);
        up = up.rotate_x(angle);
        right = right.rotate_x(angle);
    }
};

} // namespace agm
