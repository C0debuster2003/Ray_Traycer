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
#include "stb_image.h"
#include "Texture.h"
#include "AARect.h"
using namespace std;

// function to create a light source from a rectangle
hittable_list simple_light()
{
    hittable_list world;
    auto pertext = make_shared<noise_texture>();
    world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<Sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));
    auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
    world.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
    return world;
}
hittable_list earth()
{
    auto earth_texture = make_shared<image_texture>("D:\\TRayCer\\2nd book\\earthmap.jpg"); // using the filename vala constructor
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(point3(0, 0, 0), 2, earth_surface);
    return hittable_list(globe);
}
color ray_color(const ray &r, const color &background, const hittable &world, int depth)
{
    hit_record rec;
    // if we have exceeded the number of child rays allowed, then do not track the ray any longer
    if (depth <= 0)
        return color(0, 0, 0);
    // if the ray hits nothing, then just return the background color
    if (!world.hit(r, 0.001, infinity, rec))
        return background;
    else
    {
        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return emitted;
        auto temp = ray_color(scattered, background, world, depth - 1);
        return emitted + color(attenuation[0] * temp[0], attenuation[1] * temp[1], attenuation[2] * temp[2]);
    }
}
void run(string path, int s_j, int e_j)
{
    // file to which the data is to be written
    ofstream f(path, std::ofstream::out);

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 50;
    const int max_depth = 20;
    const double gamma = 2.0; // using gamma 1.9
    // gamma basically results in color^(1/gamma)
    // so, if gamma is 1 then the colours are as such

    // declaring some camera parameters
    auto vfov = 20.0;
    auto aperture = 0.0;
    point3 lookfrom;
    point3 lookat;
    vec3 vup;
    // initializing the background color variable
    color background(0, 0, 0);

    // world
    hittable_list world;
    switch (5)
    {
    case 1:
    {
        // world = random_scene();
        lookfrom = point3(13, 2, 3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        aperture = 0.1;
        background = color(0.7, 0.8, 1.00);
        break;
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
        background = color(0.7, 0.8, 1.00);
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
        background = color(0.7, 0.8, 1.00);
        break;
    }
    case 4:
    {
        world = earth();
        lookfrom = point3(-13, 2, -3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        background = color(0.7, 0.8, 1.00);
        break;
    }
    case 5:
    {
        world = simple_light();
        background = color(0.0, 0.0, 0.0);
        lookfrom = point3(26, 3, 6);
        lookat = point3(0, 2, 0);
        vfov = 20.0;
        vup = vec3(0, 1, 0);
        break; // if break is not given, then fall through happens
    }
    default:
    case 6:
    {
        // world = cornell_box();
        background = color(0, 0, 0);
        lookfrom = point3(278, 278, -800);
        lookat = point3(278, 278, 0);
        vfov = 40.0;
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
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(f, pixel_color, samples_per_pixel, gamma);
        }
    }
    f.close();
    std::cerr << "\nDone.\n";
}
int main()
{
    fstream file1, file2, file3, file4, file5, file6, file7, file8;
    file1.open("t1.txt", ios::out);
    file1.open("t2.txt", ios::out);
    file1.open("t3.txt", ios::out);
    file1.open("t4.txt", ios::out);
    file1.open("t5.txt", ios::out);
    file1.open("t6.txt", ios::out);
    file1.open("t7.txt", ios::out);
    file1.open("t8.txt", ios::out);
    thread t1(run, "t1.txt", 450, 401);
    thread t2(run, "t2.txt", 401, 343);
    thread t3(run, "t3.txt", 343, 287);
    thread t4(run, "t4.txt", 287, 230);
    thread t5(run, "t5.txt", 230, 173);
    thread t6(run, "t6.txt", 173, 116);
    thread t7(run, "t7.txt", 116, 58);
    thread t8(run, "t8.txt", 58, 0);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file6.close();
    file7.close();
    file8.close();
}