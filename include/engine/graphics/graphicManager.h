#pragma once
#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "graphics/text/text.h"
#include "graphics/window.h"
#include "graphics/particles/particleSystem.h"
#include <set>


#define SCR_WIDTH 800
#define SCR_HEIGHT 600

//indexes all renderable objects and renders them with a given view.
class GraphicManager{
    private:
        static Renderer* pQuadRenderer;
        static std::set<Quad*> quads;
        static std::set<Text*> texts;
        static std::set<ParticleSystem*> particleSystems;

        GraphicManager();
        ~GraphicManager();

    public:
        //The graphics manager can only be initialized with an open window
        static void init();
        static void terminate();

        //opens a window and initializes OpenGL, it must be called before init.
        static void openWindow(int width, int height, const char* name);

        inline static float getWindowTime(){
            return glfwGetTime();
        }

        inline static bool getWindowShouldClose(){
           return Window::getShouldClose();
        }

        inline static void setWindowShouldClose(){
            Window::setShouldClose();
        }

        inline static void setView(const View& view){
            pQuadRenderer->setView(view);
        }

        static void addQuad(Quad* quad);
        static void removeQuad(Quad* quad);

        static void addText(Text* text);
        static void removeText(Text* text);

        static void addParticleSystem(ParticleSystem* particleSystem);
        static void removeParticleSystem(ParticleSystem* particleSystem);

        static void clear();
        static void render();
};