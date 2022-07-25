#pragma once

#include "graphics/text/font.h"
#include <string>
#include <vector>
#include "graphics/image.h"

//A text to be rendered on screen
class Text{
    private:
        std::string content;
        Font* font;
        std::vector<Image> characters;
        vec2f pos;
        vec2f size;
        vec2f cursor;
        vec4f color;
        float layer;
        int index;
        float lineSpacing;
        bool visible;


    public:
        Text();
        ~Text();


        void setText(const std::string& text);
        void appendText(const std::string& text);

        //The size of the text's string in characters.
        inline int getContentSize() const{
            return content.size();
        }

        void setFont(Font* font);
        inline Font* getFont() const{
            return font;
        }

        //Space between lines.
        inline void setLineSpacing(float spacing){
            lineSpacing = spacing;
        }

        Image* getNextCharacter();
        void resetIterator();

        inline void setVisible(bool visible){
            this->visible = visible;
        }
        inline bool getVisible() const{
            return visible;
        }

        //Sets the position of the bottom left rectangle of the first letter of the first line.
        void setPosition(vec2f pos);
        void move(vec2f delta);

        //Multiplying color. As fonts are aways rendered to white, this is the actual color.
        void setColor(vec4f colorRGBA);
        void setLayer(float layer);

        //Size of the whole text boundaries.
        inline const vec2f& getSize() const{
            return size;
        }

};