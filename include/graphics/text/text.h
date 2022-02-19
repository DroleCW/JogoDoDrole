#pragma once

#include "graphics/text/font.h"
#include <string>
#include <vector>
#include "graphics/image.h"

class Text{
    private:
        std::string content;
        Font* font;
        std::vector<Image> characters;
        vec2f pos;
        vec2f cursor;
        vec4f color;
        float layer;
        int index;
        float lineSpacing;


    public:
        Text();
        ~Text();

        void setText(const std::string& text);
        void appendText(const std::string& text);
        inline int getContentSize() const{
            return content.size();
        }

        void setFont(Font* font);
        inline Font* getFont() const{
            return font;
        }

        inline void setLineSpacing(float spacing){
            lineSpacing = spacing;
        }

        Image* getNextCharacter();
        void resetIterator();

        void setPosition(vec2f pos);
        void move(vec2f delta);

        void setColor(vec4f colorRGBA);
        void setLayer(float layer);

};