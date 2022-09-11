#pragma once

#include <vector>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace agm
{

template<typename C>
void surface_to_file(const Surface<C> &surface, const std::string &filename)
{
    constexpr size_t channels = 3;
    const size_t len = surface.width * surface.height;
    std::vector<unsigned char> buffer;
    buffer.reserve(len);

    for (auto c: surface.data)
    {
        buffer.emplace_back((unsigned char)std::clamp(c.r * 255.0, 0.0, 255.0));
        buffer.emplace_back((unsigned char)std::clamp(c.g * 255.0, 0.0, 255.0));
        buffer.emplace_back((unsigned char)std::clamp(c.b * 255.0, 0.0, 255.0));
    }

    stbi_write_bmp(
        filename.c_str(), 
        surface.width, surface.height, channels,
        buffer.data() //, surface.width * channels
    );
}

template<>
void surface_to_file(const Surface<Color3<unsigned char>> &surface, const std::string &filename)
{
    constexpr size_t channels = 3;

    stbi_write_bmp(
        filename.c_str(), 
        surface.width, surface.height, channels,
        surface.data.data() //, surface.width * channels
    );
}

} // namespace agm
