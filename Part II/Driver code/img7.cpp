// rendering bouncing spheres (using motion blur)
#include "camera.h"
#include "rt_weekend.h"
#include "Color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "Sphere.h"
#include <iostream>
#include "material.h"
#include <thread>
#include <fstream>
#include "MSphere.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include "Texture.h"
using namespace std;
hittable_list earth()
{
    auto earth_texture = make_shared<image_texture>("D:\\TRayCer\\2nd book\\earthmap.jpg"); // using the filename vala constructor
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(point3(0, 0, 0), 2, earth_surface);
    return hittable_list(globe);
}
hittable_list random_scene()
{
    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto a = color::random();
                    auto b = color::random();
                    auto albedo = vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0, .5), 0);
                    world.add(make_shared<MSphere>(center, center, 0.0, 1.0, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;
    if (depth <= 0)
        return color(0, 0, 0);
    // 0 means that the lines intersect the circle
    // we use 0.001 to get rid of shadow acne
    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            vec3 k = ray_color(scattered, world, depth - 1);
            return vec3(attenuation[0] * k[0], attenuation[1] * k[1], attenuation[2] * k[2]);
        }
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
void run(string path, int s_j, int e_j)
{
    // file to which the data is to be written
    ofstream f(path, std::ofstream::out);

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 30;
    const double gamma = 2.0; // using gamma 1.9
    // gamma basically results in color^(1/gamma)
    // so, if gamma is 1 then the colours are as such

    // declaring some camera parameters
    auto vfov = 20.0;
    auto aperture = 0.0;
    point3 lookfrom;
    point3 lookat;
    vec3 vup;

    // world
    hittable_list world;
    switch (0)
    {
    case 1:
    {
        world = random_scene();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        aperture = 0.1;
    }
    case 2:
    {
        // to make the colour texture
        auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
        world.add(make_shared<Sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
        world.add(make_shared<Sphere>(point3(0, +10, 0), 10, make_shared<lambertian>(checker)));
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        break;
    }
    case 3:
    {
        auto pertext = make_shared<noise_texture>();
        world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
        world.add(make_shared<Sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        break;
    }
    default:
    case 4:
    {
        world = earth();
        //world.add(make_shared<Sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(color(0,1,1))));
        lookfrom = point3(-13, 2, -3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        break;
    }
    }
    // camera
    auto dist_to_focus = 10.0;

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    // Render

    f << "P3\n"
      << image_width << " " << image_height << "\n255\n";

    for (int j = s_j - 1; j >= e_j; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(f, pixel_color, samples_per_pixel, gamma);
        }
    }
    f.close();
    std::cerr << "\nDone.\n";
}
int main()
{
    thread t1(run, "D:\\TRayCer\\t1.txt", 450, 401);
    thread t2(run, "D:\\TRayCer\\t2.txt", 401, 343);
    thread t3(run, "D:\\TRayCer\\t3.txt", 343, 287);
    thread t4(run, "D:\\TRayCer\\t4.txt", 287, 230);
    thread t5(run, "D:\\TRayCer\\t5.txt", 230, 173);
    thread t6(run, "D:\\TRayCer\\t6.txt", 173, 116);
    thread t7(run, "D:\\TRayCer\\t7.txt", 116, 58);
    thread t8(run, "D:\\TRayCer\\t8.txt", 58, 0);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}