#pragma once

#include <vector>

#include "Vector.hpp"
#include "Material.hpp"

namespace agm
{

template<typename T = double>
struct Object
{
    virtual auto map(const Vec3<T> &) const noexcept -> std::pair<T, Material<>> = 0;
    virtual ~Object() = default;
};

struct ObjectFactory
{
    std::vector<agm::Object<> *> storage;

    template<typename T, typename ...Args>
    auto make(Args ...args) -> T *
    {
        auto obj = new T(std::forward<Args>(args)...);
        storage.emplace_back(obj);
        return obj;
    }

    virtual ~ObjectFactory()
    {
        for (auto obj: storage)
            delete obj;
    }
};

} // namespace agm
