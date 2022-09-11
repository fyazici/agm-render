#pragma once

#include <vector>
#include "Color.hpp"

namespace agm
{

template<typename C = Color3<unsigned char>>
struct Surface
{
    Surface(size_t width_, size_t height_)
        : width{width_}, height{height_}, data(width * height)
    {
    }

    C &at(const size_t i, const size_t j)
    {
        return data[static_cast<size_t>(width * i + j)];
    }

    size_t width, height;
    std::vector<C> data;
};


} // namespace agm
