# pnm

pnm format(pbm, pgm, ppm) IO for modern C++

##  example

```cpp
#include <pnm++/pnm.hpp>
#include <iostream>

int main()
{
    using namespace pnm::literals;
    pnm::image<pnm::rgb_pixel> ppm = pnm::read_ppm("sample.ppm");

    std::cout << "width  = " << ppm.width()  << std::endl;
    std::cout << "height = " << ppm.height() << std::endl;

    for(std::size_t y=0; y<ppm.y_size(); ++y)
    {
        for(std::size_t x=0; x<ppm.x_size(); ++x)
        {
            ppm[y][x] = 0xFF00FF_rgb;
        }
    }
    pnm::write_ppm("out.ppm", ppm, pnm::format::binary);

    return 0;
}
```
