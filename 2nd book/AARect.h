//axis aligned rectangles class
#pragma once
#include "rt_weekend.h"
#include"hittable.h"
//this class implements the hittable class as this will also be a hittable
class AARect:public hittable{
    //defining the members of the class which provide a complete description of the class
    public:
        double x0, x1;  //this is the range of the x values of the rectangle
        double y0, y1;  //this is the range of y values of the rectangle
        double k;       //z=k defines the plane of the rectangle
        shared_ptr<material> mat_ptr;  //specifies the material type of the rectangle

        //constructors
        AARect();
        AARect(double x0, double x1, double y0, double y1, double k, shared_ptr<material> mat_ptr);
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};
