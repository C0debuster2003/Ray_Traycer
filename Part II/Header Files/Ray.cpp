#include "Ray.h"
ray::ray() {}                                               // default constructor
ray::ray(const point3 &A, const vec3 &b, double time = 0.0) // paramterized constructor
{
    this->orig = A;
    this->dir = b;
    this->tm = time;
}
point3 ray::origin() const { return orig; }
vec3 ray::direction() const { return dir; }
double ray::time() const { return this->tm; }
point3 ray::at(double t) const
{
    return orig + t * dir;
}