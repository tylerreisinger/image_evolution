#include "Image.h"

#include <QImage>
#include <iostream>
#include <algorithm>
#include <cmath>

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
        m_bytes[idx+3] = 0.0;
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
 
std::unique_ptr<Image> Image::load_image(const std::string& filename,
        const Colorf& bg_color) {
    QImage image;

    if(!image.load(filename.c_str())) {
        return nullptr; 
    }
    
    image = image.convertToFormat(QImage::Format_ARGB32);
    auto image_data = image.constBits();
    
    std::size_t num_pixels = image.width() * image.height();
    std::vector<float> pixels(num_pixels*COMPONENT_COUNT);

    std::array<float, 3> bg_componets= {bg_color.red, bg_color.green, bg_color.blue};

    int i = 0;
    for(int px = 0; px < num_pixels; ++px) {
        float alpha = image_data[px*4+3] / 255.0;
        for(int comp = 0; comp < 3; ++comp) {
            auto component = static_cast<float>(image_data[px*4+2-comp]) / 255.0f;
            component = component * alpha + bg_componets[comp] * (1.0-alpha);
            pixels[i++] = component;
        }
        i += 1;
    }

    return std::make_unique<Image>(std::move(pixels), image.width(), image.height()); 
}

void Image::draw_rectangle(int x_min, int y_min, int x_max, int y_max,
        const Colorf& src_color) {
#ifdef USE_SSE
    draw_rectangle_sse(*this, x_min, y_min, x_max, y_max, src_color);
#else
    draw_rectangle_slow(*this, x_min, y_min, x_max, y_max, src_color);
#endif
}
 
void Image::draw_rectangle(float x_min, float y_min, 
        float x_max, float y_max, const Colorf& src_color)
{
    draw_rectangle(int(x_min * width()), int(y_min * height()), int(x_max * width()),
            int(y_max * height()), src_color);
}
 
std::unique_ptr<Image> Image::clone() const
{
    auto new_image = std::unique_ptr<Image>(new Image());
    new_image->m_bytes = m_bytes;
    new_image->m_width = m_width;
    new_image->m_height = m_height;

    return new_image;    
}
 
double image_difference(const Image& ref_image, const Image& test_image)
{
#ifdef USE_SSE 
    return image_difference_sse(ref_image, test_image);
#else 
    return image_difference_slow(ref_image, test_image);
#endif
}
 
float channel_distance(float channel1, float channel2)
{
    auto diff = std::abs(channel1-channel2);
    return diff;
}
 
bool save_image(const std::string& filename, const Image& image)
{
    auto out_img = image.to_qimage();
    return out_img.save(filename.c_str());
}
 
QImage Image::to_qimage() const
{
    QImage out_img(width(), height(), QImage::Format_RGB32);
    auto bytes = out_img.bits();
    auto src_bytes = m_bytes;

    for(int px = 0; px < width()*height(); ++px) {
        for(int comp = 0; comp < 3; ++comp) {
            bytes[px*4+comp] = src_bytes[px*COMPONENT_COUNT+2-comp] * 255.0;
        }
        bytes[px*4+3] = 255;

    }

    return out_img;
}
 
void draw_rectangle_slow(Image& image, int x_min, int y_min, int x_max, int y_max,
        const Colorf& src_color) {
 
    auto x_start = std::min(image.width()-1, x_min);
    auto y_start = std::min(image.height()-1, y_min);
    auto x_end = std::min(image.width()-1, x_max);
    auto y_end = std::min(image.height()-1, y_max);

    float src_alpha = src_color.alpha;
    float dest_alpha = 1.0f - src_alpha;

    //Pre-multiply alpha into the rectangle color. This provides a significant
    //performance gain.
    float premul_red = src_color.red * src_alpha;
    float premul_green = src_color.green * src_alpha;
    float premul_blue = src_color.blue * src_alpha;

    auto stride = image.width()*image.COMPONENT_COUNT;

    auto bytes = image.bytes();

    for(int y = y_start; y < y_end; ++y) {
        auto y_start_idx = y*stride;
        for(int idx = image.COMPONENT_COUNT*x_start+y_start_idx; 
                idx < image.COMPONENT_COUNT*x_end+y_start_idx;) {
            bytes[idx] = premul_red + bytes[idx] * dest_alpha;
            idx+=1;
            bytes[idx] = premul_green + bytes[idx] * dest_alpha;
            idx+=1;
            bytes[idx] = premul_blue + bytes[idx] * dest_alpha;
            idx+=1;
            idx+=1;
        }
    }
}
 
double image_difference_slow(const Image& ref_image, const Image& test_image)
{
    if(ref_image.width() != test_image.width() ||
            ref_image.height() != test_image.height()) {
        return -1.0;
    } 

    double image_dist = 0.0;

    for(int y = 0; y < ref_image.height(); ++y) {
        for(int x = 0; x < ref_image.width(); ++x) {
            auto idx = (x + y*ref_image.width())*Image::COMPONENT_COUNT;
            double color_dist = 0.0;
        
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
 
std::unique_ptr<Image> Image::shrink_to_next_mipmap() const
{
    int new_width = width()>>1;
    int new_height = height()>>1;

    std::vector<float> new_pixels(new_width*new_height*COMPONENT_COUNT);

    int stride = width()*COMPONENT_COUNT;

    for(int y = 0; y < new_height; ++y) {
        for(int x = 0; x < new_width; ++x) {
            auto base_index = ((y*2)*width() + x*2)*COMPONENT_COUNT;

            for(int component = 0; component < COMPONENT_COUNT; ++component) {
                float value = m_bytes[base_index]
                    + m_bytes[base_index+COMPONENT_COUNT] 
                    + m_bytes[base_index+stride] 
                    + m_bytes[base_index+stride+COMPONENT_COUNT];
                value /= COMPONENT_COUNT;

                base_index += 1;
                new_pixels[(y*new_width + x)*COMPONENT_COUNT + component] = value;
            }
        }
    }

    return std::make_unique<Image>(std::move(new_pixels), new_width, new_height);
}
 
