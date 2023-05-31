#pragma once
#include "rt_weekend.h"
#include"vec3.h"
class perlin {
    public:
    //constructor
        perlin();
    //destructor
        ~perlin();
        double noise(const point3& p) const;
    private:
        static const int point_count = 256;
        double* ranfloat;
        int* perm_x;
        int* perm_y;
        int* perm_z;

        static int* perlin_generate_perm();
        static void permute(int* p, int n);
};