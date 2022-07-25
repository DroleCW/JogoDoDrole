#pragma once
#include "math/vec2f.h"
#include "math/vec4f.h"
#include "graphics/textureLocations.h"
#include <stdio.h>

struct Vertex{
    vec2f position;
    float layer;
    vec4f color;
    vec2f textureCoord;
};

/*A set of vertices forming a rectangle to be rendered on screen. This rectangle is filled with a texture.
Every quad, if not otherwise specified, will be referenced by the graphicManager upon construction and rendered
every frame while visible.*/
class Quad{
    private:
        TextureLocation texture;
        Vertex vertices[4];
        bool visible;

    public:
        /*A quad is by default referenced by the graphicManager to be rendered individualy, this behavior is
        unwanted in certain cases.*/
        Quad(bool autoIndex = true);
        ~Quad();

        void setPosition(const vec2f& pos);
        void move(const vec2f& delta);
        void setSize(const vec2f& size);
        vec2f getSize() const;

        void scale(float scalar);
        void setWidth(float width);
        void setHeight(float height);
        void setLayer(int layer);

        inline int getLayer() const{
            return (int)vertices[0].layer;
        }

        void setTexturePosition(const vec2f& pos);
        void moveTexture(const vec2f& delta);
        void setTextureSize(const vec2f&size);
        void setTextureWidth(float width);
        void setTextureHeight(float height);

        void setColor(vec4f colorRGBA);

        inline const vec2f& getTexturePosition() const{return vertices[0].textureCoord;}

        inline void setTexture(TextureLocation texture){this->texture = texture;}
        inline TextureLocation getTexture() const{return texture;}

        inline void setVisible(bool visible){this->visible = visible;}
        inline bool getVisible() const{return visible;}

        //get the raw vertex data for rendering
        const float* getDataf() const;

};