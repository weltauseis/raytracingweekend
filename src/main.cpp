#include <iostream>

#include "vec3.h"
#include "color.h"

int main()
{
    // image

    int image_width = 256;
    int image_height = 256;

    // render

    std::cout << "P3\n"
              << image_width << ' ' << image_height << '\n'
              << "255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\r Scanline remaining : " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            double r = double(i) / (image_width - 1);
            double g = double(j) / (image_width - 1);
            double b = 0.0;

            color pixel_color = color(r, g, b);

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\r Done !                   \n";

    return 0;
}