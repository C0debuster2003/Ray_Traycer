#pragma once
#include "rt_weekend.h"
#include "hittable.h"
#include "Texture.h"

struct hit_record;
class material
{
public:
    virtual color emitted(double u, double v, const point3& p) const {
        return color(0,0,0);
    }
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

class diffuse_light : public material  {
    public:
        diffuse_light(shared_ptr<texture> a) : emit(a) {}
        diffuse_light(color c) : emit(make_shared<Solid_Color>(c)) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            return false;
        }

        virtual color emitted(double u, double v, const point3& p) const override {
            return emit->value(u, v, p);
        }

    public:
        shared_ptr<texture> emit;
};

//isotropic class
class isotropic : public material {
    public:
        isotropic(color c);
        isotropic(shared_ptr<texture> a);
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
    public:
        shared_ptr<texture> albedo;
};
