#pragma once

#include <math.h>

class vec4f{

    public:
        float x;
        float y;
        float z;
        float w;

        vec4f();
        vec4f(float x, float y, float z, float w);
        ~vec4f();

        float length() const;
        void operator=(const vec4f& attrib);
        void operator+=(const vec4f& attrib);
        void operator-=(const vec4f& attrib);
        const vec4f operator*(float scalar) const;
        const vec4f operator/(float scalar) const;

};

const vec4f operator+(const vec4f& first, const vec4f& second);

const vec4f operator-(const vec4f& first, const vec4f& second);

const vec4f operator*(float scalar, const vec4f& vec);

const vec4f operator/(float scalar, const vec4f& vec);