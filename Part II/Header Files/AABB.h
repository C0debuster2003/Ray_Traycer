#pragma once
//similar to using ifndef header guard
#include"rt_weekend.h"
#include"vec3.h"
#include"Ray.h"
class aabb{
    public:
        //default constructor
        aabb();
        //parametrized constructor
        aabb(const point3& a, const point3& b);
        point3 min() const;
        point3 max() const;
        bool hit(const ray& r, double t_min, double t_max) const;
    public:
        point3 minimum;
        point3 maximum;

};
//function declaration
aabb surrounding_box(aabb box0, aabb box1);