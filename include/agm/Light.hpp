#pragma once

#include "Vector.hpp"
#include "Color.hpp"

namespace agm
{

template<typename T = float, typename C = Color3<>>
struct Light
{
    Vec3<T> position;
    C color;
};

} // namespace agm
