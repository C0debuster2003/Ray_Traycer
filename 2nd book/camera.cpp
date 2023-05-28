#include "camera.h"
// default constructor (for older images rendered as they do not include lookfrom and lookat functionality)
camera::camera()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const auto viewport_height = 2.0;
    const auto viewport_width = static_cast<int>(viewport_height * aspect_ratio);
    const auto focal_length = 1.0;
    this->origin = point3(0.0, 0.0, 0.0);
    this->horizontal = vec3(viewport_width, 0.0, 0.0);
    this->vertical = vec3(0.0, viewport_height, 0.0);
    this->lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0.0, 0.0, focal_length);
}
// parametrized consstructor for the lookfrom and lookat functionality
camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double v_fov, double aspect_ratio, double aperture,
               double focus_distance, double _time1 = 0.0, double _time2 = 0.0)
{
    double rad_vfoc = degrees_to_radians(v_fov); // v_fov is in degrees and is converted to radians
    const auto viewport_height = 2.0 * tan(rad_vfoc / 2);
    const auto viewport_width = (viewport_height * aspect_ratio);
    const auto focal_length = 1.0;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    time1 = _time1;
    time2 = _time2;

    origin = lookfrom;
    horizontal = focus_distance * viewport_width * u;
    vertical = focus_distance * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;
    lens_radius = aperture / 2;
}
// function to get a ray
ray camera::get_ray(double s, double t) const
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return ray(
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset, random_double(time1, time2));
    // the purpose of the randome_double(..) is to produce a time at which a ray is generated from the camera
    // and strikes the scene
}
