#ifndef BMPRENDERER_IMAGE_HPP_
#define BMPRENDERER_IMAGE_HPP_

#include <cstddef>
#include <string>
#include <vector>

namespace bmpr {
    // idk if __attribute__((packed)) is portable across compilers, need to check
    struct __attribute__((packed)) BmpHeader {
        BmpHeader();
        std::uint16_t magic;
        std::uint32_t size;
        std::uint16_t reserved1;
        std::uint16_t reserved2;
        std::uint32_t offset;
    };

    struct __attribute__((packed)) CoreHeader {
        CoreHeader();
        std::uint32_t hsize;
        std::uint16_t width;
        std::uint16_t height;
        std::uint16_t planes;
        std::uint16_t bpp;
    };

    struct __attribute__((packed)) Color {
        Color(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0);
        std::uint8_t blue;
        std::uint8_t green;
        std::uint8_t red;
    };

    class Image {
        public:
            Image(std::size_t width, std::size_t height, Color bg = Color());

            void write(const std::string& path);
            Color& getPixel(int x, int y);
        private:
            std::size_t width;
            std::size_t height;
            std::vector<Color> content;
    };
}

#endif