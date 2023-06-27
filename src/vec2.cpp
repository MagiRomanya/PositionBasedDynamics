#include "vec2.hpp"
#include <cmath>
#include <math.h>

float vec2::length2() const { return dot(*this, *this); }

float vec2::length() const { return sqrt(length2()); }

void vec2::make_unit_vector() { *this / length(); }

float dot(const vec2& v1, const vec2& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y();
}

vec2 normalize(const vec2& v) { return v / v.length(); }

vec2 operator*(const vec2 &v, const float s) {
    return vec2(v.x() * s, v.y() * s);
}

vec2 operator*(const float s, const vec2 &v) {
    return vec2(v.x() * s, v.y() * s);
}

vec2 operator+(const vec2 &v1, const vec2 &v2){
    return vec2(v1.x() + v2.x(), v1.y() + v2.y());
}

vec2 operator/(const vec2 &v, const float s) {
    return v * 1.0f / s;
}

vec2 operator-(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.x() - v2.x(), v1.y() - v2.y());
}

std::ostream& operator<<(std::ostream& os, const vec2& v) {
    os << "(" << v.x() << "," << v.y() << ")";
    return os;
}

float distance(const vec2& v1, const vec2& v2) {
    return (v1 - v2).length();
}

float distance2(const vec2& v1, const vec2& v2) {
    return (v1 - v2).length();
}
