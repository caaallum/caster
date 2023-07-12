#ifndef __VECTOR2_H
#define __VECTOR2_H

template <typename T>
class Vector2 {
public:
    T x, y;

    explicit Vector2() : x(0), y(x) {}
    
    Vector2(T x, T y) : x(x), y(y) {}

    template<typename U>
    Vector2(U x, U y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

    template<typename U>
    Vector2(Vector2<U> v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
};

#endif /* __VECTOR2_H */
