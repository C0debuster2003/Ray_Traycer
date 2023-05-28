#include "material.h"
struct hit_record;
lambertian::lambertian(const color &a) //::is the scope resolution operator
{
    this->albedo = make_shared<Solid_Color>(a);
}
lambertian::lambertian(shared_ptr<texture> a)
{
    this->albedo = a;
}
bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();
    // catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;
    scattered = ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}

// metal class members
metal::metal(const color &a, double f)
{
    this->albedo = a;
    this->fuzz = f < 1 ? f : 1;
}
bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

// dielectric class members
dielectric::dielectric(double index_of_refraction) : ir(index_of_refraction) {}
bool dielectric::scatter(
    const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = ray(rec.p, direction, r_in.time());
    return true;
}

color material::emitted(double u, double v, const point3 &p) const{
    return color(0,0,0); //return white
}


//for the diffuse_light class
diffuse_light::diffuse_light(shared_ptr<texture> a){
    this->emit = a;
}
diffuse_light::diffuse_light(color c){
    this->emit = make_shared<Solid_Color>(c);
}
bool diffuse_light::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const{
    return false; //as the material only emits lights and does not reflect 
}
color diffuse_light::emitted(double u, double v, const point3 &p) const{
    return this->emit->value(u,v,p);
}