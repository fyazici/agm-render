#pragma once

#include <tuple>
#include <optional>

#include "Color.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Surface.hpp"

namespace agm
{

constexpr size_t RAYMARCH_MAX_STEPS = 256;

template<typename T = double>
constexpr T RAYMARCH_EPSILON = 1e-6;

template<typename T = double>
constexpr T RAYMARCH_OCCLUSION_MAX = 100;

template<typename T = double, typename C = Color3<double>, typename S = Surface<>>
void render(
    const Camera<T> &camera, 
    const Object<T> &object,
    const Light<T, C> &light,
    const C &background,
    S &surface
) {
    #ifdef AGM_USE_OPENMP
    #pragma omp parallel for
    #endif
    for (size_t i = 0; i < surface.height; ++i)
    {
        for (size_t j = 0; j < surface.width; ++j)
        {
            C frag_color;
            auto viewport_pos = get_viewport_pos(i, j, camera, surface);
            auto ray = get_camera_ray(viewport_pos, camera);
            
            auto march_result = do_raymarch(ray, object, camera.far);
            if (march_result)
            {
                auto [p, m] = march_result.value();
                auto normal = estimate_normal(p, object);

                auto light_dir = (light.position - p).normalize();
                auto occlusion = do_raymarch(
                    { p + normal * 2 * RAYMARCH_EPSILON<>, light_dir }, 
                    object, 
                    RAYMARCH_OCCLUSION_MAX<T>
                );
                
                typename C::value_type shadow = 0;

                if (occlusion)
                {
                    shadow = 0.5;
                }

                auto dot_1 = normal.dot(light_dir);
                auto diffuse_mix = light.color * std::max((T)0, dot_1);

                auto reflect_dir = normal.reflect(light_dir);
                auto dot_2 = reflect_dir.dot(-ray.direction);
                auto specular_mix = light.color * std::pow(std::max(T(0), dot_2), 4);

                frag_color = m.ambient + (m.diffuse * diffuse_mix + m.specular * specular_mix) * (1 - shadow);
            }
            else
                frag_color = background;
            
            surface.at(i, j) = frag_color;
        }
    }
}

template<typename T = double, typename C>
auto get_viewport_pos(size_t i, size_t j, const Camera<T> &camera, const Surface<C> &surface) -> Vec2<T>
{
    const auto viewport = camera.viewport;
    const auto vw = viewport.right - viewport.left;
    const auto vh = viewport.top - viewport.bottom;
    if (vw < 0 || vh < 0) exit(-1);

    return { 
        viewport.left + ((T)j / surface.width)  * vw, 
        viewport.top - ((T)i / surface.height) * vh 
    };
}

template<typename T = double>
auto get_camera_ray(const Vec2<T> viewport_pos, const Camera<T> &camera) -> Ray<T>
{   
    auto dir = camera.gaze + (camera.up * viewport_pos.y + camera.right * viewport_pos.x) / camera.near;
    return { camera.position, dir.normalize() };
}

template<typename T = double>
auto do_raymarch(const Ray<T> &ray, const Object<T> &object, const T &far) -> std::optional<std::pair<Vec3<T>, Material<>>>
{
    Vec3<T> p = ray.position;
    T distance_marched = 0;

    for (size_t i = 0; i < RAYMARCH_MAX_STEPS; ++i)
    {
        auto [d, m] = object.map(p);
        p = p + ray.direction * d;
        if (d < RAYMARCH_EPSILON<T>)
            return { { p, m } };
        distance_marched += d;
        if (distance_marched > far)
            break;
    }

    return {};
}

template<typename T = double>
auto estimate_normal(const Vec3<T> position, const Object<T> &object) -> Vec3<T>
{
    constexpr Vec3<T> dx = { RAYMARCH_EPSILON<T>, 0, 0 };
    constexpr Vec3<T> dy = { 0, RAYMARCH_EPSILON<T>, 0 };
    constexpr Vec3<T> dz = { 0, 0, RAYMARCH_EPSILON<T> };

    auto mxp = object.map(position + dx).first;
    auto mxn = object.map(position - dx).first;
    auto myp = object.map(position + dy).first;
    auto myn = object.map(position - dy).first;
    auto mzp = object.map(position + dz).first;
    auto mzn = object.map(position - dz).first;

    return Vec3<T>{ mxp - mxn, myp - myn, mzp - mzn }.normalize();
}

} // namespace agm
