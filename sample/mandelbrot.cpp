#include <pnm.hpp>
#include <complex>
#include <iostream>

pnm::rgb_pixel colormap(double ratio)
{
    const std::uint8_t color = std::min<uint8_t>(255u,
        static_cast<std::uint8_t>(256 * (ratio*4 - std::floor(ratio*4))));
    if     (ratio < 0.25) {return pnm::rgb_pixel(255, color, 0);}
    else if(ratio < 0.50) {return pnm::rgb_pixel(255-color, 255, 0);}
    if     (ratio < 0.75) {return pnm::rgb_pixel(0, 255, color);}
    else                  {return pnm::rgb_pixel(0, 255-color, 255);}
}

int main(int argc, char **argv)
{
    using namespace pnm::literals;
    const std::size_t w   = 512;
    const std::size_t h   = 512;
    const std::size_t max_iter = 1000;

    const double ox = -1.5;
    const double oy = -1.0;
    const double dx = 2.0 / w;
    const double dy = 2.0 / h;

    pnm::image<pnm::rgb_pixel> img(w, h, 0x000000_rgb);

    for(std::size_t j=0; j<h; ++j)
    {
        const double y = oy + j * dy;
        for(std::size_t i=0; i<w; ++i)
        {
            const double x = ox + i * dx;
            const std::complex<double> c(x, y);

            std::size_t iteration = max_iter;
            std::complex<double> z(0, 0);
            for(; iteration > 0; --iteration)
            {
                z = z * z + c;
                if(std::abs(z) > 2.0)
                {
                    break;
                }
            }
            if(iteration != 0)
            {
                const double ratio = static_cast<double>(iteration) / max_iter;
                img[j][i] = colormap(ratio);
            }
        }
    }
    pnm::write("mandelbrot.ppm", img, pnm::format::binary);
    return 0;
}
