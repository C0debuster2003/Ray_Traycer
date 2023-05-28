#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt_weekend.h"
#include "hittable.h"
#include "Texture.h"

struct hit_record;
class material
{
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered)
        const = 0;
};

// defining the lambertian class for diffuse objects (scatter in a random direction)
class lambertian : public material
{
public:
    // without using a solid texture
    lambertian(const color &a);
    // with using a solid texture
    lambertian(shared_ptr<texture> a);
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;

public:
    shared_ptr<texture> albedo;
};

class metal : public material
{
public:
    metal(const color &a, double f);
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;

public:
    color albedo;
    double fuzz;
};

// defining the refraction class
class dielectric : public material
{
public:
    dielectric(double index_of_refraction);
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
    double ir; // Index of Refraction
private:
    static double reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
#endif