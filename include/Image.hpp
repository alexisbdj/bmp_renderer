#ifndef BMPRENDERER_IMAGE_HPP_
#define BMPRENDERER_IMAGE_HPP_

#include <cstddef>
#include <string>

namespace bmpr {
    struct BmpHeader {
        BmpHeader();
        std::uint16_t magic;
        std::uint32_t size;
        std::uint16_t reserved1;
        std::uint16_t reserved2;
        std::uint32_t offset;
    };

    struct InfHeader {

    };

    class Image {
        public:
            Image(std::size_t width, std::size_t height);

            void write(const std::string& path);
        private:
            std::size_t width;
            std::size_t height;
    };
}

#endif