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
    Sphere() {} // default constructor
    Sphere(point3 cen, double r, shared_ptr<material> mat_ptr)
    {
        this->centre = cen;
        this->radius = r;
        this->mat_ptr = mat_ptr;
    }
    virtual bool hit(
        const ray &r, double t_min, double t_max, hit_record &rec) const override;
};
bool Sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - centre;
    auto a = dot(r.direction(), r.direction());
    auto b = 2 * dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    // finding the nearest root that lies in the acceptable range
    auto root = (-b - sqrtd) / (2 * a);
    if (root > t_max || root < t_min)
    {
        root = (-b + sqrtd) / (2 * a);
        if (root < t_min || root > t_max)
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = vec3(rec.p - centre) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
#endif