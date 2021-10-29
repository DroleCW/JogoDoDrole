#pragma once
#include "math/vec2f.h"
#include "math/vec4f.h"

struct Vertex{
    vec2f position;
    vec4f color;
    vec2f textureCoord;
};

class Quad{
    private:
        Vertex vertices[4];

    public:
        Quad();
        ~Quad();

        void setPosition(const vec2f& pos);
        void move(const vec2f& delta);
        void setSize(const vec2f& size);
        void scale(float scalar);
        void setWidth(float width);
        void setHeight(float height);

        void setTexturePosition(const vec2f& pos);
        void setTextureSize(const vec2f&size);
        void setTextureWidth(float width);
        void setTextureHeight(float height);

        void setColor(vec4f colorRGBA);

        const float* getDataf() const;

};