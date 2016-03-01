#ifndef POINT_H_
#define POINT_H_

template<typename T>
class Point {
public:
    Point() = delete;
    ~Point() = default;

    Point(const Point& other) = default;
    Point(Point&& other) noexcept = default;
    Point& operator =(const Point& other) = default;
    Point& operator =(Point&& other) noexcept = default;

    T x;
    T y; 
};

#endif
