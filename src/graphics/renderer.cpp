#include "graphics/renderer.h"

#include <glad/glad.h>
#include <cstring>

Renderer::Renderer(const View& view):rendererShader(), rendererView(view){

    boundTexturesCount = 0;
    quadBuffer.clear();

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10*sizeof(float), (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);
    //texture index
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10*sizeof(float), (void*)(9*sizeof(float)));
    glEnableVertexAttribArray(3);
}

Renderer::~Renderer(){
    glDeleteVertexArrays(1, &rendererVertexArray);
    glDeleteBuffers(1, &rendererVertexBuffer);
    glDeleteBuffers(1, &rendererIndexBuffer);
}

void Renderer::clear(){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
}

void Renderer::render(){
    unsigned int textureIndex;

    for(auto quadIt = quadBuffer.begin(); quadIt != quadBuffer.end(); quadIt++){
        if(!renderQuad(quadIt->second)){
            renderBuffer();
            renderQuad(quadIt->second);
        }
    }
    renderBuffer();
    quadBuffer.clear();
}

bool Renderer::renderQuad(Quad* quad){

    unsigned int textureIndex;
    for(textureIndex = 0; textureIndex < boundTexturesCount && boundTextures[textureIndex] != quad->getTexture(); textureIndex++);

    if(textureIndex == MAX_TEXTURE_SLOTS || loadedQuads == MAX_QUADS_PER_DRAW)
        return false;
    else{
        float renderData[40];
        memcpy(renderData, quad->getDataf(), sizeof(Vertex));
        renderData[9] = (float)textureIndex;
        memcpy(renderData+10, quad->getDataf()+9, sizeof(Vertex));
        renderData[19] = (float)textureIndex;
        memcpy(renderData+20, quad->getDataf()+18, sizeof(Vertex));
        renderData[29] = (float)textureIndex;
        memcpy(renderData+30, quad->getDataf()+27, sizeof(Vertex));
        renderData[39] = (float)textureIndex;

        glBindBuffer(GL_ARRAY_BUFFER, rendererVertexBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, loadedQuads*4*(sizeof(Vertex)+sizeof(float)), 4*(sizeof(Vertex)+sizeof(float)), renderData);
    
        if(textureIndex == boundTexturesCount){
            boundTexturesCount++;
            boundTextures[textureIndex] = quad->getTexture();
        }

        loadedQuads++;
        return true;
    }

}

void Renderer::queueQuad(Quad* quad){
    quadBuffer.insert({quad->getLayer(), quad});
}

void Renderer::queueText(Text* text){
    text->resetIterator();
    for(Image* quad = text->getNextCharacter(); quad != nullptr; quad = text->getNextCharacter())
        quadBuffer.insert({quad->getLayer(), quad});
}

void Renderer::queueParticles(ParticleSystem* particleSystem){
    particleSystem->resetIterator();
    for(Particle* quad = particleSystem->getNextLivingParticle(); quad != nullptr; quad = particleSystem->getNextLivingParticle())
        quadBuffer.insert({quad->getLayer(), quad});
    
}

void Renderer::renderBuffer(){
    rendererShader.bind();
    glBindVertexArray(rendererVertexArray);
    //view transform uniforms
    rendererShader.setUniform("worldTranslation", rendererView.getSourcePosition().x, rendererView.getSourcePosition().y);
    rendererShader.setUniform("scale", rendererView.getTargetSize().x/rendererView.getSourceSize().x, rendererView.getTargetSize().y/rendererView.getSourceSize().y);
    rendererShader.setUniform("screenTranslation", rendererView.getTargetPosition().x, rendererView.getTargetPosition().y);

    for(int i = 0; i < MAX_TEXTURE_SLOTS; i++)
        textureSlots[i] = i;
    rendererShader.setUniform("textureSampler", textureSlots, boundTexturesCount);

    for(unsigned int i = 0; i < boundTexturesCount; i++)
        TextureManager::bindTexture(boundTextures[i], i);
    
    glDrawElements(GL_TRIANGLES, 6*loadedQuads, GL_UNSIGNED_INT, 0);

    if(boundTexturesCount == MAX_TEXTURE_SLOTS || TextureManager::getLoadedTextures() > MAX_TEXTURE_SLOTS){
        boundTexturesCount = 0;
    }

    loadedQuads = 0;
    
}