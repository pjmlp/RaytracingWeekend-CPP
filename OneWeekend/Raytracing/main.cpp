import <iostream>;

import color;
import algebra;
import images;

using namespace Raytracinglib::images;

int main() {
    // Image
    constexpr int image_width = 256;
    constexpr int image_height = 256;

    ImageBuffer buffer(image_width, image_height, PixelFormat::RGB);


    // Render
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
            buffer.set_color(i, j, pixel_color);
        }
    }

    buffer.save("img.png");
    std::cerr << "\nDone.\n";
}