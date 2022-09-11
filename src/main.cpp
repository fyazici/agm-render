#include <fmt/core.h>
#include <memory>

#define AGM_USE_OPENMP
#include <agm/agm.h>

auto create_scene(agm::ObjectFactory &factory) -> agm::Object<> *
{
    auto sphere1 = factory.make<agm::geometry::Sphere<>>();
    {
        sphere1->center = { 0.5, 0, 1 };
        sphere1->radius = 1;
        sphere1->material.ambient = {0.0, 0.0, 0.0};
        sphere1->material.diffuse = {1.0, 0.0, 0.0};
        sphere1->material.specular = {1.0, 0.8, 0.8};
    }

    auto sphere2 = factory.make<agm::geometry::Sphere<>>();
    {
        sphere2->center = { -0.2, 0, 0.7 };
        sphere2->radius = 1;
        sphere2->material.ambient = {0.05, 0.05, 0.05};
        sphere2->material.diffuse = {0.0, 0.0, 1.0};
        sphere2->material.specular = {1.0, 1.0, 1.0};
    }

    //auto union1 = factory.make<agm::geometry::Union<>>(sphere1, sphere2);

    auto difference1 = factory.make<agm::geometry::Difference<>>(sphere1, sphere2);
    
    //auto intersection1 = factory.make<agm::geometry::Intersection<>>(sphere1, sphere2);

    /*
    auto wiggle_fn = [](agm::Vec3<float> p, float d) { 
        return d + 0.02 * std::sin(20 * p.x);// * std::sin(20 * p.y) * std::sin(20 * p.z); 
    };

    auto distort1 = factory.make<agm::geometry::Distort<decltype(wiggle_fn)>>(difference1, wiggle_fn);
    */

    auto plane1 = factory.make<agm::geometry::InfinitePlane<>>();
    {
        plane1->pos = { 0, 0, 0 };
        plane1->normal = agm::Vec3<>{ 0, 1, 0 }.normalize();
        plane1->material.ambient = {0.05, 0.05, 0.05};
        plane1->material.diffuse = {0.0, 1.0, 0.0};
        plane1->material.specular = {0.2, 0.2, 0.2};
    }

    auto union2 = factory.make<agm::geometry::Union<>>(difference1, plane1);
    
    return union2;
}

int main(int argc, char *argv[])
{
    constexpr size_t Width = 4000, Height = 4000;

    std::string output_filename = "output.bmp";
    if (argc > 1)
        output_filename = argv[1];

    fmt::print("Rendering to file: {}\n", output_filename);
    fmt::print("Resolution: {} x {} px\n", Width, Height);

    fmt::print("Setting up camera\n");
    agm::Camera camera1;
    {
        camera1.position = {0, 1, -1};
        camera1.gaze = {0, 0, 1};
        camera1.up = {0, 1, 0};
        camera1.right = {1, 0, 0};
        camera1.rotate_x(-30 * M_PI / 180);

        camera1.near = 1;
        camera1.far = 1000;
        camera1.viewport = { -1, 1, 1, -1 };
    }
    
    fmt::print("Setting up scene\n");

    agm::ObjectFactory factory1;
    auto scene1 = create_scene(factory1);

    fmt::print("Setting up light source\n");
    agm::Light light1;
    {
        light1.position = {2, 2, 0};
        light1.color = {0.96, 0.91, 0.60};
    }

    fmt::print("Setting up render target\n");
    agm::Surface surface1(Width, Height);
    {
    }

    fmt::print("Rendering scene\n");
    agm::render(camera1, scene1, light1, {0, 0, 0}, surface1);

    fmt::print("Saving surface to file\n");
    agm::surface_to_file(surface1, output_filename);

    fmt::print("Complete\n");

    return 0;
}
