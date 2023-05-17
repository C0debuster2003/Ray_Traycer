// rendering shiny metals using multithreading
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
using namespace std;

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
            vec3 l = ray_color(scattered, world, depth - 1);
            return vec3(attenuation[0] * l[0], attenuation[1] * l[1], attenuation[2] * l[2]);
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
    const int max_depth = 50;
    const double gamma = 2.0; // using gamma 1.9
    // gamma basically results in color^(1/gamma)
    // so, if gamma is 1 then the colours are as such

    // World

hittable_list world;

auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
auto material_left   = make_shared<dielectric>(1.5);
auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

camera cam;
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