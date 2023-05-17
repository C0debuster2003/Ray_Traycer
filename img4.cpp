//A sphere colored according to its normal vectors
#include<iostream>
using namespace std;
#include "Ray.h"
//produces a gradient

double hit_sphere(const point3 &centre, const double &radius, const ray &r){
    //basically defining A-C  (A is the origin of the ray (point from which the ray emanates) and C is centre)
    vec3 oc = r.origin() - centre;
    //defining the coefficient a,b,c in ax2+bx+c for intersection of the line and the circle
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    //calculating the discriminant of the equation if D>0 2 roots, if D=0 1 root, D<0 no intersection
    auto discriminant = b*b-4*a*c;
    //here we have to return the point of contact as well
    if(discriminant >=0) return (-b-sqrt(discriminant))/(2*a);
    else return -1.0;
}
color ray_color(const ray& r){
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if(t==-1.0) {}
    else if(t>=0){
        vec3 normal = unit_vector(r.at(t)-point3(0,0,-1));
        //here the values x x,y,z are between -1 and 1 and thus, this scaling basically peoduces values
        //between 0 and 1 because -1+1 = 0 and 1+1 = 2 and when 0.5 is multiplied gives 1.
        return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction[1]+1.0);
    return (1.0-t)*color(1.0,1.0,1.0)+t*color(0.5,0.7,1.0);
}
int main(){
//Image
const auto aspect_ratio = 16.0/9;
const int image_width = 400;
const int image_height = static_cast<int>(400/aspect_ratio);
//Camera
auto origin = point3(0,0,0);
auto viewport_height = 2.0;
auto viewport_width = aspect_ratio*viewport_height;
auto focal_length =1.0;
auto horizontal = vec3(viewport_width,0,0);
auto vertical = vec3(0, viewport_height,0);
auto lower_left_corner = origin-horizontal/2-vertical/2-vec3(0,0,focal_length);

//Render
cout << "P3\n" << image_width << " " << image_height << "\n255\n";
for(int j = image_height-1; j>=0; j--){
    for(int i=0;i<=image_width-1;i++){
        auto u = double(i)/(image_width-1);
        auto v = double(j)/(image_height-1);
        ray r(origin, lower_left_corner+u*horizontal+v*vertical-origin);
        color pixel_color = ray_color(r);
        int ir = static_cast<int>(255.999*pixel_color[0]);
        int ig = static_cast<int>(255.999*pixel_color[1]);
        int ib = static_cast<int>(255.999*pixel_color[2]);
        cout <<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }
}