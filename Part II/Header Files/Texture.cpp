#include "Texture.h"
Solid_Color::Solid_Color() {} // default constructor
Solid_Color::Solid_Color(color c)
{
    this->color_value = c;
}
Solid_Color::Solid_Color(double red, double green, double blue)
{
    this->color_value = color(red, blue, green);
}
color Solid_Color::value(double u, double v, const point3 &p) const
{
    return color_value;
}

checker_texture::checker_texture() {}
checker_texture::checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd) : even(_even), odd(_odd) {}
checker_texture::checker_texture(color c1, color c2) : even(make_shared<Solid_Color>(c1)),
                                                       odd(make_shared<Solid_Color>(c2)) {}
color checker_texture::value(double u, double v, const point3 &p) const
{
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}

noise_texture::noise_texture() {}
color noise_texture::value(double u, double v, const point3 &p) const
{
    return color(1, 1, 1) * noise.noise(p);
}

// for the image texture mapping class
image_texture::image_texture()
{
    data = nullptr;
    width = 0;
    height = 0;
    bytes_per_scanline = 0;
}
//:: is the scope resolution operator
image_texture::image_texture(const char* filename)
{
    auto components_per_pixel = bytes_per_pixel;
    data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);
    if (data == nullptr)
    {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }
    bytes_per_scanline = bytes_per_pixel * width;
}
// destructor
image_texture::~image_texture()
{
    delete data;
}
color image_texture::value(double u, double v, const vec3 &p) const
{
    if (data == nullptr) // if we have no texture data, then return cyan as the color for that pixel
        return color(0, 1, 1);

    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);
    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);
    if (i >= width)
        i = width - 1;
    if (j >= height)
        j = height - 1;
    const auto color_scale = 1.0 / 255.0;
    auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;
    return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}