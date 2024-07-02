# bmp_renderer

This library is designed to render images in BMP format.

It is simple and lightweight

## Key Features:
- **Easy to Use:** Simple API for quick integration.
- **Lightweight:** only dependency is STL.
- **Console Application Support:** Perfect for testing console applications by displaying data such as maps and charts without requiring a GUI.

## Getting Started

### Installation

you can clone this repository from your project and then refer to this library in your own CMakeFiles as `bmprenderer`.

### Exemple

```cpp
    #include "Image.hpp"

    int main()
    {
        bmpr::Image img(210, 210, bmpr::Color(255, 255, 255));
        img.setOrigin(bmpr::Origin::TopLeft);
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
```