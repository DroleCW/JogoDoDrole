
#include "managers/inputManager.h"

bool InputManager::pressedKeys[Keys::NumberOfKeys];
bool InputManager::releasedKeys[Keys::NumberOfKeys];
bool InputManager::heldKeys[Keys::NumberOfKeys];
vec2f InputManager::mousePos;

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

vec2f InputManager::getMousePosScreen(){
    return mousePos;
}

vec2f InputManager::getMousePosWorld(const View& view){
    vec2f pos = mousePos - view.getTargetPosition();
    vec2f scalingFactor = view.getScalingFactor();
    pos.x /= scalingFactor.x;
    pos.y /= -scalingFactor.y; //world y grows downwards, NDC y grows upwards
    return pos + view.getSourcePosition();
}

void InputManager::pollEvents(){
    
    for(int i = 0; i < Keys::NumberOfKeys; i++){
        pressedKeys[i] = false;
        releasedKeys[i] = false;
    }
    glfwPollEvents();
    double mouseX, mouseY;
    glfwGetCursorPos(Window::getWindowHandle(), &mouseX, &mouseY);
    mousePos = {2*mouseX/Window::getWindowWidth()-1, -2*mouseY/Window::getWindowHeight()+1};
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