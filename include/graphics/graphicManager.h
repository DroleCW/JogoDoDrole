#pragma once
#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "graphics/text/text.h"
#include "graphics/window.h"
#include "graphics/particles/particleSystem.h"
#include <set>



class GraphicManager{
    private:
        static Renderer* pQuadRenderer;
        static std::set<Quad*> quads;
        static std::set<Text*> texts;
        static std::set<ParticleSystem*> particleSystems;

        GraphicManager();
        ~GraphicManager();

    public:
        static void init();
        static void terminate();

        static void openWindow(int width, int height, const char* name);

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