
import <iostream>;

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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            auto ir = static_cast<std::uint8_t>(255.999 * r);
            auto ig = static_cast<std::uint8_t>(255.999 * g);
            auto ib = static_cast<std::uint8_t>(255.999 * b);

            buffer.set_color(i, j, ir, ig, ib);
        }
    }

    buffer.save("img.png");
    std::cerr << "\nDone.\n";
}