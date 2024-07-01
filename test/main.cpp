#include "Image.hpp"

int main()
{
    bmpr::Image img(200, 200);
    img.write("test.bmp");
    return 0;
}