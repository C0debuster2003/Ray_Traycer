#include "MSphere.h"
MSphere::MSphere() {} // default constructor
MSphere::MSphere(point3 cen1, point3 cen0, double time0, double time1, double radius, shared_ptr<material> mat_ptr)
{
    this->cen1 = cen0;
    this->cen2 = cen1;
    this->time1 = time0;
    this->time2 = time1;
    this->mat_ptr = mat_ptr;
    this->radius = radius;
}
point3 MSphere::centre(double time) const
{
    return cen1 + ((time - time1) / (time2 - time1)) * (cen2 - cen1);
}


//defining the hit function
//just use the same hit function as the sphere class and replace center by center(t)
//also, an instance of a class can also be defined as const and such an instance can only invoke const 
//member functions as they ensure not to change any of the class members
bool MSphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - centre(r.time());
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
    vec3 outward_normal = vec3(rec.p - centre(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
bool MSphere::bounding_box(double time0, double time1, aabb& output_box) const{
    //first create a bounding box at time to
    //then create a bounding box at time t1
    //now define the bounding box for this moving sphere as the box surrounding both these bounding boxes
    aabb box0(centre(time0)-vec3(radius, radius, radius), centre(time0)+vec3(radius, radius, radius));
    aabb box1(centre(time1)-vec3(radius, radius, radius), centre(time1)+vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}
