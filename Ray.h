#ifndef RAY_H
#define RAY_H
#include<iostream>
using namespace std;
#include "Color.h"

//defining the ray class
//ray is of the form P(t) = A+Bt  where A,B,P are vectors and t is a scalar (trivial)
class ray{
    public:
        point3 orig;
        vec3 dir;
        ray(){} //default constructor
        ray(const point3 &A, const vec3 &b){
            this->orig = A;
            this->dir = b;
        }
        point3 origin() const{return orig;}
        vec3 direction() const{return dir;}
        point3 at(double t) const{
            return orig+t*dir;
        }
};
#endif