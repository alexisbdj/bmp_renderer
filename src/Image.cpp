#include <fstream>
#include "Image.hpp"

namespace bmpr {
    BmpHeader::BmpHeader()
    {
        this->magic = 0x4D42;
        this->size = 0;
        this->reserved1 = 0;
        this->reserved2 = 0;
        this->offset = 0;
    }

    Image::Image(std::size_t width, std::size_t height)
    {
        this->width = width;
        this->height = height;
    }

    void Image::write(const std::string& path)
    {
        BmpHeader bheader;
        std::ofstream file(path, std::ofstream::out | std::ofstream::binary);

        file.write(reinterpret_cast<char*>(&bheader), sizeof(BmpHeader));
        file.close();
    }

}