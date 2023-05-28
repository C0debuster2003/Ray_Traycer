#pragma once
// could have also used #ifndef header guard but this is a cleaner implementation of the same
#include "rt_weekend.h"
#include <iostream>
#include "hittable.h"
#include "AABB.h" 
using namespace std;

// defining the class moving_Sphere
class MSphere : public hittable
{
public:
    // defining the default constructor
    MSphere();
    // defining the paramterized constructor
    MSphere(point3 cen1, point3 cen0, double time0, double time1,double radius, shared_ptr<material> mat_ptr);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
    //defining a function to return the position of the centre of the sphere at the desired time;
    //we assume that the circle moves linearly from start to finish
    point3 centre(double time) const;
private:
    point3 cen1;
    point3 cen2;
    double time1;
    double time2;
    double radius;
    shared_ptr<material> mat_ptr;
};
