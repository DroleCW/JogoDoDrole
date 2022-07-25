#include "game/gameStates/mainMenuState.h"
#include "game/gameStates/playState.h"
#include "engine/input/inputManager.h"

MainMenuState::MainMenuState(StateStack* gameStateStack):StateStack::State(gameStateStack){

    testView = View({0.0f, 0.0f}, {SCR_WIDTH, SCR_HEIGHT}, {-1.0f, 1.0f}, {2.0f, 2.0f});
    GraphicManager::setView(testView);

    FontManager::loadFont(FontLocation::TEST_FONT1_LOCATION, 50);
    initText.setFont(FontManager::getFont(FontLocation::TEST_FONT1_LOCATION, 50));
    initText.setLineSpacing(50);
    initText.setText("PRESSIONE 'A' PARA INICIAR");
    initText.setPosition({10.0f, 50.0f});
    initText.setColor({1.0f, 0.1f, 0.1f, 1.0f});
    initText.setLayer(8);
    initText.setVisible(true);
}

MainMenuState::~MainMenuState(){
    FontManager::unloadFont(FontLocation::TEST_FONT1_LOCATION, 10);
}

void MainMenuState::onActive(){
    initText.setVisible(true);
}

void MainMenuState::onInactive(){
    initText.setVisible(false);
}

void MainMenuState::update(){
    if(InputManager::wasKeyPressed(Keys::A)){
        stateStack->push(static_cast<StateStack::State*>(new PlayState(stateStack)));
    }
}