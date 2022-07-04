
#include "input/inputManager.h"
#include "input/clickable.h"

bool InputManager::pressedKeys[Keys::NumberOfKeys];
bool InputManager::releasedKeys[Keys::NumberOfKeys];
bool InputManager::heldKeys[Keys::NumberOfKeys];

vec2f InputManager::mousePos;
bool InputManager::pressedMouseButtons[NUMBER_OF_MOUSE_BUTTONS];
bool InputManager::heldMouseButtons[NUMBER_OF_MOUSE_BUTTONS];
bool InputManager::releasedMouseButtons[NUMBER_OF_MOUSE_BUTTONS];

std::vector<Clickable*> InputManager::clickables;
View InputManager::clickablesView;

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

void InputManager::addClickable(Clickable* clickable){
    clickables.push_back(clickable);
}

void InputManager::removeClickable(Clickable* clickable){
    for(auto i = clickables.begin(); i != clickables.end(); i++)
            if(*i == clickable){
                clickables.erase(i);
                break;
            }
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

    for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++){
        pressedMouseButtons[i] = false;
        releasedMouseButtons[i] = false;
    }

    glfwPollEvents();
    double mouseX, mouseY;
    glfwGetCursorPos(Window::getWindowHandle(), &mouseX, &mouseY);
    mousePos = {2*mouseX/Window::getWindowWidth()-1, -2*mouseY/Window::getWindowHeight()+1};

    for(auto i = clickables.begin(); i != clickables.end(); i++){
        if(!(*i)->getEnabled())
            continue;
            
        vec2f pos = (*i)->getPosition();
        vec2f size = (*i)->getSize();
        vec2f worldMousePos = getMousePosWorld(clickablesView);
        if(worldMousePos.x > pos.x && worldMousePos.x < pos.x+size.x && worldMousePos.y < pos.y && worldMousePos.y > pos.y-size.y){
            (*i)->setHovering(true);
            for(int j = 0; j < NUMBER_OF_MOUSE_BUTTONS; j++)
                if(pressedMouseButtons[j])
                    (*i)->setClicked(1<<j);
                else
                    (*i)->clearClicked(1<<j); 
        }
        else{
            (*i)->setHovering(false);
            (*i)->clearClicked();
        }
    }
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

void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        pressedMouseButtons[button] = true;
        heldMouseButtons[button] = true;
    }
    else if(action == GLFW_RELEASE){
        releasedMouseButtons[button] = true;
        heldMouseButtons[button] = false;
    }
}