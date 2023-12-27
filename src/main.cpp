#include <iostream>

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

            int ir = static_cast<int>(255 * r);
            int ig = static_cast<int>(255 * g);
            int ib = static_cast<int>(255 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\r Done !                   \n";

    return 0;
}