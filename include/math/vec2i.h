#pragma once

#include <math.h>

class vec2i{

    public:
        int x;
        int y;

        vec2i();
        vec2i(int x, int y);
        ~vec2i();

        float length() const;
        void operator=(const vec2i& attrib);
        void operator+=(const vec2i& attrib);
        void operator-=(const vec2i& attrib);
        const vec2i operator*(int scalar) const;
        const vec2i operator/(int scalar) const;

};

const vec2i operator+(const vec2i& first, const vec2i& second);

const vec2i operator-(const vec2i& first, const vec2i& second);

const vec2i operator*(int scalar, const vec2i& vec);

const vec2i operator/(int scalar, const vec2i& vec);