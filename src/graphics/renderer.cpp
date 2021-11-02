#include "graphics/renderer.h"

#include <glad/glad.h>

Renderer::Renderer(TextureManager* pTextureManager, const View& view):rendererShader(), rendererView(view){

    this->pTextureManager = pTextureManager;
    boundTexturesCount = 0;

    for(int i = 0; i < MAX_TEXTURE_SLOTS; i++)
        textureSlots[i] = i;

    //shader setup
    rendererShader.addShaderFromFile(VERTEX_SHADER_PATH);
    rendererShader.addShaderFromFile(FRAGMENT_SHADER_PATH);
    rendererShader.link();

    //vertex array setup
    glGenVertexArrays(1, &rendererVertexArray);
    glBindVertexArray(rendererVertexArray);

    //vertex buffer setup
    glGenBuffers(1, &rendererVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rendererVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);


    //index buffer setup
    unsigned int indices[MAX_QUADS_PER_DRAW*6];
    for(int i = 0; i < MAX_QUADS_PER_DRAW; i++){
        indices[6*i]   = 0 + 4*i;
        indices[6*i+1] = 1 + 4*i;
        indices[6*i+2] = 2 + 4*i;

        indices[6*i+3] = 0 + 4*i;
        indices[6*i+4] = 2 + 4*i;
        indices[6*i+5] = 3 + 4*i;
    }

    glGenBuffers(1, &rendererIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_QUADS_PER_DRAW, indices, GL_STATIC_DRAW);

    //vertex attributes setup
    //position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    //texture index
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(8*sizeof(float)));
    glEnableVertexAttribArray(3);
}

Renderer::~Renderer(){
    glDeleteVertexArrays(1, &rendererVertexArray);
    glDeleteBuffers(1, &rendererVertexBuffer);
    glDeleteBuffers(1, &rendererIndexBuffer);
}

void Renderer::clear(){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderQuad(const Quad& quad, TextureLocation texture){


    unsigned int textureIndex;
    for(textureIndex = 0; textureIndex < boundTexturesCount && boundTextures[textureIndex]; textureIndex++);

    if(textureIndex < MAX_TEXTURE_SLOTS && loadedQuads < MAX_QUADS_PER_DRAW){
        float renderData[36];
        memcpy(renderData, quad.getDataf(), sizeof(Vertex));
        renderData[8] = (float)textureIndex;
        memcpy(renderData+9, quad.getDataf()+8, sizeof(Vertex));
        renderData[17] = (float)textureIndex;
        memcpy(renderData+18, quad.getDataf()+16, sizeof(Vertex));
        renderData[26] = (float)textureIndex;
        memcpy(renderData+27, quad.getDataf()+24, sizeof(Vertex));
        renderData[35] = (float)textureIndex;

        glBindBuffer(GL_ARRAY_BUFFER, rendererVertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, loadedQuads*4*(sizeof(Vertex)+sizeof(float)), 4*(sizeof(Vertex)+sizeof(float)), renderData);
    
        if(textureIndex == boundTexturesCount){
            boundTexturesCount++;
            boundTextures[textureIndex] = texture;
        }

        loadedQuads++;
    }
    else{
        render();
        renderQuad(quad, texture);
    }

}

void Renderer::render(){

    rendererShader.bind();
    glBindVertexArray(rendererVertexArray);
    //view transform uniforms
    rendererShader.setUniform("worldTranslation", rendererView.getSourcePosition().x, rendererView.getSourcePosition().y);
    rendererShader.setUniform("scale", rendererView.getTargetSize().x/rendererView.getSourceSize().x, rendererView.getTargetSize().y/rendererView.getSourceSize().y);
    rendererShader.setUniform("screenTranslation", rendererView.getTargetPosition().x, rendererView.getTargetPosition().y);


    //texture uniforms
    rendererShader.setUniform("textureSampler", textureSlots, boundTexturesCount);

    for(unsigned int i = 0; i < boundTexturesCount; i++)
        pTextureManager->bindTexture(boundTextures[i], i);

    glDrawElements(GL_TRIANGLES, 6*loadedQuads, GL_UNSIGNED_INT, 0);

    boundTexturesCount = 0;
    loadedQuads = 0;
}