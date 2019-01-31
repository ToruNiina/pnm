#define CATCH_CONFIG_MAIN
#include <extlib/catch.hpp>
#include <pnm.hpp>
#include <random>

TEST_CASE("test access to pbm images", "[pbm access]")
{
    using namespace pnm::literals;

    pnm::image<pnm::bit_pixel> img(10, 10);
    for(std::size_t i=0; i<100; ++i)
    {
        img.raw_at(i) = (i < 50) ? 0_bit : 1_bit;
    }

    SECTION("access via line_proxy")
    {
        for(std::size_t y=0; y<5; ++y)
        {
            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(img[y][x] == 0_bit);
                REQUIRE(img[y][x] == 0_bit);
            }
        }
        for(std::size_t y=5; y<10; ++y)
        {
            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(img[y][x] == 1_bit);
                REQUIRE(img[y][x] == 1_bit);
            }
        }
    }

    SECTION("access via line_range")
    {
        std::size_t y = 0;
        for(const auto line : img.lines())
        {
            if(y < 5)
            {
                for(std::size_t x=0; x<10; ++x)
                {
                    REQUIRE(line.at(x) == 0_bit);
                    REQUIRE(line.at(x) == 0_bit);
                }
            }
            else
            {
                for(std::size_t x=0; x<10; ++x)
                {
                    REQUIRE(line.at(x) == 1_bit);
                    REQUIRE(line.at(x) == 1_bit);
                }
            }
            y++;
        }
    }
}

TEST_CASE("test access to pgm images", "[pgm access]")
{
    using namespace pnm::literals;

    pnm::image<pnm::gray_pixel> img(10, 10);
    for(std::size_t y=0; y<10; ++y)
    {
        const auto color =
            pnm::gray_pixel(static_cast<std::uint8_t>(256 * 0.1 * y));

        for(std::size_t x=0; x<10; ++x)
        {
            img.raw_at(y * 10 + x) = color;
        }
    }

    SECTION("access via line_proxy")
    {
        for(std::size_t y=0; y<10; ++y)
        {
            const auto color =
                pnm::gray_pixel(static_cast<std::uint8_t>(256 * 0.1 * y));

            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(img[y][x] == color);
                REQUIRE(img[y][x] == color);
            }
        }
    }

    SECTION("access via line_range")
    {
        std::size_t y = 0;
        for(const auto line : img.lines())
        {
            const auto color =
                pnm::gray_pixel(static_cast<std::uint8_t>(256 * 0.1 * y));
            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(line.at(x) == color);
                REQUIRE(line.at(x) == color);
            }
            y++;
        }
    }
}

TEST_CASE("test access to ppm images", "[ppm access]")
{
    using namespace pnm::literals;

    pnm::image<pnm::rgb_pixel> img(10, 10);
    for(std::size_t y=0; y<10; ++y)
    {
        const auto color = pnm::rgb_pixel(
                static_cast<std::uint8_t>(256 * 0.1 * y),
                static_cast<std::uint8_t>(255 - 256 * 0.1 * y),
                static_cast<std::uint8_t>(0)
            );

        for(std::size_t x=0; x<10; ++x)
        {
            img.raw_at(y * 10 + x) = color;
        }
    }

    SECTION("access via line_proxy")
    {
        for(std::size_t y=0; y<10; ++y)
        {
            const auto color = pnm::rgb_pixel(
                    static_cast<std::uint8_t>(256 * 0.1 * y),
                    static_cast<std::uint8_t>(255 - 256 * 0.1 * y),
                    static_cast<std::uint8_t>(0)
                );

            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(img[y][x] == color);
                REQUIRE(img[y][x] == color);
            }
        }
    }


    SECTION("access via line_range")
    {
        const auto lines = img.lines();
        std::size_t y = 0;
        for(const auto line : img.lines())
        {
            const auto color = pnm::rgb_pixel(
                    static_cast<std::uint8_t>(256 * 0.1 * y),
                    static_cast<std::uint8_t>(255 - 256 * 0.1 * y),
                    static_cast<std::uint8_t>(0)
                );
            for(std::size_t x=0; x<10; ++x)
            {
                REQUIRE(line.at(x) == color);
                REQUIRE(line.at(x) == color);
            }
            y++;
        }
    }
}
