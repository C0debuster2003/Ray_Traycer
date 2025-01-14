#include"AARect.h"
xy_rect::xy_rect(){}  //default constructor
xy_rect::xy_rect(double x0, double x1, double y0, double y1, double k, shared_ptr<material> mat_ptr){
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->k = k;
    this->mp = mat_ptr;
}

//bounding box function to define the bounding box for the rectangles
//since the bounding boxes should have a non zero dimension along all the 3 axes, we give a bit of padding
//to the plane to basically make it a cuboid
bool xy_rect::bounding_box(double time0, double time1, aabb& output_box) const{
    output_box = aabb(point3(x0,y0,k-0.0001), point3(x1,y1,k+0.0001));
    return true;
}

//defining the hit function for the rectangle class
bool xy_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
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
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}
//for the xz_rect class
xz_rect::xz_rect(){}  //default constructor
xz_rect::xz_rect(double x0, double x1, double z0, double z1, double k, shared_ptr<material> mat_ptr){
    this->x0 = x0;
    this->x1 = x1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mp = mat_ptr;
}

//bounding box function to define the bounding box for the rectangles
//since the bounding boxes should have a non zero dimension along all the 3 axes, we give a bit of padding
//to the plane to basically make it a cuboid
bool xz_rect::bounding_box(double time0, double time1, aabb& output_box) const{
    output_box = aabb(point3(x0,k-0.0001,z0), point3(x1,k+0.0001,z1));
    return true;
}

//defining the hit function for the rectangle class
bool xz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    auto t = (k-r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x()+t*r.direction().x();
    auto z = r.origin().z()+t*r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)   //means that the ray does not intersect the rectangle
        return false;
    //if the ray does actually intersect the rectangle
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}


yz_rect::yz_rect(){}  //default constructor
yz_rect::yz_rect(double y0, double y1, double z0, double z1, double k, shared_ptr<material> mat_ptr){
    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
    this->k = k;
    this->mp = mat_ptr;
}

//bounding box function to define the bounding box for the rectangles
//since the bounding boxes should have a non zero dimension along all the 3 axes, we give a bit of padding
//to the plane to basically make it a cuboid
bool yz_rect::bounding_box(double time0, double time1, aabb& output_box) const{
    output_box = aabb(point3(k-0.0001,y0,z0), point3(k+0.0001,y1,z1));
    return true;
}

//defining the hit function for the rectangle class
bool yz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    auto t = (k-r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;
    auto y = r.origin().y()+t*r.direction().y();
    auto z = r.origin().z()+t*r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)   //means that the ray does not intersect the rectangle
        return false;
    //if the ray does actually intersect the rectangle
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}