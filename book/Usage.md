# Usage

## Installation

Copy `pnm.hpp` to your favorite location.
Because pnm is a header-only, you need no build before use it.

## example

```cpp
#include <pnm++/pnm.hpp>
#include <iostream>

int main()
{
    using namespace pnm::literals; // ""_rgb literal

    pnm::image<pnm::rgb_pixel> ppm = pnm::read("sample.ppm");

    // you can get a number of pixels in the image
    std::cout << "width  = " << ppm.width()  << std::endl;
    std::cout << "height = " << ppm.height() << std::endl;

    // fill the image with 0xFF00FF.
    for(std::size_t y=0; y<ppm.y_size(); ++y)
    {
        for(std::size_t x=0; x<ppm.x_size(); ++x)
        {
            ppm[y][x] = 0xFF00FF_rgb;
        }
    }

    // write the image into `out.ppm` as binary format (after conversion)
    pnm::write("out.ppm", ppm, pnm::format::binary);

    return 0;
}
```

## Pixel types

pnm supports 3 pixel types that correspond binary, grayscale, and RGB color.

binary and grayscale pixel type has a member variable `value`. RGB pixel type
has 3 member variables named `red`, `blue`, and `green`, respectively.

```cpp
pnm::bit_pixel binary;
binary.value = true;

pnm::gray_pixel gray;
gray.value = 0xFF;

pnm::rgb_pixel RGB;
RGB.red   = 0xFF;
RGB.green = 0xFF;
RGB.blue  = 0xFF;
```

## Image types

`pnm::image` is a class that represents image. It requires pixel format as a
template parameter.

```cpp
pnm::image<pnm::bit_pixel>  ppm;
pnm::image<pnm::gray_pixel> ppm;
pnm::image<pnm::rgb_pixel>  ppm;
```

You can access each pixel by using `operator[]` and `at()` in the same way as
nested vector. Also, you can access to lines composed by pixels by `lines()`.

```cpp
pnm::image<pnm::rgb_pixel> img;
for(const auto line : img.lines())
{
    for(const auto pixel : line)
    {
        std::cout << '(' << pixel.red  << ' ' << pixel.green << ' '
                         << pixel.blue << ')';
    }
}
```

The constructors accepts `(width, height)`, `(width, height, pixel)`,
`(width, height, std::vector<pixel>)`, and `(std::vector<std::vector<pixel>>)`.


## IO

`read()` and `read_(pbm|pgm|ppm)` functions read a file header and
automatically detects the file format. `read()` function receives `pixel_type`
that you want to get(By default, it is `rgb_pixel`).

{% hint style='working' %}
Note that when you pass a `pixel_type` that is different from actual one
contained in the file, `read()` converts the `pixel_type` if it is not
`narrowing-conversion` (for example, conversion from `bit_pixel` to `rgb_pixel`
is allowed. On the other hand, the opposite conversion is not allowed).
{% endhint %}

`write` function writes the image file into a specific file. You can select a
format to write out by passing an enum value `pnm::format::ascii` or
`pnm::format::binary`.


