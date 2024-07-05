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

### Usage

create an `Image` object from `bmpr` namespace :
```cpp
Image(std::size_t width, std::size_t height, Color bg = Color());
```

then you can call it's methods :

get a pixel so you can change it's value.
```cpp
Color& getPixel(int x, int y);
```

choose where is the 0,0 position located  
possible values are `TopLeft` and `BottomLeft` (default is `TopLeft`)
```cpp
void setOrigin(Origin origin);
```

save your image
```cpp
void write(const std::string& path);
```

### Exemple

```cpp
    #include <BmpRenderer.hpp>

    int main()
    {
        bmpr::Image img(210, 210, bmpr::Color(255, 255, 255)); // default white background
        img.setOrigin(bmpr::Origin::TopLeft); // origin (0,0) is topLeft

        for (int x = 5; x < 95; x++) {  // draw a square
            for (int y = 5; y < 95; y++) {
                img.getPixel(x, y) = bmpr::Color(0, 0, 255);
            }
        }

        for (int i = 0; i < 200; i++) { // draw a line
            img.getPixel(i, i) = bmpr::Color(255, 0, 0);
        }
        img.write("test.bmp");
        return 0;
    }
```