#ifndef SPHERE_H
#define SPHERE_H
using namespace std;
#include <iostream>
#include "Ray.h"
#include "vec3.h"
#include "hittable.h"
class Sphere : public hittable
{
public:
    point3 centre;
    double radius;
    shared_ptr<material> mat_ptr;
    Sphere(); // default constructor
    Sphere(point3 cen, double r, shared_ptr<material> mat_ptr);
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
private:
static void get_sphere_uv(const point3&p, double&u, double& v);
};
#endif