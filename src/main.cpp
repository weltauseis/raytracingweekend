#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "color.h"

int main()
{
    // materials

    auto ground_mat = make_shared<lambertian>(color(0.141, 0.18, 0.451));
    auto ball_mat = make_shared<lambertian>(color(0.98, 0.604, 1));
    auto metal_mat = make_shared<metal>(color(1, 1, 1), 0.7);
    auto tinted_metal_mat = make_shared<metal>(color(0.443, 1, 0.659), 0.01);

    // world

    hittable_list world;
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, ground_mat));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, ball_mat));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, metal_mat));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, tinted_metal_mat));

    // camera

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);

    return 0;
}