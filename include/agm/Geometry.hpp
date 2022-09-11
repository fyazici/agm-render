#pragma once

#include <memory>

#include "Vector.hpp"
#include "Material.hpp"
#include "Object.hpp"

namespace agm::geometry
{

template<typename T = double>
struct Sphere: public Object<T>
{
    Sphere()
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        return { (p - center).norm() - radius, material };
    }

    Vec3<T> center;
    T radius;
    Material<> material;
};


template<typename T = double>
struct InfinitePlane: public Object<T>
{
    InfinitePlane()
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        return { (p - pos).dot(normal), material };
    }

    Vec3<T> pos, normal;
    Material<> material;
};

template<typename T = double>
struct Union: public Object<T>
{
    Union(const Object<T> * const obj1_, const Object<T> * const obj2_) 
        : obj1{obj1_}, obj2{obj2_}
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        auto d1m1 = obj1->map(p);
        auto d2m2 = obj2->map(p);

        if (d1m1.first < d2m2.first)
            return d1m1;
        else
            return d2m2;
    }

    const Object<T> * const obj1;
    const Object<T> * const obj2;
};

template<typename T = double>
struct Difference: public Object<T>
{
    Difference(const Object<T> * const obj1_, const Object<T> * const obj2_) 
        : obj1{obj1_}, obj2{obj2_}
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        auto [d1, m1] = obj1->map(p);
        auto [d2, m2] = obj2->map(p);

        if (d1 > -d2)
            return {d1, m1};
        else
            return {-d2, m1};
    }

    const Object<T> * const obj1;
    const Object<T> * const obj2;
};

template<typename DistortFn, typename T = double>
struct Distort: public Object<T>
{
    Distort(const Object<T> * const obj_, DistortFn distort_fn_) 
        : obj{obj_}, distort_fn{distort_fn_}
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        auto [d, m] = obj->map(p);
        return { distort_fn(p, d), m };
    }

    const Object<T> * const obj;
    DistortFn distort_fn;
};

} // namespace geometry
