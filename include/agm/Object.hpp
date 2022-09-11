#pragma once

#include "Vector.hpp"
#include "Material.hpp"

namespace agm
{

template<typename T = double>
struct Object
{
    virtual auto map(const Vec3<T> &) const noexcept -> std::pair<T, Material<>> = 0;
};

} // namespace agm
