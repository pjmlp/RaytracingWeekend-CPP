module;

// for sprintf_s and friends
#ifdef _WIN32
#define __STDC_LIB_EXT1__
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <string>
#include <vector>
#include <span>
#include <cstddef>
#include <stdexcept>

export module RaytracingLib:images;

import :algebra;

// public view of the module
export namespace RaytracingLib {
    /**
     * @brief Set of available pixel formats to export.
     */
    enum class PixelFormat : int { RGB = 3, RGBA = 4 };

    /**
     * @brief Allows writing a data buffer representing an image as a PNG.
     * @param filename The complete path to the filename being written.
     * @param width The image width.
     * @param height The image height.
     * @param buffer The image contents, it must match the desired size.
     * @exception std::logic_error if there is an error saving the file.
     * @exception std::out_of_range if there is an error saving the file.
     */
    void write_image(const std::string& filename, int width, int height, PixelFormat format, std::span<std::uint8_t> buffer) {
        auto bpp = static_cast<int>(format);
        if (static_cast<size_t>(width * height * bpp) > buffer.size()) {
            throw std::out_of_range("Image buffer isn't the expected size");
        }

        stbi_flip_vertically_on_write(true);
        int res = stbi_write_png(filename.c_str(), width, height, bpp, buffer.data(), bpp * width);
        if (res == 0) {
            throw std::logic_error("Failed to write the image file");
        }
    }

    /**
     * @brief Provides a type safe abstraction of an image data buffer.
     */
    class ImageBuffer final {
    public:
        ImageBuffer(int width, int height) : imgWidth(width), imgHeight(height), imgFormat(PixelFormat::RGB)
        {
            buffer.resize(width * height * static_cast<int>(PixelFormat::RGB));
        }

        ImageBuffer(int width, int height, PixelFormat format): imgWidth(width), imgHeight(height), imgFormat(format) 
        {
            buffer.resize(width * height * static_cast<int>(imgFormat));
        }

        int width() const noexcept { return imgWidth; }
        int height() const noexcept { return imgHeight; }
        PixelFormat format() const noexcept { return imgFormat; }

        void set_color(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
            const int bpp = static_cast<int>(imgFormat);
            const int index = (y * imgHeight + x) * bpp;
            if (static_cast<size_t>(index + bpp) > buffer.size()) {
                throw std::out_of_range("Image buffer isn't the expected size");
            }

            buffer[index    ] = r;
            buffer[index + 1] = g;
            buffer[index + 2] = b;
        }

        void set_color(int x, int y, color pixel_color) {
            const int bpp = static_cast<int>(imgFormat);
            const int index = (y * imgWidth + x) * bpp;
            if (static_cast<size_t>(index + bpp) > buffer.size()) {
                throw std::out_of_range("Image buffer isn't the expected size");
            }

            // Write the translated [0,255] value of each color component.
            buffer[index] = static_cast<std::uint8_t>(255.999 * pixel_color.x());
            buffer[index + 1] = static_cast<std::uint8_t>(255.999 * pixel_color.y());
            buffer[index + 2] = static_cast<std::uint8_t>(255.999 * pixel_color.z());
        }

        void set_color(int x, int y, color pixel_color, int samples_per_pixel) {
            const int bpp = static_cast<int>(imgFormat);
            const int index = (y * imgWidth + x) * bpp;
            if (static_cast<size_t>(index + bpp) > buffer.size()) {
                throw std::out_of_range("Image buffer isn't the expected size");
            }

            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            auto scale = 1.0 / samples_per_pixel;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write the translated [0,255] value of each color component.
            buffer[index] = static_cast<std::uint8_t>(256 * clamp(r, 0.0, 0.999));
            buffer[index + 1] = static_cast<std::uint8_t>(256 * clamp(g, 0.0, 0.999));
            buffer[index + 2] = static_cast<std::uint8_t>(256 * clamp(b, 0.0, 0.999));
        }

        void set_color(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
            constexpr int bpp = static_cast<int>(PixelFormat::RGBA);
            const int index = (y * imgWidth + x) * bpp;
            if (static_cast<size_t>(index + bpp) > buffer.size()) {
                throw std::out_of_range("Image buffer isn't the expected size");
            }

            buffer[index] = r;
            buffer[index + 1] = g;
            buffer[index + 2] = b;
            buffer[index + 3] = a;
        }

        void save(const std::string& filename) {
            write_image(filename, imgWidth, imgHeight, imgFormat, buffer);
        }

    private:
        const int imgWidth;
        const int imgHeight;

        PixelFormat imgFormat;
        std::vector<std::uint8_t> buffer;
    };
}
