#include <pnm.hpp>

int main()
{
    using namespace pnm::literals;

    pnm::write("white.pbm", pnm::pbm_image(100, 100, 0_bit       ), pnm::format::binary);
    pnm::write("black.pbm", pnm::pbm_image(100, 100, 1_bit       ), pnm::format::binary);
    pnm::write("gray.pgm",  pnm::pgm_image(100, 100, 0xAA_gray   ), pnm::format::binary);
    pnm::write("red.ppm",   pnm::ppm_image(100, 100, 0xFF0000_rgb), pnm::format::binary);
    pnm::write("green.ppm", pnm::ppm_image(100, 100, 0x00FF00_rgb), pnm::format::binary);
    pnm::write("blue.ppm",  pnm::ppm_image(100, 100, 0x0000FF_rgb), pnm::format::binary);

    return 0;
}
