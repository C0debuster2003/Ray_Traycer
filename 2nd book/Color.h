#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
using namespace std;
#include<iostream>
#include<fstream>

//function declaration, definition is in the cpp file of the same name
void write_color(std::ofstream &out, color pixel_color, int samples_per_pixel, double gamma);
#endif
