#define CATCH_CONFIG_MAIN
#include <extlib/catch.hpp>
#include <pnm.hpp>

TEST_CASE("pixel type for pbm binary images", "[bit_pixel]")
{
    static_assert(pnm::is_pixel<pnm::bit_pixel>::value,
                  "bit_pixel is a pixel type");

    SECTION("construct from bare values")
    {
        const pnm::bit_pixel b1(true);
        const pnm::bit_pixel b2(false);

        REQUIRE(b1.value == true);
        REQUIRE(b2.value == false);
    }

    SECTION("construct by literals")
    {
        using namespace pnm::literals;

        const pnm::bit_pixel b1 = 0_bit;
        const pnm::bit_pixel b2 = 1_bit;

        REQUIRE(b1.value == false);
        REQUIRE(b2.value == true);
    }
}

TEST_CASE("pixel type for pgm grayscale images", "[gray_pixel]")
{
    static_assert(pnm::is_pixel<pnm::gray_pixel>::value,
                  "gray_pixel is a pixel type");

    SECTION("construct from bare values")
    {
        const pnm::gray_pixel p1(0);
        const pnm::gray_pixel p2(128);
        const pnm::gray_pixel p3(255);

        REQUIRE(p1.value ==   0);
        REQUIRE(p2.value == 128);
        REQUIRE(p3.value == 255);
    }

    SECTION("construct by literals")
    {
        using namespace pnm::literals;

        const pnm::gray_pixel p1 =   0_gray;
        const pnm::gray_pixel p2 = 128_gray;
        const pnm::gray_pixel p3 = 255_gray;

        REQUIRE(p1.value ==   0);
        REQUIRE(p2.value == 128);
        REQUIRE(p3.value == 255);
    }
}


TEST_CASE("pixel type for ppm rgb color images", "[rgb_pixel]")
{
    static_assert(pnm::is_pixel<pnm::rgb_pixel>::value,
                  "rgb_pixel is a pixel type");

    SECTION("construct from bare values")
    {
        const pnm::rgb_pixel p1(0,   0,   0);
        const pnm::rgb_pixel p2(0, 128,   0);
        const pnm::rgb_pixel p3(1, 255, 128);

        REQUIRE(p1.red   == 0);
        REQUIRE(p1.green == 0);
        REQUIRE(p1.blue  == 0);

        REQUIRE(p2.red   == 0);
        REQUIRE(p2.green == 128);
        REQUIRE(p2.blue  == 0);

        REQUIRE(p3.red   == 1);
        REQUIRE(p3.green == 255);
        REQUIRE(p3.blue  == 128);
    }

    SECTION("construct by literals")
    {
        using namespace pnm::literals;

        const pnm::rgb_pixel p1 = 0x000000_rgb;
        const pnm::rgb_pixel p2 = 0x00FF00_rgb;
        const pnm::rgb_pixel p3 = 0xC0FFEE_rgb;

        REQUIRE(p1.red   == 0);
        REQUIRE(p1.green == 0);
        REQUIRE(p1.blue  == 0);

        REQUIRE(p2.red   == 0);
        REQUIRE(p2.green == 255);
        REQUIRE(p2.blue  == 0);

        REQUIRE(p3.red   == 0xC0);
        REQUIRE(p3.green == 0xFF);
        REQUIRE(p3.blue  == 0xEE);
    }
}


TEST_CASE("conversion between pixel types", "[convert pixel]")
{
    SECTION("bit -> gray")
    {
        const pnm::bit_pixel b1(true);
        const pnm::bit_pixel b2(false);

        const auto g1 = pnm::convert_to<pnm::gray_pixel>(b1);
        const auto g2 = pnm::convert_to<pnm::gray_pixel>(b2);

        REQUIRE(g1.value ==   0);
        REQUIRE(g2.value == 255);
    }

    SECTION("bit -> rgb")
    {
        const pnm::bit_pixel b1(true);
        const pnm::bit_pixel b2(false);

        const auto c1 = pnm::convert_to<pnm::rgb_pixel>(b1);
        const auto c2 = pnm::convert_to<pnm::rgb_pixel>(b2);

        REQUIRE(c1.red   ==   0);
        REQUIRE(c1.green ==   0);
        REQUIRE(c1.blue  ==   0);
        REQUIRE(c2.red   == 255);
        REQUIRE(c2.green == 255);
        REQUIRE(c2.blue  == 255);
    }

    SECTION("gray -> rgb")
    {
        const pnm::gray_pixel g1(0);
        const pnm::gray_pixel g2(128);
        const pnm::gray_pixel g3(255);

        const auto c1 = pnm::convert_to<pnm::rgb_pixel>(g1);
        const auto c2 = pnm::convert_to<pnm::rgb_pixel>(g2);
        const auto c3 = pnm::convert_to<pnm::rgb_pixel>(g3);

        REQUIRE(c1.red   == 0);
        REQUIRE(c1.green == 0);
        REQUIRE(c1.blue  == 0);

        REQUIRE(c2.red   == 128);
        REQUIRE(c2.green == 128);
        REQUIRE(c2.blue  == 128);

        REQUIRE(c3.red   == 255);
        REQUIRE(c3.green == 255);
        REQUIRE(c3.blue  == 255);
    }
}
