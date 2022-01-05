import <iostream>;
import <array>;
import <stdexcept>;
import images;

int main() {
    // Image
    constexpr int image_width = 256;
    constexpr int image_height = 256;
    constexpr int bpp = 3;

    std::array<std::byte, image_width * image_height * 3> buffer;

    // Render

    int current = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            auto ir = static_cast<std::byte>(255.999 * r);
            auto ig = static_cast<std::byte>(255.999 * g);
            auto ib = static_cast<std::byte>(255.999 * b);

            buffer[current    ] = ir;
            buffer[current + 1] = ig;
            buffer[current + 2] = ib;

            current += 3;
        }
    }

    write_image("img.png", image_width, image_height, PixelFormat::RGB, buffer);
}