#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>

class vec2 {
    public:
        vec2(float x, float y) {
            e[0] = x;
            e[1] = y;
        }
        float length2() const;

        float length() const;

        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }

        void make_unit_vector();

        vec2 operator-() { return vec2( -e[0], -e[1]); }

        float operator[](int i) const { return e[i]; }

        vec2 operator+=(const vec2 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            return *this;
        }

        vec2 operator-=(const vec2 &v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            return *this;
        }

        vec2 operator*=(const vec2 &v) {
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            return *this;
        }

    private:
        float e[2];
};


float dot(const vec2& v1, const vec2& v2);

float distance(const vec2& v1, const vec2& v2);

float distance2(const vec2& v1, const vec2& v2);

vec2 normalize(const vec2& v);

vec2 operator*(const vec2 &v, const float s);

vec2 operator*(const float s, const vec2 &v);

vec2 operator+(const vec2 &v1, const vec2 &v2);

vec2 operator/(const vec2 &v, const float s);

vec2 operator-(const vec2 &v1, const vec2 &v2);

std::ostream& operator<<(std::ostream& os, const vec2& v);

#endif // VEC3_H_
