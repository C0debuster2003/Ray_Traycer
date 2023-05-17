#ifndef CAMERA_H
#define CAMERA_H

using namespace std;
#include <iostream>
#include "rt_weekend.h"

class camera
{
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;

public:
    camera()
    {
        const auto aspect_ratio = 16.0 / 9.0;
        const auto viewport_height = 2.0;
        const auto viewport_width = static_cast<int>(viewport_height * aspect_ratio);
        const auto focal_length = 1.0;
        this->origin = point3(0.0, 0.0, 0.0);
        this->horizontal = vec3(viewport_width, 0.0, 0.0);
        this->vertical = vec3(0.0, viewport_height, 0.0);
        this->lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0.0, 0.0, focal_length);
    }
    // default constructor
    camera(point3 lookfrom, point3 lookat, vec3 vup, double v_fov, double aspect_ratio, double aperture,
           double focus_distance)
    {
        double rad_vfoc = degrees_to_radians(v_fov); // v_fov is in degrees and is converted to radians
        const auto viewport_height = 2.0 * tan(rad_vfoc / 2);
        const auto viewport_width = (viewport_height * aspect_ratio);
        const auto focal_length = 1.0;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;
        lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const
    {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset);}
    };
#endif