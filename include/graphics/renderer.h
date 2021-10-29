#pragma once

#include "graphics/textureManager.h"
#include "graphics/shaderProgram.h"
#include "graphics/view.h"
#include "graphics/quad.h"

#define MAX_QUADS_PER_DRAW      1000
#define RENDERER_BUFFER_SIZE    MAX_QUADS_PER_DRAW*sizeof(Quad)

#define MAX_TEXTURE_SLOTS       16

#define VERTEX_SHADER_PATH "shaders/simpleTestVertexShader.sdv"
#define FRAGMENT_SHADER_PATH "shaders/simpleTestFragmentShader.sdf"

class Renderer{

    private:
        unsigned int rendererVertexBuffer;
        unsigned int rendererIndexBuffer;
        unsigned int rendererVertexArray;

        unsigned int bufferOffset;

        TextureLocation boundTextures[MAX_TEXTURE_SLOTS];
        unsigned int boundTexturesCount;
        unsigned int loadedQuads;
        int textureSlots[MAX_TEXTURE_SLOTS];

        ShaderProgram rendererShader;

        View rendererView;

        TextureManager* pTextureManager;
        

    public:
        Renderer(TextureManager* pTextureManager = nullptr, const View& view = {{0.0f, 0.0f}, {0.0f, 0.0f}, {-1.0f, 1.0f}, {2.0f, 2.0f}});
        ~Renderer();

        void clear();
        void renderQuad(const Quad& quad, TextureLocation texture);
        void render();

        inline void setRenderer(TextureManager* textureManager) {pTextureManager = textureManager;}
        inline void setView(const View& view) {rendererView = view;}

        
};