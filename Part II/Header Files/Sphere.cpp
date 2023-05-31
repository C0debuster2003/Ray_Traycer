#include "Sphere.h"
Sphere::Sphere() {}
Sphere::Sphere(point3 cen, double r, shared_ptr<material> mat_ptr)
{
    this->centre = cen;
    this->radius = r;
    this->mat_ptr = mat_ptr;
}
void Sphere::get_sphere_uv(const point3 &p, double &u, double &v)
{
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}
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
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;
    return true;
}
bool Sphere::bounding_box(double time0, double time1, aabb& output_box) const{
    output_box = aabb(centre-vec3(radius, radius, radius), centre+vec3(radius, radius, radius));
    return true;
}