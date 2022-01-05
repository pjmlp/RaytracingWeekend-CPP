module;

#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

export module images;

import <string>;
import <span>;
import <cstddef>;
import <stdexcept>;

/**
 * @brief Set of available pixel formats to export.
 */
export enum class PixelFormat : int {RGB = 3, RGBA = 4};

/**
 * @brief Allows writing a data buffer representing an image as a PNG.
 * @param filename The complete path to the filename being written.
 * @param width The image width.
 * @param height The image height.
 * @param buffer The image contents, it must match the desired size.
*/
export void write_image(const std::string& filename, int width, int height, PixelFormat format, std::span<std::byte> buffer) {
    int res = stbi_write_png(filename.c_str(), width, height, static_cast<int>(format), buffer.data(), 0);
    if (res == 0) {
        throw std::logic_error("Failed to write the image file");
    }
}
