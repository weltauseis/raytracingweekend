#include <iostream>

#include "vec3.h"
#include "ray.h"
#include "color.h"

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray &r)
{
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);

    if (t > 0)
    {
        vec3 N = unit_vector(r.at(t) - point3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());

    double a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // image

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    point3 camera_center = point3(0, 0, 0);

    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // render

    std::cout << "P3\n"
              << image_width << ' ' << image_height << '\n'
              << "255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\r Scanline remaining : " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            point3 pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            vec3 ray_direction = pixel_center - camera_center;

            // not a unit vector
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\r Done !                   \n";

    return 0;
}