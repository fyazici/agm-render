#pragma once

#include "Vector.hpp"

namespace agm
{

template<typename T = float>
struct Ray
{
    Vec3<T> position, direction;
};

} // namespace agm
