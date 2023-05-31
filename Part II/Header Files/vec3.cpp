#include "vec3.h"
vec3::vec3()
{
    this->e[0] = 0;
    this->e[1] = 0;
    this->e[2] = 0;
}
// parametrized constructor
vec3::vec3(double e0, double e1, double e2)
{
    this->e[0] = e0;
    this->e[1] = e1;
    this->e[2] = e2;
}
double vec3::x() const { return this->e[0]; }
double vec3::y() const { return this->e[1]; }
double vec3::z() const { return this->e[2]; }

vec3 vec3::operator-() const { return vec3(-this->e[0], -this->e[1], -this->e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double &vec3::operator[](int i) { return e[i]; }

void vec3::operator+=(const vec3 &vector)
{
    this->e[0] = this->e[0] + vector[0];
    this->e[1] = this->e[1] + vector[1];
    this->e[2] = this->e[2] + vector[2];
}
void vec3::operator*=(const double t)
{
    this->e[0] = t * this->e[0];
    this->e[1] = t * this->e[1];
    this->e[2] = t * this->e[2];
}
void vec3::operator/=(const double t)
{
    this->e[0] = this->e[0] / t;
    this->e[1] = this->e[1] / t;
    this->e[2] = this->e[2] / t;
}

double vec3::length() const { return sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2)); }
double vec3::length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
bool vec3::near_zero() const
{
    // checks if all the 3 components of the vector are very small or not
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}
vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}
vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}
vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}