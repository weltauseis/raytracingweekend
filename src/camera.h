#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "color.h"

class camera
{
private:
    int image_height;   // Rendered image height
    point3 center;      // Camera center
    point3 pixel00_loc; // Location of pixel 0, 0
    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; // Offset to pixel below

    void initialize()
    {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);

        // Determine viewport dimensions
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        point3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray &r, const hittable &world)
    {
        hit_record rec;

        // if we hit smt, return the color-converted normal vector
        if (world.hit(r, interval(0, infinity), rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        // else, "sky" effect based on y component of ray
        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    void render(const hittable &world)
    {
        initialize();

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << '\n'
                  << "255\n";

        for (int j = 0; j < image_height; j++)
        {
            std::clog << "\r Scanline remaining : " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                point3 pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
                vec3 ray_direction = pixel_center - center;

                // not a unit vector
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, world);

                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\r Done !                   \n";
    }
};

#endif // CAMERA_H