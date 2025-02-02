#ifndef BMPRENDERER_HPP_
#define BMPRENDERER_HPP_

#include <cstddef>
#include <string>
#include <vector>

namespace bmpr {
    extern const int BPP;

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
        std::int32_t width;
        std::int32_t height;
        std::uint16_t planes;
        std::uint16_t bpp;
        std::uint32_t compression;
        std::uint32_t imgSize;
        std::int32_t hRes;
        std::int32_t wRes;
        std::uint32_t nColors;
        std::uint32_t iColors;

    };

    struct __attribute__((packed)) Color {
        Color(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0);
        std::uint8_t blue;
        std::uint8_t green;
        std::uint8_t red;
    };

    enum Origin {
        TopLeft,
        BottomLeft,
    };

    class Image {
        public:
            Image(std::size_t width, std::size_t height, Color bg = Color());

            void write(const std::string& path);
            Color& getPixel(int x, int y);
            void setOrigin(Origin origin);
        private:
            std::size_t getPadding() const;
            std::size_t getWidthSize() const;

            std::size_t width;
            std::size_t height;
            std::vector<Color> content;
            Origin origin;
    };
}

#endif