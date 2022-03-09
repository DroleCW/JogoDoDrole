
#include <iostream>

#include "graphics/shaderProgram.h"
#include "graphics/textureManager.h"
#include "math/vec2f.h"
#include "graphics/sprite.h"
#include "graphics/image.h"
#include "managers/inputManager.h"
#include "graphics/text/fontManager.h"
#include "graphics/text/text.h"
#include "sound/soundManager.h"
#include "graphics/graphicManager.h"

#include <string>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){
    printf("main\n");
    //initializing static managers
    GraphicManager::openWindow(SCR_WIDTH, SCR_HEIGHT, "abstracted window");
    TextureManager::init();
    GraphicManager::init();
    FontManager::init();
    SoundManager::init();

    
    
    FontManager::loadFont(TEST_FONT1_LOCATION, 50);

    //creating a text with the loaded font and setting its properties
    Text testText;
    testText.setFont(FontManager::getFont(TEST_FONT1_LOCATION, 50));
    testText.setLineSpacing(50);
    testText.setText("DroleDrile");
    testText.appendText("\nDrule");
    testText.setPosition({10.0f, 50.0f});
    testText.setColor({1.0f, 0.1f, 0.1f, 1.0f});
    testText.setLayer(8);

    //setting a view to the whole screen
    View testView({0.0f, 0.0f}, {800.0f, 600.0f}, {-1.0f, 1.0f}, {2.0f, 2.0f});
    GraphicManager::setView(testView);

    TextureManager::loadTexture(TEST_TEXTURE2_LOCATION);
    TextureManager::loadTexture(TEST_TEXTURE3_LOCATION);
    TextureManager::loadTexture(TEST_TEXTURE4_LOCATION);

    //making an animated sprite from a loaded texture
    Sprite testSprite(TEST_TEXTURE2_LOCATION);
    testSprite.setPosition({100.0f, 100.0f});
    testSprite.setSize({67.0f, 62.0f});
    testSprite.setColor({1.0f, 1.0f, 1.0f, 1.0f});
    testSprite.generateQuads({0.0f, 0.0f}, {201.0f, 251.0f}, 4, 3);
    testSprite.setLayer(5);

    //making a still image from a loaded texture
    Image testImage(TEST_TEXTURE3_LOCATION, {80.0f, 80.0f}, {180.0f, 220.0f});
    vec2f testImagePos(300.0f, 300.0f);
    testImage.setPosition({300.0f, 300.0f});
    testImage.setSize({100.0f, 100.0f});
    testImage.setColor({0.0f, 1.0f, 1.0f, 1.0f});
    testImage.setLayer(30);

    ParticleSystem testParticleSystem;
    testParticleSystem.setTexture(TEST_TEXTURE4_LOCATION);
    testParticleSystem.setTexturePosition({0.0f, 0.0f});
    testParticleSystem.setTextureSize({801.0f, 598.0f});
    testParticleSystem.setPosition({300.0f, 300.0f});
    testParticleSystem.setPositionRange({0.0f, 0.0f}, {0.0f, 0.0f});
    testParticleSystem.setVelocityRange({-100.0f, -100.0f}, {100.0f, 100.0f});
    testParticleSystem.setParticleSize({50.0f, 50.0f});
    testParticleSystem.setLifetimeRange(3, 4);
    testParticleSystem.setLayer(10);

    
    SoundManager::loadSound(TEST_SOUND1_LOCATION);
    SoundManager::loadSound(TEST_SOUND2_LOCATION);
    SoundSource testSoundSource1;
    SoundSource testSoundSource2;

    //all MONO sounds will be played as heard from a listener in the center of the 2D screen and 1 screen width away from it.
    //the idea is to simulate your head's position in the scene
    SoundManager::setListenerPosition({SCR_WIDTH/2.0f, SCR_HEIGHT/2.0f}, SCR_WIDTH);

    //creating a streaming audio source
    testSoundSource1.queueSound(TEST_SOUND1_LOCATION);
    testSoundSource1.play();

    //attaching a sound to an audio source
    testSoundSource2.attachSound(TEST_SOUND2_LOCATION);
    testSoundSource2.setReferenceDistance(SCR_WIDTH/2.0f);

    short i = 0;
    // render loop
    // -----------
    while (!GraphicManager::getWindowShouldClose()){
        i++;
        if(i > 60){
            i = 0;
            testSprite.nextQuad();
            testParticleSystem.emit();
        }

        testParticleSystem.update(0.01);
        //WASD will update the position of the test image
        if(InputManager::isKeyPressed(Keys::D)){
            testImagePos += {2.0f, 0.0f};
        }
        if(InputManager::isKeyPressed(Keys::W)){
            testImagePos += {0.0f, -2.0f};
        }
        if(InputManager::isKeyPressed(Keys::A)){
            testImagePos += {-2.0f, 0.0f};
        }
        if(InputManager::isKeyPressed(Keys::S)){
            testImagePos += {0.0f, 2.0f};
        }

        //G will play a sound roughly where the test image is
        if(InputManager::wasKeyPressed(Keys::G)){           
            testSoundSource2.play();
        }
        testImage.setPosition(testImagePos);
        testSoundSource2.setPosition(testImagePos);

        GraphicManager::render();
        
        // swap buffers and poll IO events
        // -------------------------------------------------------------------------------
        InputManager::pollEvents();

    }

    //unloading sounds
    testSoundSource1.clear();
    testSoundSource2.clear();
    SoundManager::unloadSound(TEST_SOUND1_LOCATION);
    SoundManager::unloadSound(TEST_SOUND2_LOCATION);
    
    //unloading fonts
    FontManager::unloadFont(TEST_FONT1_LOCATION, 50);

    //unloading textures
    TextureManager::unloadTexture(TEST_TEXTURE2_LOCATION);
    TextureManager::unloadTexture(TEST_TEXTURE3_LOCATION);
    TextureManager::unloadTexture(TEST_TEXTURE4_LOCATION);

    //terminating managers
    SoundManager::terminate();//because the sources are in the stack and persist until the return, this will cause errors. It will not happen in a real situation.
    FontManager::terminate();
    GraphicManager::terminate();
    TextureManager::terminate();

    return 0;
}

