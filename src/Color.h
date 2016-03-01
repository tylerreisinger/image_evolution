#ifndef COLOR_H_
#define COLOR_H_

template<typename T>
class Color {
public:
    Color() = default;
    constexpr Color(T red, T green, T blue, T alpha);
    ~Color() = default;

    Color(const Color& other) = default;
    Color(Color&& other) noexcept = default;
    Color& operator =(const Color& other) = default;
    Color& operator =(Color&& other) noexcept = default;

    T red;
    T green;
    T blue;
    T alpha;
};

template<typename T>
Color<T> alpha_blend(const Color<T>& c1, const Color<T>& c2) {
    T src_alpha = c1.alpha;
    T dest_alpha = c2.alpha;
    return Color<T>(c1.red * src_alpha + c2.red * dest_alpha,
            c1.green * src_alpha + c2.green * dest_alpha,
            c1.blue * src_alpha + c2.green * dest_alpha,
            dest_alpha);
}

using Colorf = Color<float>;

template<typename T>
inline constexpr Color<T>::Color(T red, T green, T blue, T alpha):
    red(red), green(green), blue(blue), alpha(alpha) {
 
}
 
#endif
