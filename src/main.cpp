
#include <iostream>

#include "engine/math/vec2f.h"
#include "engine/input/inputManager.h"
#include "engine/sound/soundManager.h"
#include "engine/graphics/graphicManager.h"
#include "engine/graphics/text/fontManager.h"
#include "engine/physics/collisionManager.h"
#include "engine/stateMachine/stateStack.h"
#include "game/gameStates/mainMenuState.h"



#include <string>

#define TICK_TIME 1.0f/60.0f

// settings


int main(){
    printf("main\n");
    //initializing static managers
    GraphicManager::openWindow(SCR_WIDTH, SCR_HEIGHT, "abstracted window");
    TextureManager::init();
    GraphicManager::init();
    FontManager::init();
    SoundManager::init();

  
    StateStack* gameStateStack = new StateStack;
    gameStateStack->push(static_cast<StateStack::State*>(new MainMenuState(gameStateStack)));

    // render loop
    // -----------
    
    double currentTime, previousTime, dt;
    double updateTimer = 0;
    previousTime = GraphicManager::getWindowTime();

    while (!GraphicManager::getWindowShouldClose()){

        currentTime = GraphicManager::getWindowTime();
        dt = currentTime-previousTime;
        previousTime = currentTime;

        updateTimer += dt;
        
        while(updateTimer >= TICK_TIME){
            gameStateStack->update();
            updateTimer -= TICK_TIME;
        }

        GraphicManager::render();
        
        // swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        InputManager::pollEvents();

    }

   

    //terminating managers
    SoundManager::terminate();//because the sources are in the stack and persist until the return, this will cause errors. It will not happen in a real situation.
    FontManager::terminate();
    GraphicManager::terminate();
    TextureManager::terminate();

    return 0;
}

