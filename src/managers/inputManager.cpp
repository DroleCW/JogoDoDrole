
#include "managers/inputManager.h"

bool InputManager::pressedKeys[Keys::NumberOfKeys];
bool InputManager::releasedKeys[Keys::NumberOfKeys];
bool InputManager::heldKeys[Keys::NumberOfKeys];

InputManager::InputManager(){

}

InputManager::~InputManager(){
    
}

bool InputManager::wasKeyPressed(Keys key){
    return pressedKeys[key];
}

bool InputManager::wasKeyReleased(Keys key){
    return releasedKeys[key];
}

bool InputManager::isKeyPressed(Keys key){
    return heldKeys[key];
}

void InputManager::pollEvents(){
    
    for(int i = 0; i < Keys::NumberOfKeys; i++){
        pressedKeys[i] = false;
        releasedKeys[i] = false;
    }
    glfwPollEvents();
}


void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        pressedKeys[key] = true;
        heldKeys[key] = true;
    }
    else if(action == GLFW_RELEASE){
        releasedKeys[key] = true;
        heldKeys[key] = false;
    }
}