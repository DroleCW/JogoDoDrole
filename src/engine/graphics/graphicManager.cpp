#include "graphics/graphicManager.h"

Renderer* GraphicManager::pQuadRenderer = nullptr;
std::set<Quad*> GraphicManager::quads;
std::set<Text*> GraphicManager::texts;
std::set<ParticleSystem*> GraphicManager::particleSystems;

void GraphicManager::init(){
    pQuadRenderer = new Renderer();
}

void GraphicManager::terminate(){
    delete pQuadRenderer;
}

void GraphicManager::openWindow(int width, int height, const char* name){
    Window::createWindow(width, height, name);
}

GraphicManager::GraphicManager(){

}

GraphicManager::~GraphicManager(){

}

void GraphicManager::addQuad(Quad* quad){
    quads.insert(quad);
}

void GraphicManager::removeQuad(Quad* quad){
    quads.extract(quad);
}

void GraphicManager::addText(Text* text){
    texts.insert(text);
}

void GraphicManager::removeText(Text* text){
    texts.extract(text);
}

void GraphicManager::addParticleSystem(ParticleSystem* particleSystem){
    particleSystems.insert(particleSystem);
}

void GraphicManager::removeParticleSystem(ParticleSystem* particleSystem){
    particleSystems.erase(particleSystem);
}

void GraphicManager::clear(){
    pQuadRenderer->clear();
}

void GraphicManager::render(){
    pQuadRenderer->clear();

    for(auto i = texts.begin(); i != texts.end(); i++){
        if((*i)->getVisible())
            pQuadRenderer->queueText(*i);
    }

    for(auto i = quads.begin(); i != quads.end(); i++){
        if((*i)->getVisible())
            pQuadRenderer->queueQuad(*i);
    }

    for(auto i = particleSystems.begin(); i != particleSystems.end(); i++)
        pQuadRenderer->queueParticles(*i);

    pQuadRenderer->render();

    Window::refresh();

}