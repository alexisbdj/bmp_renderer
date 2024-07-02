#include <fstream>
#include "Image.hpp"

namespace bmpr {
    const int BPP = 24;
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
        this->bpp = BPP;
        this->compression = 0;
        this->imgSize = 0;
        this->hRes = -300;
        this->wRes = 300;
        this->nColors = 0;
        this->iColors = 0;
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
        this->origin = Origin::TopLeft;
    }

    void Image::write(const std::string& path)
    {
        BmpHeader bheader;
        CoreHeader cheader;
        bheader.offset = sizeof(BmpHeader) + sizeof(CoreHeader);
        bheader.size = bheader.offset + this->height * this->width * sizeof(Color);
        cheader.width = this->width;
        cheader.height = this->height;
        if (this->origin == Origin::TopLeft) {
            cheader.height *= -1;
        }

        std::ofstream file(path, std::ofstream::out | std::ofstream::binary);

        file.write(reinterpret_cast<char*>(&bheader), sizeof(BmpHeader));
        file.write(reinterpret_cast<char*>(&cheader), sizeof(CoreHeader));

        if (this->getPadding() == 0)
            file.write(reinterpret_cast<char*>(this->content.data()), sizeof(Color) * this->width * this->height);
        else {
            for (int y = 0; y < this->height; y++) {
                file.write(reinterpret_cast<char*>(this->content.data() + (y * this->width)), getWidthSize());
            }
        }
        file.close();
    }

    Color& Image::getPixel(int x, int y)
    {
        return this->content.at(x + y * this->width);
    }

    void Image::setOrigin(Origin origin)
    {
        this->origin = origin;
    }

    std::size_t Image::getPadding() const
    {
        return ((this->width * BPP) % 32) / 8;
    }

    std::size_t Image::getWidthSize() const
    {
        return this->width * sizeof(Color) + getPadding();
    }
}