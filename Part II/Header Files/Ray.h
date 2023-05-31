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
        double tm = 0.0 ;
        ray(); //default constructor
        ray(const point3 &A, const vec3 &b, double time);
        //<data type><function name>(.....) const?
        //this means that the given funciton cannot change any of the class members
        //they are denied permission to change the data members of the particular class where they are defined

        point3 origin() const;
        vec3 direction() const;
        double time() const;
        point3 at(double t) const;};
#endif