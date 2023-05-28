#include"AARect.h"
AARect::AARect(){}  //default constructor
AARect::AARect(double x0, double x1, double y0, double y1, double k, shared_ptr<material> mat_ptr){
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->k = k;
    this->mat_ptr = mat_ptr;
}

//bounding box function to define the bounding box for the rectangles
//since the bounding boxes should have a non zero dimension along all the 3 axes, we give a bit of padding
//to the plane to basically make it a cuboid
bool AARect::bounding_box(double time0, double time1, aabb& output_box) const{
    output_box = aabb(point3(x0,y0,k-0.0001), point3(x1,y1,k+0.0001));
    return true;
}

//defining the hit function for the rectangle class
bool AARect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    auto t = (k-r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x()+t*r.direction().x();
    auto y = r.origin().y()+t*r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)   //means that the ray does not intersect the rectangle
        return false;
    //if the ray does actually intersect the rectangle
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = this->mat_ptr;
    rec.p = r.at(t);
    return true;
}