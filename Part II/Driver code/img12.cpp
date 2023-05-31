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
#include "box.h"
#include"constant_medium.h"
#include "BVH.h"
using namespace std;

hittable_list final_scene() {
    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hittable_list objects;

    objects.add(make_shared<bvh_node>(boxes1, 0, 1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    objects.add(make_shared<MSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(make_shared<Sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    objects.add(make_shared<Sphere>(
        point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)));

    auto boundary = make_shared<Sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    objects.add(boundary);
    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<Sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
    objects.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("marble1.jpg"));
    objects.add(make_shared<Sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<lambertian>(make_shared<image_texture>("marble2.jpg"));
    objects.add(make_shared<Sphere>(point3(220,280,300), 80, pertext));
    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<Sphere>(point3::random(0,165), 10, white));
    }

    objects.add(make_shared<translate>(
        make_shared<rotate_y>(
            make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
            vec3(-100,270,395)
        )
    );

    return objects;
}





hittable_list cornell_smoke() {
    hittable_list objects;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));

    objects.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    objects.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));

    return objects;
}

hittable_list cornell_box()
{
    hittable_list objects;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    objects.add(box1);

    shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    objects.add(box2);
    return objects;
}

// function to create a light source from a rectangle
hittable_list simple_light()
{
    hittable_list objects;

    auto pertext = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    objects.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<Sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(1, 1, 1));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

    return objects;
}
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
    const auto aspect_ratio = 1.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 400;
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
    switch (0)
    {
    case 1:
    {
        world = random_scene();
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
        // world.add(make_shared<Sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(color(0,1,1))));
        lookfrom = point3(-13, 2, -3);
        lookat = point3(0, 0, 0);
        vup = vec3(0, 1, 0);
        background = color(0.7, 0.8, 1.00);
        break;
    }
    case 5:
    {
        world = simple_light();
        background = color(0, 0, 0);
        lookfrom = point3(26, 3, 6);
        lookat = point3(0, 2, 0);
        vup = vec3(0, 1, 0);
        vfov = 20.0;
        break; // if break is not given, then fall through happens
    }
    case 6:
    {
        world = cornell_box();
        samples_per_pixel = 300;
        background = color(0, 0, 0);
        lookfrom = point3(278, 278, -800);
        lookat = point3(278, 278, 0);
        vup = vec3(0, 1, 0);
        vfov = 40.0;
        break;
    }
    case 7:
        world = cornell_smoke();
        samples_per_pixel = 200;
        lookfrom = point3(278, 278, -800);
        lookat = point3(278, 278, 0);
        vfov = 40.0;
        vup = vec3(0,1,0);
        break;
    default:
        case 8:
            world = final_scene();
            samples_per_pixel = 2000;
            background = color(0,0,0);
            lookfrom = point3(478, 278, -600);
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            vup = vec3(0,1,0);
            break;}
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
    //for 8 concurrent threads
    fstream file1, file2, file3, file4, file5, file6, file7, file8;
    file1.open("t1.txt", ios::out);
    file1.open("t2.txt", ios::out);
    file1.open("t3.txt", ios::out);
    file1.open("t4.txt", ios::out);
    file1.open("t5.txt", ios::out);
    file1.open("t6.txt", ios::out);
    file1.open("t7.txt", ios::out);
    file1.open("t8.txt", ios::out);
    thread t1(run, "t1.txt", 800, 701);
    thread t2(run, "t2.txt", 701, 601);
    thread t3(run, "t3.txt", 601, 501);
    thread t4(run, "t4.txt", 501, 401);
    thread t5(run, "t5.txt", 401, 301);
    thread t6(run, "t6.txt", 301, 201);
    thread t7(run, "t7.txt", 201, 101);
    thread t8(run, "t8.txt", 101, 0);
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