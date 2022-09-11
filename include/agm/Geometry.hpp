#pragma once

#include <memory>

#include "Vector.hpp"
#include "Material.hpp"
#include "Object.hpp"

namespace agm::geometry
{

template<typename T = float>
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


template<typename T = float>
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

template<typename T = float>
struct Union: public Object<T>
{
    Union(const Object<T> * const obj1_, const Object<T> * const obj2_) 
        : obj1{obj1_}, obj2{obj2_}
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        auto [d1, m1] = obj1->map(p);
        auto [d2, m2] = obj2->map(p);

        if (d1 < d2)
            return {d1, m1};
        else
            return {d2, m2};
    }

    const Object<T> * const obj1;
    const Object<T> * const obj2;
};

template<typename T = float>
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

template<typename T = float>
struct Intersection: public Object<T>
{
    Intersection(const Object<T> * const obj1_, const Object<T> * const obj2_) 
        : obj1{obj1_}, obj2{obj2_}
    {
    }

    auto map(const Vec3<T> &p) const noexcept -> std::pair<T, Material<>> override
    {
        auto [d1, m1] = obj1->map(p);
        auto [d2, m2] = obj2->map(p);

        if (d1 > d2)
            return {d1, m1};
        else
            return {d2, m2};
    }

    const Object<T> * const obj1;
    const Object<T> * const obj2;
};

template<typename DistortFn, typename T = float>
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
