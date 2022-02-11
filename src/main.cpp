
#include <iostream>

#include "graphics/shaderProgram.h"
#include "graphics/textureManager.h"
#include "math/vec2f.h"
#include "graphics/renderer.h"
#include "graphics/sprite.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "managers/inputManager.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){


    Window mainWindow(SCR_WIDTH, SCR_HEIGHT, "abstracted window");
    InputManager mainInputManager;

    TextureManager testTextureManager;
    View testView({0.0f, 0.0f}, {800.0f, 600.0f});

    Renderer testRenderer(&testTextureManager, testView);

    testTextureManager.loadTexture(TEST_TEXTURE2_LOCATION);
    testTextureManager.loadTexture(TEST_TEXTURE3_LOCATION);

    Sprite testSprite(TEST_TEXTURE2_LOCATION);
    testSprite.setPosition({100.0f, 100.0f});
    testSprite.setSize({67.0f, 62.0f});
    testSprite.setColor({1.0f, 1.0f, 1.0f, 1.0f});
    testSprite.generateQuads({0.0f, 0.0f}, {201.0f, 251.0f}, 4, 3);

    Image testImage(TEST_TEXTURE3_LOCATION, {80.0f, 80.0f}, {180.0f, 220.0f});
    testImage.setPosition({300.0f, 300.0f});
    testImage.setSize({100.0f, 100.0f});
    testImage.setColor({0.0f, 1.0f, 1.0f, 1.0f});

    short i = 0;
    // render loop
    // -----------
    while (!mainWindow.getShouldClose()){

        i++;
        if(i > 60){
            i = 0;
            testSprite.nextQuad();
        }   
        
        testRenderer.clear();
        testRenderer.renderQuad(testSprite, testSprite.getTexture());
        testRenderer.renderQuad(testImage, testImage.getTexture());
        testRenderer.render();
        
        // swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        mainWindow.refresh();

    }
    return 0;
}

