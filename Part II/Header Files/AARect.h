//axis aligned rectangles class
#pragma once
#include "rt_weekend.h"
#include"hittable.h"
//this class implements the hittable class as this will also be a hittable
class xy_rect:public hittable{
    //defining the members of the class which provide a complete description of the class
    public:
        double x0, x1;  //this is the range of the x values of the rectangle
        double y0, y1;  //this is the range of y values of the rectangle
        double k;       //z=k defines the plane of the rectangle
        shared_ptr<material> mp;  //specifies the material type of the rectangle

        //constructors
        xy_rect();
        xy_rect(double x0, double x1, double y0, double y1, double k, shared_ptr<material> mat_ptr);
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};
class xz_rect:public hittable{
    //defining the members of the class which provide a complete description of the class
    public:
        double x0, x1;  //this is the range of the x values of the rectangle
        double z0, z1;  //this is the range of y values of the rectangle
        double k;       //z=k defines the plane of the rectangle
        shared_ptr<material> mp;  //specifies the material type of the rectangle

        //constructors
        xz_rect();
        xz_rect(double x0, double x1, double z0, double z1, double k, shared_ptr<material> mat_ptr);
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

class yz_rect:public hittable{
    //defining the members of the class which provide a complete description of the class
    public:
        double y0, y1;  //this is the range of the x values of the rectangle
        double z0, z1;  //this is the range of y values of the rectangle
        double k;       //z=k defines the plane of the rectangle
        shared_ptr<material> mp;  //specifies the material type of the rectangle

        //constructors
        yz_rect();
        yz_rect(double y0, double y1, double z0, double z1, double k, shared_ptr<material> mat_ptr);
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

