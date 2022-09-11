#pragma once

#include "Color.hpp"

namespace agm
{

template <typename C = Color3<>>
struct Material
{
    C ambient, diffuse, specular;
};

} // namespace agm
