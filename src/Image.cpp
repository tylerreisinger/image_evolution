#include "Image.h"

#include <QImage>
#include <iostream>
#include <algorithm>

Image::Image(std::vector<float> pixels, int width, int height):
    m_bytes(std::move(pixels)), m_width(width), m_height(height)
{

}

Image::Image(int width, int height, const Colorf& fill_color):
    m_bytes(width*height*COMPONENT_COUNT), m_width(width), m_height(height)
{
    for(int i = 0; i < width*height; ++i){
        auto idx = i*COMPONENT_COUNT;
        m_bytes[idx] = fill_color.red;
        m_bytes[idx+1] = fill_color.green;
        m_bytes[idx+2] = fill_color.blue;
    }
}
 
Image::Image(Image&& other) noexcept:
    m_bytes(std::move(other.m_bytes)), m_width(other.m_width),
    m_height(other.m_height)
{
}
 
Image& Image::operator=(Image&& other) noexcept
{
    std::swap(other.m_bytes, m_bytes);
    m_width = other.m_width;
    m_height = other.m_height;
    return *this;
}
 
Image Image::load_image(const std::string& filename, const Colorf& bg_color) {
    QImage image;
    image.load(filename.c_str());
    
    image = image.convertToFormat(QImage::Format_ARGB32);
    auto image_data = image.constBits();
    
    std::size_t num_pixels = image.width() * image.height();
    std::vector<float> pixels(num_pixels*3);

    std::array<float, 3> bg_componets= {bg_color.red, bg_color.green, bg_color.blue};

    int i = 0;
    for(int px = 0; px < num_pixels; ++px) {
        float alpha = image_data[px*4+3] / 255.0;
        for(int comp = 0; comp < 3; ++comp) {
            auto component = static_cast<float>(image_data[px*4+2-comp]) / 255.0f;
            component = component * alpha + bg_componets[comp] * (1.0-alpha);
            pixels[i++] = component;
        }
    }

    return Image(std::move(pixels), image.width(), image.height()); 
}

void Image::draw_rectangle(int x_min, int y_min, int x_max, int y_max,
        const Colorf& src_color) {
    auto x_start = std::min(width()-1, x_min);
    auto y_start = std::min(height()-1, y_min);
    auto x_end = std::min(width()-1, x_max);
    auto y_end = std::min(height()-1, y_max);

    auto src_alpha = src_color.alpha;
    auto dest_alpha = 1.0 - src_alpha;

    auto stride = m_width*COMPONENT_COUNT;

    for(int y = y_start; y < y_end; ++y) {
        for(int idx = COMPONENT_COUNT*x_start+y*stride; idx < COMPONENT_COUNT*x_end+y*stride;) {
            m_bytes[idx] = src_color.red * src_alpha + m_bytes[idx] * dest_alpha;
            idx+=1;
            m_bytes[idx] = src_color.green * src_alpha + m_bytes[idx] * dest_alpha;
            idx+=1;
            m_bytes[idx] = src_color.blue * src_alpha + m_bytes[idx] * dest_alpha;
            idx+=1;
        }
    }
}
 
void Image::draw_rectangle(float x_min, float y_min, 
        float x_max, float y_max, const Colorf& src_color)
{
    draw_rectangle(int(x_min * width()), int(y_min * height()), int(x_max * width()),
            int(y_max * height()), src_color);
}
 
Image Image::clone() const
{
    Image new_image;
    new_image.m_bytes = m_bytes;
    new_image.m_width = m_width;
    new_image.m_height = m_height;

    return new_image;    
}
 
float image_difference(const Image& ref_image, const Image& test_image)
{
    if(ref_image.width() != test_image.width() || ref_image.height() != test_image.height()) {
        return -1.0;
    } 

    float image_dist = 0.0;

    for(int y = 0; y < ref_image.height(); ++y) {
        for(int x = 0; x < ref_image.width(); ++x) {
            auto idx = (x + y*ref_image.width())*Image::COMPONENT_COUNT;
            float color_dist = 0.0;
        
            color_dist += channel_distance(ref_image[idx], test_image[idx]);
            idx+=1;
            color_dist += channel_distance(ref_image[idx], test_image[idx]);
            idx+=1;
            color_dist += channel_distance(ref_image[idx], test_image[idx]);

            image_dist += color_dist;
        }
    }
    
    return image_dist;
}
 
float channel_distance(float channel1, float channel2)
{
    auto diff = channel1-channel2;
    return diff*diff; 
}
 
void save_image(const std::string& filename, const Image& image)
{
    QImage out_img(image.width(), image.height(), QImage::Format_RGB32);
    auto bytes = out_img.bits();
    auto src_bytes = image.bytes();

    for(int px = 0; px < image.width()*image.height(); ++px) {
        for(int comp = 0; comp < 3; ++comp) {
            bytes[px*4+comp] = src_bytes[px*3+2-comp] * 255.0;
        }
        bytes[px*4+3] = 255;

    }
    out_img.save(filename.c_str());
}
 
