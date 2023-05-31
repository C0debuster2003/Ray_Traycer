#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
using namespace std;
#include "rt_weekend.h"
#include"Perlin.h"
#include"rtw_stb_image.h"
class texture{
    public:
    //defining a purely virtual function using this syntax
    virtual color value(double u, double v, const point3& p) const =0;
};


class Solid_Color: public texture{
    public:
    color color_value;
    //creating the default constructor
    Solid_Color();

    //creating the parametrized constructor
    //you can simply pass the colour as rgb components
    Solid_Color(color c);
    //or you can pass the color as rgb values and then covert it into the specific colour
    Solid_Color(double red, double green, double blue);
    virtual color value(double u, double v, const point3& p)const override;
};


class checker_texture : public texture {
    public:
        checker_texture();
        checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);
        checker_texture(color c1, color c2);
        virtual color value(double u, double v, const point3& p) const override;

    public:
        shared_ptr<texture> odd;
        shared_ptr<texture> even;
};


//defining a perlin texture class
class noise_texture : public texture {
    public:
        noise_texture();
        virtual color value(double u, double v, const point3& p) const override;
    public:
        perlin noise;
};

//image texture mapping
class image_texture: public texture{
    public:
        const static int bytes_per_pixel = 3;
        //default constructor
        image_texture();
        //parametrized constructor
        image_texture(const char* filename);
        ~image_texture();
         virtual color value(double u, double v, const vec3& p) const override;
    private:
        unsigned char* data;   //this array basically store the texture data
        int width;
        int height;
        int bytes_per_scanline;
};
#endif