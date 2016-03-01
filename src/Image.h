#ifndef IMAGE_H_
#define IMAGE_H_

#include <vector>
#include <string>
#include <cstdint>

#include "Color.h"

class Image {
public:
    static constexpr int COMPONENT_COUNT = 3;

    Image(int width, int height, const Colorf& fill_color);
    Image(std::vector<float> pixels, int width, int height);

    ~Image() = default;

    Image(const Image& other) = delete;
    Image(Image&& other) noexcept;
    Image& operator =(const Image& other) = delete;
    Image& operator =(Image&& other) noexcept; 

    float& operator [](std::size_t idx) {return m_bytes[idx];}
    const float& operator [](std::size_t idx) const {return m_bytes[idx];}

    static Image load_image(const std::string& filename, const Colorf& bg_color
            = Colorf(1.0, 1.0, 1.0, 1.0));

    void draw_rectangle(int x_min, int y_min, int x_max, int y_max, 
            const Colorf& src_color);
    void draw_rectangle(float x_min, float y_min, float x_max, float y_max, 
            const Colorf& src_color);

    const float* bytes() const {
        return m_bytes.data();
    }

    int width() const {return m_width;}
    int height() const {return m_height;}

    int pixel_count() const {return width()*height();}

    Image clone() const;

private:
    Image() = default;
    std::vector<float> m_bytes;
    int m_width;
    int m_height;
};

float image_difference(const Image& ref_image, const Image& test_image);

float channel_distance(float channel1, float channel2);

void save_image(const std::string& filename, const Image& image);

#endif
