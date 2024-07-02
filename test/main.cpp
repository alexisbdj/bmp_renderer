#include "Image.hpp"

int main()
{
    bmpr::Image img(200, 200, bmpr::Color(255, 255, 255));
    for (int x = 5; x < 95; x++) {
        for (int y = 5; y < 95; y++) {
            img.getPixel(x, y) = bmpr::Color(0, 0, 255);
        }
    }
    for (int i = 0; i < 200; i++) {
        img.getPixel(i, i) = bmpr::Color(255, 0, 0);
    }
    img.write("test.bmp");
    return 0;
}