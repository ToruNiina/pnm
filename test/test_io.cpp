#define CATCH_CONFIG_MAIN
#include <extlib/catch.hpp>
#include <pnm.hpp>
#include <random>

namespace pnm
{
template<typename Pixel, typename Alloc>
bool operator==(const image<Pixel, Alloc>& lhs, const image<Pixel, Alloc>& rhs)
{
    return lhs.width() == rhs.width() && lhs.height() == rhs.height() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
}

TEST_CASE("test input/output for pbm images", "[pbm io]")
{
    pnm::image<pnm::bit_pixel> img(10, 10);

    std::random_device dev;
    std::mt19937 mt(dev());
    std::bernoulli_distribution dist(0.5);

    for(std::size_t j=0; j<10; ++j)
    {
        for(std::size_t i=0; i<10; ++i)
        {
            img[j][i] = pnm::bit_pixel(dist(mt));
        }
    }

    pnm::write("test_ascii.pbm",  img, pnm::format::ascii);
    pnm::write("test_binary.pbm", img, pnm::format::binary);

    SECTION("set pixel type by template parameter")
    {
        const auto ascii  = pnm::read<pnm::bit_pixel>("test_ascii.pbm");
        const auto binary = pnm::read<pnm::bit_pixel>("test_binary.pbm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type by function name")
    {
        const auto ascii  = pnm::read_pbm("test_ascii.pbm");
        const auto binary = pnm::read_pbm("test_binary.pbm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type and format by function name")
    {
        const auto ascii  = pnm::read_pbm_ascii("test_ascii.pbm");
        const auto binary = pnm::read_pbm_binary("test_binary.pbm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }
}

TEST_CASE("test input/output for pgm images", "[pgm io]")
{
    pnm::image<pnm::gray_pixel> img(10, 10);

    std::random_device dev;
    std::mt19937 mt(dev());
    std::uniform_int_distribution<std::uint8_t> dist(0, 255);

    for(std::size_t j=0; j<10; ++j)
    {
        for(std::size_t i=0; i<10; ++i)
        {
            img[j][i] = pnm::gray_pixel(dist(mt));
        }
    }

    pnm::write("test_ascii.pgm",  img, pnm::format::ascii);
    pnm::write("test_binary.pgm", img, pnm::format::binary);

    SECTION("set pixel type by template parameter")
    {
        const auto ascii  = pnm::read<pnm::gray_pixel>("test_ascii.pgm");
        const auto binary = pnm::read<pnm::gray_pixel>("test_binary.pgm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type by function name")
    {
        const auto ascii  = pnm::read_pgm("test_ascii.pgm");
        const auto binary = pnm::read_pgm("test_binary.pgm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type and format by function name")
    {
        const auto ascii  = pnm::read_pgm_ascii("test_ascii.pgm");
        const auto binary = pnm::read_pgm_binary("test_binary.pgm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }
}


TEST_CASE("test input/output for ppm images", "[ppm io]")
{
    pnm::image<pnm::rgb_pixel> img(10, 10);

    std::random_device dev;
    std::mt19937 mt(dev());
    std::uniform_int_distribution<std::uint8_t> dist(0, 255);

    for(std::size_t j=0; j<10; ++j)
    {
        for(std::size_t i=0; i<10; ++i)
        {
            img[j][i] = pnm::rgb_pixel(dist(mt), dist(mt), dist(mt));
        }
    }

    pnm::write("test_ascii.ppm",  img, pnm::format::ascii);
    pnm::write("test_binary.ppm", img, pnm::format::binary);

    SECTION("set pixel type by template parameter")
    {
        const auto ascii  = pnm::read<pnm::rgb_pixel>("test_ascii.ppm");
        const auto binary = pnm::read<pnm::rgb_pixel>("test_binary.ppm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type by function name")
    {
        const auto ascii  = pnm::read_ppm("test_ascii.ppm");
        const auto binary = pnm::read_ppm("test_binary.ppm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }

    SECTION("set pixel type and format by function name")
    {
        const auto ascii  = pnm::read_ppm_ascii("test_ascii.ppm");
        const auto binary = pnm::read_ppm_binary("test_binary.ppm");

        REQUIRE(img == ascii);
        REQUIRE(img == binary);
    }
}
