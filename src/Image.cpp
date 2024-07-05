#include <fstream>
#include "BmpRenderer.hpp"

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
        this->bpp = 0;
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

    template <class T>
    Image<T>::Image(std::size_t width, std::size_t height, T bg)
    {
        this->width = width;
        this->height = height;
        this->content.resize(width * height, bg);
        this->origin = Origin::TopLeft;
        this->bpp = sizeof(T) * 8;
    }

    template <class T>
    void Image<T>::write(const std::string& path)
    {
        BmpHeader bheader;
        CoreHeader cheader;
        bheader.offset = sizeof(BmpHeader) + sizeof(CoreHeader);
        bheader.size = bheader.offset + this->height * this->width * sizeof(T);
        cheader.width = this->width;
        cheader.height = this->height;
        cheader.bpp = this->bpp;
        if (this->origin == Origin::TopLeft) {
            cheader.height *= -1;
        }

        std::ofstream file(path, std::ofstream::out | std::ofstream::binary);

        file.write(reinterpret_cast<char*>(&bheader), sizeof(BmpHeader));
        file.write(reinterpret_cast<char*>(&cheader), sizeof(CoreHeader));

        if (this->getPadding() == 0)
            file.write(reinterpret_cast<char*>(this->content.data()), sizeof(T) * this->width * this->height);
        else {
            for (int y = 0; y < this->height; y++) {
                file.write(reinterpret_cast<char*>(this->content.data() + (y * this->width)), getWidthSize());
            }
        }
        file.close();
    }

    template <class T>
    T& Image<T>::getPixel(int x, int y)
    {
        return this->content.at(x + y * this->width);
    }

    template <class T>
    void Image<T>::setOrigin(Origin origin)
    {
        this->origin = origin;
    }

    template <class T>
    std::size_t Image<T>::getPadding() const
    {
        return ((this->width * this->bpp) % 32) / 8;
    }

    template <class T>
    std::size_t Image<T>::getWidthSize() const
    {
        return this->width * sizeof(T) + getPadding();
    }

    template class Image<Color>;
    template class Image<uint8_t>;
}