# Reference

## pixels

```cpp
template<typename T, std::size_t N>
struct basic_pixel;

template<typename T>
struct basic_pixel<T, 1>
{
  public:
    using value_type = T;
    static constexpr std::size_t colors = 1;

    basic_pixel()  = default;
    ~basic_pixel() = default;
    basic_pixel(const basic_pixel&) = default;
    basic_pixel(basic_pixel&&)      = default;
    basic_pixel& operator=(const basic_pixel&) = default;
    basic_pixel& operator=(basic_pixel&&)      = default;

// noexcept if T is nothrow constructible
    basic_pixel(const value_type& v);
    basic_pixel(value_type&& v);

    value_type value;
};

template<typename T>
struct basic_pixel<T, 3>
{
  public:
    using value_type = T;
    static constexpr std::size_t colors = 3;

    basic_pixel()  = default;
    ~basic_pixel() = default;
    basic_pixel(const basic_pixel&) = default;
    basic_pixel(basic_pixel&&)      = default;
    basic_pixel& operator=(const basic_pixel&) = default;
    basic_pixel& operator=(basic_pixel&&)      = default;

// noexcept if T is nothrow constructible
    basic_pixel(const value_type& R, const value_type& G, const value_type& B);
    basic_pixel(value_type&&      R, value_type&&      G, value_type&&      B);
    basic_pixel(const std::array<value_type, 3>& values);

    value_type red;
    value_type green;
    value_type blue;
};

using  bit_pixel = basic_pixel<bool,         1>;
using gray_pixel = basic_pixel<std::uint8_t, 1>;
using  rgb_pixel = basic_pixel<std::uint8_t, 3>;

namespace literals
{
inline namespace pixel_literals
{
bit_pixel  operator"" _bit (unsigned long long x);
gray_pixel operator"" _gray(unsigned long long x);
rgb_pixel  operator"" _rgb (unsigned long long x);
}
}

template<typename T> struct is_pixel;
template<typename From, typename To> struct is_narrowing_conversion;

template<typename ToPixel, typename FromPixel>
ToPixel convert_to(FromPixel&& pixel);
```

## images

```cpp
template<typename Pixel, typename Alloc = std::allocator<Pixel>>
class image
{
  public:
    using pixel_type                = Pixel;
    using allocator_type            = Alloc;
    using container_type            = std::vector<pixel_type, allocator_type>;
    using size_type                 = typename container_type::size_type;
    using difference_type           = typename container_type::difference_type;
    using value_type                = typename container_type::value_type;
    using pointer                   = typename container_type::pointer;
    using const_pointer             = typename container_type::const_pointer;
    using reference                 = typename container_type::reference;
    using const_reference           = typename container_type::const_reference;
    using iterator                  = typename container_type::iterator;
    using const_iterator            = typename container_type::const_iterator;
    using reverse_iterator          = typename container_type::reverse_iterator;
    using const_reverse_iterator    = typename container_type::const_reverse_iterator;
    using line_proxy                = /* internal proxy class */
    using const_line_proxy          = /* internal proxy class */
    using line_proxy_iterator       = /* internal proxy class */
    using const_line_proxy_iterator = /* internal proxy class */
    using line_range                = /* internal proxy class */
    using const_line_range          = /* internal proxy class */

    image()  = default;
    ~image() = default;
    image(const image&) = default;
    image(image&&)      = default;
    image& operator=(const image&) = default;
    image& operator=(image&&)      = default;

    image(const std::size_t width, const std::size_t height);
    image(const std::size_t width, const std::size_t height, const pixel_type& pix);

    template<typename T>
    image(const std::size_t width, const std::size_t height, const std::vector<T>& values)
    template<typename T>
    image(const std::vector<std::vector<T>>& values)

    line_proxy       operator[](const std::size_t i)       noexcept;
    const_line_proxy operator[](const std::size_t i) const noexcept;

    line_proxy       at(const std::size_t i);
    const_line_proxy at(const std::size_t i) const;

    reference       operator()(const std::size_t ix, const std::size_t iy)       noexcept;
    const_reference operator()(const std::size_t ix, const std::size_t iy) const noexcept;

    reference       at(const std::size_t ix, const std::size_t iy);
    const_reference at(const std::size_t ix, const std::size_t iy) const;

    reference       raw_access(const std::size_t i)       noexcept;
    const_reference raw_access(const std::size_t i) const noexcept;
    reference       raw_at(const std::size_t i);
    const_reference raw_at(const std::size_t i) const;

    std::size_t width()  const noexcept;
    std::size_t height() const noexcept;
    std::size_t x_size() const noexcept;
    std::size_t y_size() const noexcept;
    std::size_t size()   const noexcept;

    iterator       begin()        noexcept;
    iterator       end()          noexcept;
    const_iterator begin()  const noexcept;
    const_iterator end()    const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend()   const noexcept;

    reverse_iterator       rbegin()        noexcept;
    reverse_iterator       rend()          noexcept;
    const_reverse_iterator rbegin()  const noexcept;
    const_reverse_iterator rend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    line_proxy_iterator       line_begin()        noexcept;
    line_proxy_iterator       line_end()          noexcept;
    const_line_proxy_iterator line_begin()  const noexcept;
    const_line_proxy_iterator line_end()    const noexcept;
    const_line_proxy_iterator line_cbegin() const noexcept;
    const_line_proxy_iterator line_cend()   const noexcept;

    line_range       lines()       noexcept;
    const_line_range lines() const noexcept;
};

using pbm_image = image< bit_pixel>;
using pgm_image = image<gray_pixel>;
using ppm_image = image< rgb_pixel>;
```

## IO

```cpp
enum class format: bool {ascii, binary};

template<typename Pixel = rgb_pixel, typename Alloc = std::allocator<Pixel>>
image<Pixel, Alloc> read(const std::string& fname);
template<typename Pixel, typename Alloc>
void write(const std::string& fname, const image<Pixel, Alloc>& img, const format fmt);

template<typename Alloc = std::allocator<bit_pixel>>
image<bit_pixel, Alloc>  read_pbm(const std::string& fname);
template<typename Alloc = std::allocator<gray_pixel>>
image<gray_pixel, Alloc> read_pgm(const std::string& fname);
template<typename Alloc = std::allocator<rgb_pixel>>
image<rgb_pixel, Alloc>  read_ppm(const std::string& fname);


template<typename Alloc = std::allocator<bit_pixel>>
image<bit_pixel, Alloc> read_pbm_ascii(const std::string& fname);
template<typename Alloc = std::allocator<bit_pixel>>
image<bit_pixel, Alloc> read_pbm_binary(const std::string& fname);

template<typename Alloc = std::allocator<gray_pixel>>
image<gray_pixel, Alloc> read_pgm_ascii(const std::string& fname);
template<typename Alloc = std::allocator<gray_pixel>>
image<gray_pixel, Alloc> read_pgm_binary(const std::string& fname);

template<typename Alloc = std::allocator<rgb_pixel>>
image<rgb_pixel, Alloc> read_ppm_ascii(const std::string& fname);
template<typename Alloc = std::allocator<rgb_pixel>>
image<rgb_pixel, Alloc> read_ppm_binary(const std::string& fname);


template<typename Alloc>
void write_pbm(const std::string& fname, const image<bit_pixel, Alloc>& img, const format fmt);
template<typename Alloc>
void write_pgm(const std::string& fname, const image<gray_pixel, Alloc>& img, const format fmt);
template<typename Alloc>
void write_ppm(const std::string& fname, const image<rgb_pixel, Alloc>& img, const format fmt);

template<typename Alloc>
void write_pbm_ascii (const std::string& fname, const image<bit_pixel, Alloc>& img);
template<typename Alloc>
void write_pbm_binary(const std::string& fname, const image<bit_pixel, Alloc>& img);

template<typename Alloc>
void write_pgm_ascii (const std::string& fname, const image<gray_pixel, Alloc>& img);
template<typename Alloc>
void write_pgm_binary(const std::string& fname, const image<gray_pixel, Alloc>& img);

template<typename Alloc>
void write_ppm_ascii (const std::string& fname, const image<rgb_pixel, Alloc>& img);
template<typename Alloc>
void write_ppm_binary(const std::string& fname, const image<rgb_pixel, Alloc>& img);
```
