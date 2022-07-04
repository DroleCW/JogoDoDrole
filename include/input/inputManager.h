#pragma once

#include "graphics/graphicManager.h"

class Clickable;

//keyboard enum, maps from glfw
enum Keys{
    Unknown = GLFW_KEY_UNKNOWN,
    Space = GLFW_KEY_SPACE,
    Apostrophe = GLFW_KEY_APOSTROPHE, /* ' */
    Comma = GLFW_KEY_COMMA, /* , */
    Minus = GLFW_KEY_MINUS, /* - */
    Period = GLFW_KEY_PERIOD, /* . */
    Slash = GLFW_KEY_SLASH, /* / */
    Number_0 = GLFW_KEY_0,
    Number_1 = GLFW_KEY_1,
    Number_2 = GLFW_KEY_2,
    Number_3 = GLFW_KEY_3,
    Number_4 = GLFW_KEY_4,
    Number_5 = GLFW_KEY_5,
    Number_6 = GLFW_KEY_6,
    Number_7 = GLFW_KEY_7,
    Number_8 = GLFW_KEY_8,
    Number_9 = GLFW_KEY_9,
    Semicolon = GLFW_KEY_SEMICOLON, /* ; */
    Equal = GLFW_KEY_EQUAL,/* = */
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    Left_Bracket = GLFW_KEY_LEFT_BRACKET,/* [ */
    Backslash = GLFW_KEY_BACKSLASH,/* \ */
    Right_Bracket = GLFW_KEY_RIGHT_BRACKET,/* ] */
    Grave_Accent = GLFW_KEY_GRAVE_ACCENT,/* ` */
    World_1 = GLFW_KEY_WORLD_1,/* non-US #1 */
    World_2 = GLFW_KEY_WORLD_2, /* non-US #2 */
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
    TAB = GLFW_KEY_TAB,
    backspace = GLFW_KEY_BACKSPACE,
    Insert = GLFW_KEY_INSERT,
    Delete = GLFW_KEY_DELETE,
    Arrow_Right = GLFW_KEY_RIGHT,
    Arrow_Left = GLFW_KEY_LEFT,
    Arrow_Down = GLFW_KEY_DOWN,
    Arrow_Up = GLFW_KEY_UP,
    Page_Up = GLFW_KEY_PAGE_UP,
    page_Down = GLFW_KEY_PAGE_DOWN,
    Home = GLFW_KEY_HOME,
    End = GLFW_KEY_END,
    Caps_Lock = GLFW_KEY_CAPS_LOCK,
    Scroll_Lock = GLFW_KEY_SCROLL_LOCK,
    Num_Lock = GLFW_KEY_NUM_LOCK,
    Print_Screen = GLFW_KEY_PRINT_SCREEN,
    Pause = GLFW_KEY_PAUSE,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    F13 = GLFW_KEY_F13,
    F14 = GLFW_KEY_F14,
    F15 = GLFW_KEY_F15,
    F16 = GLFW_KEY_F16,
    F17 = GLFW_KEY_F17,
    F18 = GLFW_KEY_F18,
    F19 = GLFW_KEY_F19,
    F20 = GLFW_KEY_F20,
    F21 = GLFW_KEY_F21,
    F22 = GLFW_KEY_F22,
    F23 = GLFW_KEY_F23,
    F24 = GLFW_KEY_F24,
    F25 = GLFW_KEY_F25,
    Keypad_0 = GLFW_KEY_KP_0,
    Keypad_1 = GLFW_KEY_KP_1,
    Keypad_2 = GLFW_KEY_KP_2,
    Keypad_3 = GLFW_KEY_KP_3,
    Keypad_4 = GLFW_KEY_KP_4,
    Keypad_5 = GLFW_KEY_KP_5,
    Keypad_6 = GLFW_KEY_KP_6,
    Keypad_7 = GLFW_KEY_KP_7,
    Keypad_8 = GLFW_KEY_KP_8,
    Keypad_9 = GLFW_KEY_KP_9,
    Keypad_Decimal = GLFW_KEY_KP_DECIMAL,
    Keypad_Divide = GLFW_KEY_KP_DIVIDE,
    Keypad_Multiply = GLFW_KEY_KP_MULTIPLY,
    Keypad_Subtract = GLFW_KEY_KP_SUBTRACT,
    Keypad_Add = GLFW_KEY_KP_ADD,
    Keypad_Enter = GLFW_KEY_KP_ENTER,
    Keypad_Equal = GLFW_KEY_KP_EQUAL,
    Left_Shift = GLFW_KEY_LEFT_SHIFT,
    Left_Control = GLFW_KEY_LEFT_CONTROL,
    Left_Alt = GLFW_KEY_LEFT_ALT,
    Left_Super = GLFW_KEY_LEFT_SUPER,
    Right_Shift = GLFW_KEY_RIGHT_SHIFT,
    Right_Control = GLFW_KEY_RIGHT_CONTROL,
    Right_Alt = GLFW_KEY_RIGHT_ALT,
    Right_Super = GLFW_KEY_RIGHT_SUPER,
    Menu = GLFW_KEY_MENU,
    NumberOfKeys
};

enum MouseButtons{
    MouseButton_1 = 1 << GLFW_MOUSE_BUTTON_1,
    MouseButton_2 = 1 << GLFW_MOUSE_BUTTON_2,
    MouseButton_3 = 1 << GLFW_MOUSE_BUTTON_3,
    MouseButton_4 = 1 << GLFW_MOUSE_BUTTON_4,
    MouseButton_5 = 1 << GLFW_MOUSE_BUTTON_5,
    MouseButton_6 = 1 << GLFW_MOUSE_BUTTON_6,
    MouseButton_7 = 1 << GLFW_MOUSE_BUTTON_7,
    MouseButton_8 = 1 << GLFW_MOUSE_BUTTON_8
};

#define NUMBER_OF_MOUSE_BUTTONS 8

class InputManager{
    private:
        static bool pressedKeys[Keys::NumberOfKeys];
        static bool heldKeys[Keys::NumberOfKeys];
        static bool releasedKeys[Keys::NumberOfKeys];

        static bool pressedMouseButtons[NUMBER_OF_MOUSE_BUTTONS];
        static bool heldMouseButtons[NUMBER_OF_MOUSE_BUTTONS];
        static bool releasedMouseButtons[NUMBER_OF_MOUSE_BUTTONS];

        static vec2f mousePos;

        static View clickablesView;

        static std::vector<Clickable*> clickables;

        InputManager();
        ~InputManager();
    public:

        static bool wasKeyPressed(Keys key);
        static bool wasKeyReleased(Keys key);
        static bool isKeyPressed(Keys key);

        static void addClickable(Clickable* clickable);
        static void removeClickable(Clickable* clickable);
        inline static void setClickablesView(const View& view){
            clickablesView = view;
        }

        static vec2f getMousePosScreen();//mouse position on screen (NDC)
        static vec2f getMousePosWorld(const View& view);//undoes the view transform and returns the position the cursor would have in the world

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void pollEvents();
};

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);