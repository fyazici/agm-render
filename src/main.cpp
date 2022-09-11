#include <fmt/core.h>

//#define AGM_USE_OPENMP
#include <agm/agm.h>

int main(int argc, char *argv[])
{
    constexpr size_t Width = 1000, Height = 1000;

    std::string output_filename = "output.bmp";
    if (argc > 1)
        output_filename = argv[1];

    fmt::print("Rendering to file: {}\n", output_filename);
    fmt::print("Resolution: {} x {} px\n", Width, Height);

    fmt::print("Setting up camera\n");
    agm::Camera camera1;
    {
        camera1.position = {0, 0, -1};
        camera1.left = {-1, 0, 0};
        camera1.up = {0, 1, 0};
        camera1.gaze = {0, 0, 1};
        camera1.focal_distance = 1;
        camera1.maximum_distance = 100;
    }
    
    fmt::print("Setting up scene\n");
    agm::geometry::Sphere sphere1;
    {
        sphere1.center = { 0, 0, 1 };
        sphere1.radius = 1;
        sphere1.material.ambient = {0.05, 0.05, 0.05};
        sphere1.material.diffuse = {1.0, 0.0, 0.0};
        sphere1.material.specular = {1.0, 0.8, 0.8};
    }

    agm::geometry::Sphere sphere2;
    {
        sphere2.center = { -0.5, 0, 0.4 };
        sphere2.radius = 0.5;
        sphere2.material.ambient = {0.05, 0.05, 0.05};
        sphere2.material.diffuse = {0.0, 1.0, 0.0};
        sphere2.material.specular = {1.0, 1.0, 1.0};
    }

    auto union1 = agm::geometry::Union(sphere1, sphere2);
    auto difference1 = agm::geometry::Difference(sphere1, sphere2);
    auto distort1 = agm::geometry::Distort(difference1,
        [](auto p, auto d) { 
            return d + 0.05 * std::sin(10 * p.x) * std::sin(10 * p.y) * std::sin(10 * p.z); 
        }
    );

    auto scene1 = distort1;

    fmt::print("Setting up light source\n");
    agm::Light light1;
    {
        light1.position = {1, 1, -1};
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
