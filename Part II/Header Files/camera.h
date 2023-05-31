#ifndef CAMERA_H
#define CAMERA_H

using namespace std;
#include <iostream>
#include "rt_weekend.h"
#include "vec3.h"
#include "Ray.h"

class camera
{
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time1 = 0.0;
    double time2 = 0.0;

public:
    // default constructor
    camera();
    // parametrized constructor
    camera(point3 lookfrom, point3 lookat, vec3 vup, double v_fov, double aspect_ratio, double aperture,
           double focus_distance, double _time1, double _time2);
    ray get_ray(double s, double t) const;
};
#endif