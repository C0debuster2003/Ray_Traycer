//simple PPM image file is created here
#include<iostream>
using namespace std;
int main(){
    //the image_height = 256px and image_width = 256px
    const int image_height = 256;
    const int image_width = 256;
    //writing according to the syntax specified for PPM files
    cout <<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";

    for(int i = 0;i<=image_height-1;i++){
        for(int j=0;j<=image_width-1;j++){
            auto r = (double)i/(image_height-1);
            auto g = (double)j/(image_width-1);
            auto b = (r+g)/2;

            int ir = static_cast<int>(255.999*r);
            int ig = static_cast<int>(255.999*g);
            int ib = static_cast<int>(255.999*b);
            cout <<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }
}
