#pragma once

#include <math.h>

class vec2f{

    public:
        float x;
        float y;

        vec2f();
        vec2f(float x, float y);
        ~vec2f();

        float length() const;
        void operator=(const vec2f& attrib);
        void operator+=(const vec2f& attrib);
        void operator-=(const vec2f& attrib);
        const vec2f operator*(float scalar) const;
        const vec2f operator/(float scalar) const;

};

const vec2f operator+(const vec2f& first, const vec2f& second);

const vec2f operator-(const vec2f& first, const vec2f& second);

const vec2f operator*(float scalar, const vec2f& vec);

const vec2f operator/(float scalar, const vec2f& vec);