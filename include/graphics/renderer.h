#pragma once

#include "graphics/textureManager.h"
#include "graphics/shaderProgram.h"
#include "graphics/view.h"
#include "graphics/quad.h"
#include "graphics/text/text.h"
#include "graphics/particles/particleSystem.h"

#include <map>

#define MAX_QUADS_PER_DRAW      1000
#define RENDERER_BUFFER_SIZE    MAX_QUADS_PER_DRAW*4*(sizeof(Vertex)+sizeof(float))

#define MAX_TEXTURE_SLOTS       16

#define VERTEX_SHADER_PATH "shaders/simpleTestVertexShader.sdv"
#define FRAGMENT_SHADER_PATH "shaders/simpleTestFragmentShader.sdf"

class Renderer{

    private:
        std::multimap<int, Quad*> quadBuffer;

        unsigned int rendererVertexBuffer;
        unsigned int rendererIndexBuffer;
        unsigned int rendererVertexArray;

        unsigned int bufferOffset;

        TextureLocation boundTextures[MAX_TEXTURE_SLOTS];
        int textureSlots[MAX_TEXTURE_SLOTS];
        unsigned int boundTexturesCount;
        unsigned int loadedQuads;

        ShaderProgram rendererShader;

        View rendererView;

        void renderBuffer(); 

    public:
        Renderer(const View& view = {{0.0f, 0.0f}, {0.0f, 0.0f}, {-1.0f, 1.0f}, {2.0f, 2.0f}});
        ~Renderer();

        void clear();
        bool renderQuad(Quad* quad);
        void queueQuad(Quad* quad);
        void queueParticles(ParticleSystem* particleSystem);
        void queueText(Text* quad);
        void render();

        inline void setView(const View& view) {rendererView = view;}
        
};