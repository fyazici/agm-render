#pragma once

#include "Vector.hpp"

namespace agm
{

template<typename T = double>
struct Camera
{
    Vec3<T> position;
    Vec3<T> left, up, gaze;
    T focal_distance;
    T maximum_distance;
};

} // namespace agm
