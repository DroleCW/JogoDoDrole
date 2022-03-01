#include "graphics/graphicManager.h"

Renderer* GraphicManager::pQuadRenderer = nullptr;
std::set<Quad*> GraphicManager::quads;
std::set<Text*> GraphicManager::texts;

void GraphicManager::init(){
    pQuadRenderer = new Renderer();
}

void GraphicManager::terminate(){
    delete pQuadRenderer;
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

void GraphicManager::clear(){
    pQuadRenderer->clear();
}

void GraphicManager::render(){
    for(auto i = quads.begin(); i != quads.end(); i++){
        pQuadRenderer->renderQuad(*i);
    }
    for(auto i = texts.begin(); i != texts.end(); i++){
        pQuadRenderer->renderText(*i);
    }
    pQuadRenderer->render();
}