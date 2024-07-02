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

    CoreHeader::CoreHeader()
    {
        this->hsize = sizeof(CoreHeader);
        this->width = 0;
        this->height = 0;
        this->planes = 1;
        this->bpp = 24; // rgb
    }

    Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        this->red = r;
        this->green = g;
        this->blue = b;
    }

    Image::Image(std::size_t width, std::size_t height, Color bg)
    {
        this->width = width;
        this->height = height;
        this->content.resize(width * height, bg);
    }

    void Image::write(const std::string& path)
    {
        BmpHeader bheader;
        CoreHeader cheader;
        bheader.offset = sizeof(BmpHeader) + sizeof(CoreHeader);
        bheader.size = bheader.offset + this->height * this->width * sizeof(Color);
        cheader.width = this->width;
        cheader.height = this->height;
        std::ofstream file(path, std::ofstream::out | std::ofstream::binary);


        file.write(reinterpret_cast<char*>(&bheader), sizeof(BmpHeader));
        file.write(reinterpret_cast<char*>(&cheader), sizeof(CoreHeader));
        file.write(reinterpret_cast<char*>(this->content.data()), sizeof(Color) * this->width * this->height);
        file.close();
    }

    Color& Image::getPixel(int x, int y)
    {
        return this->content.at(x + y * this->width);
    }
}