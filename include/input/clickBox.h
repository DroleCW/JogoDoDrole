#pragma once

#include "math/vec2f.h"
#include "input/inputManager.h"

/*An object of this class is attached to anything that can be clicked. It is referenced to the inputManager
upon construction and will be updated when an event happens.*/
class ClickBox{
    protected:
        vec2f pos;
        vec2f size;

        bool hovering;
        unsigned int clicked;

        bool enabled;

    public:
        ClickBox(const vec2f& pos = {0.0f, 0.0f}, const vec2f& size = {0.0f, 0.0f});
        ~ClickBox();

        inline bool isHovering() const{
            return hovering;
        }
        inline bool wasClicked(MouseButtons button) const{
            return clicked & button;
        }

        void setBox(const vec2f& pos, const vec2f& size);

        inline void setClicked(int clicked){
            this->clicked |= clicked;
        }
        
        inline void clearClicked(int unclicked){
            this->clicked &= ~unclicked;
        }

        inline void clearClicked(){
            this->clicked = 0;
        }

        inline void setHovering(bool hovering){
            this->hovering = hovering;
        }

        inline void setPosition(const vec2f& pos){
            this->pos = pos;
        }

        inline const vec2f& getPosition() const{
            return pos;
        }

        inline void setSize(const vec2f& size){
            this->size = size;
        }

        inline const vec2f& getSize() const{
            return size;
        }
        //void hover();

        inline void setEnabled(bool enabled){
            this->enabled = enabled;
        }

        inline bool getEnabled(){
            return enabled;
        }
        

};
