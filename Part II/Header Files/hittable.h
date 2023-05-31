#ifndef HITTABLE_H
#define HITTABLE_H
#include "Ray.h"
#include <iostream>
using namespace std;
#include"rt_weekend.h"
#include"AABB.h"
class material;

//class material;
struct hit_record
{
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat_ptr;
    //this is to store the coordinates of the hit point(point where the ray strikes the body)
    double u;
    double v;
    bool front_face;
    inline void set_face_normal(const ray &r, const vec3 &outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        this->normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;
    // this syntax basically creates a purely function
    /*A pure virtual function is a virtual function that is used when the designer of the class wants to
    force derived classes to override the function and provide their own implementation.*/
    // any class containing a purely virtual function is called an abstract class and cannot be instantiated.
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};


class translate : public hittable {
    public:
        translate(shared_ptr<hittable> p, const vec3& displacement);

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    public:
        shared_ptr<hittable> ptr;
        vec3 offset;
};


class rotate_y : public hittable {
    public:
        rotate_y(shared_ptr<hittable> p, double angle);
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
    public:
        shared_ptr<hittable> ptr;
        double sin_theta;
        double cos_theta;
        bool hasbox;
        aabb bbox;
};

#endif
