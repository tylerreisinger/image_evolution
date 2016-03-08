#include "Image.h"


#include <x86intrin.h>

#ifdef USE_SSE

__m128 abs_ps(__m128 x) {
    static const __m128 mask = _mm_set_ps1(-0.0f);
    return _mm_andnot_ps(mask, x);
}

void draw_rectangle_sse(Image& image, int x_min, int y_min, int x_max, int y_max,
        const Colorf& src_color) {

    //Clip the coordinates to the image dimensions
    int x_start = std::min(image.width()-1, x_min);
    int y_start = std::min(image.height()-1, y_min);
    int x_end = std::min(image.width()-1, x_max);
    int y_end = std::min(image.height()-1, y_max);

    //We assume the alpha of the background is always 1.
    float src_alpha_chan = src_color.alpha;
    float dest_alpha_chan = 1.0f - src_alpha_chan;

    //Pre-multiply the alpha and the rectangle colors as they are constant
    //for every pixel and it saves one multiply.
    float premul_red = src_color.red * src_alpha_chan;
    float premul_green = src_color.green * src_alpha_chan;
    float premul_blue = src_color.blue * src_alpha_chan;

    //Store the alpha in all four components of the float vector
    __m128 dest_alpha = _mm_set_ps1(dest_alpha_chan);
    //Load the premultiplied alphas into a packed vector. Because of endian-ness,
    //we will operate on channels in the opposite order.
    __m128 premul_src_color = _mm_set_ps(0.0f, premul_blue, premul_green, premul_red);

    __m128* pixels = reinterpret_cast<__m128*>(image.bytes());

    for(int y = y_start; y < y_end; ++y) {
        auto idx_start = y*image.width();
        auto end_idx = idx_start+x_end;
        for(int idx = idx_start+x_start; idx < end_idx; ++idx) {
            //pixel = (pixel*dest_alpha) + premul_src_color
#ifdef USE_FMA
            pixels[idx] = _mm_fmadd_ps(pixels[idx], dest_alpha, premul_src_color);
#else
            pixels[idx] = _mm_add_ps(premul_src_color, _mm_mul_ps(pixels[idx], dest_alpha));
#endif
        }
    }
}

double image_difference_sse(const Image& ref_image, const Image& test_image) {

    if(ref_image.width() != test_image.width() || 
            ref_image.height() != test_image.height()) {
        return -1.0;
    } 

    auto num_pixels = ref_image.width() * ref_image.height();

    const __m128* ref_pixels = reinterpret_cast<const __m128*>(ref_image.bytes());
    const __m128* test_pixels = reinterpret_cast<const __m128*>(test_image.bytes());

    //Stores two "half-sums", (alpha+blue, green+red). Adding these together at the
    //end is faster than doing it progressively.
    __m128d half_sums = _mm_set_pd(0.0, 0.0);

    //Sum BLOCK_SIZE pixels at a time before converting the partial
    //sums from float to double for extra precision. This should provide
    //very little precision loss while being faster than converting
    //each difference to a double and adding those.
    static constexpr int BLOCK_SIZE = 100;

    int num_blocks = num_pixels / BLOCK_SIZE;
    int remainder = num_pixels - num_blocks*BLOCK_SIZE;

    for(int blk = 0; blk < num_blocks; ++blk) {
        __m128 partial_component_sums = _mm_set_ps1(0.0f);
        auto idx_base = blk*BLOCK_SIZE;

        //Score each pixel in the block
        for(int i = 0; i < BLOCK_SIZE; ++i) {
            auto idx = idx_base+i;
            __m128 channel_distance = _mm_sub_ps(ref_pixels[idx], test_pixels[idx]);
            __m128 difference = _mm_mul_ps(channel_distance, channel_distance);
            partial_component_sums = _mm_add_ps(partial_component_sums, difference);
        }
        
        __m128 partial_half_sums = _mm_hadd_ps(partial_component_sums, partial_component_sums);
        __m128d double_partial_sums = _mm_cvtps_pd(partial_half_sums);
        half_sums = _mm_add_pd(half_sums, double_partial_sums);
    }

    //Score the last partial block
    __m128 partial_component_sums = _mm_set_ps1(0.0f);
    for(int i = 0; i < remainder; ++i) {
        auto idx = num_blocks*BLOCK_SIZE+i;
        __m128 channel_distance = _mm_sub_ps(ref_pixels[idx], test_pixels[idx]);
        channel_distance = abs_ps(channel_distance);
        partial_component_sums = _mm_add_ps(partial_component_sums, channel_distance);
    }
    
    __m128 partial_half_sums = _mm_hadd_ps(partial_component_sums, partial_component_sums);
    __m128d double_partial_sums = _mm_cvtps_pd(partial_half_sums);
    half_sums = _mm_add_pd(half_sums, double_partial_sums);

    //Sum the partial sums and copy the result to a scalar value.
    __m128d sums = _mm_hadd_pd(half_sums, half_sums);

    double image_dist;
    _mm_store_sd(&image_dist, sums);

    return image_dist;
}


#endif
