#include "game/gameStates/playState.h"

PlayState::PlayState(StateStack* gameStateStack):StateStack::State(gameStateStack){

    FontManager::loadFont(TEST_FONT1_LOCATION, 50);

    //creating a text with the loaded font and setting its properties
    
    testText.setFont(FontManager::getFont(TEST_FONT1_LOCATION, 50));
    testText.setLineSpacing(50);
    testText.setText("DroleDrile");
    testText.appendText("\nDrule");
    testText.setPosition({10.0f, 50.0f});
    testText.setColor({1.0f, 0.1f, 0.1f, 1.0f});
    testText.setLayer(8);

    //setting a view to the whole screen
    testView = View({0.0f, 0.0f}, {SCR_WIDTH, SCR_HEIGHT}, {-1.0f, 1.0f}, {2.0f, 2.0f});
    GraphicManager::setView(testView);

    TextureManager::loadTexture(TEST_TEXTURE2_LOCATION);
    TextureManager::loadTexture(TEST_TEXTURE3_LOCATION);
    TextureManager::loadTexture(TEST_TEXTURE4_LOCATION);
    TextureManager::loadTexture(TEST_TEXTURE5_LOCATION);

    //making an animated sprite from a loaded texture
    testSprite.setTexture(TEST_TEXTURE2_LOCATION);
    testSprite.setPosition({100.0f, 100.0f});
    testSprite.setSize({67.0f, 62.0f});
    testSprite.setColor({1.0f, 1.0f, 1.0f, 1.0f});
    testSprite.generateFrames({0.0f, 0.0f}, {201.0f, 251.0f}, 4, 3);
    testSprite.setLayer(5);

    //making a still image from a loaded texture
    testImage.setTexture(TEST_TEXTURE3_LOCATION);
    testImage.setTexturePosition({80.0f, 80.0f});
    testImage.setTextureSize({180.0f, 220.0f});
    testImagePos = vec2f(300.0f, 300.0f);
    testImage.setPosition({300.0f, 300.0f});
    testImage.setSize({100.0f, 100.0f});
    testImage.setColor({0.0f, 1.0f, 1.0f, 1.0f});
    testImage.setLayer(30);

    //making an image that will follow the cursor
    testPointerImage.setTexture(TEST_TEXTURE5_LOCATION);
    testPointerImage.setTexturePosition({0.0f, 0.0f});
    testPointerImage.setTextureSize({443.0f, 312.0f});
    pointerDelta = vec2f(-100.0f, 0.0f);
    testPointerImage.setPosition({300.0f, 300.0f});
    testPointerImage.setSize({100.0f, 100.0f});
    testPointerImage.setColor({1.0f, 1.0f, 1.0f, 1.0f});
    testPointerImage.setLayer(50);

    
    testParticleSystem.setTexture(TEST_TEXTURE4_LOCATION);
    testParticleSystem.setTexturePosition({0.0f, 0.0f});
    testParticleSystem.setTextureSize({801.0f, 598.0f});
    testParticleSystem.setPosition({300.0f, 300.0f});
    testParticleSystem.setPositionRange({0.0f, 0.0f}, {0.0f, 0.0f});
    testParticleSystem.setVelocityRange({-100.0f, -100.0f}, {100.0f, 100.0f});
    testParticleSystem.setLifetimeRange(3, 4);
    testParticleSystem.setSizeRange({100.0f, 100.0f,}, {200.0f, 200.0f}, true);
    testParticleSystem.setScalingFactor(0.998f);
    testParticleSystem.setLayer(10);

    
    SoundManager::loadSound(TEST_SOUND1_LOCATION);
    SoundManager::loadSound(TEST_SOUND2_LOCATION);
    

    //all MONO sounds will be played as heard from a listener in the center of the 2D screen and 1 screen width away from it.
    //the idea is to simulate your head's position in the scene
    SoundManager::setListenerPosition({SCR_WIDTH/2.0f, SCR_HEIGHT/2.0f}, SCR_WIDTH);

    //creating a streaming audio source
    testSoundSource1.queueSound(TEST_SOUND1_LOCATION);
    testSoundSource1.play();

    //attaching a sound to an audio source
    testSoundSource2.attachSound(TEST_SOUND2_LOCATION);
    testSoundSource2.setReferenceDistance(SCR_WIDTH/2.0f);

    i = 0;

}

PlayState::~PlayState(){
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
    TextureManager::unloadTexture(TEST_TEXTURE5_LOCATION);
}

void PlayState::update(){

    i++;
        if(i > 60){
            i = 0;
            testSprite.nextFrame();
            testParticleSystem.emit();
        }
        imageVel = {0.0f, 0.0f};
        testParticleSystem.update(0.01);
        //WASD will update the position of the test image
        if(InputManager::isKeyPressed(Keys::D)){
            imageVel += {2.0f, 0.0f};
        }
        if(InputManager::isKeyPressed(Keys::W)){
            imageVel += {0.0f, -4.0f};
        }
        if(InputManager::isKeyPressed(Keys::A)){
            imageVel += {-2.0f, 0.0f};
        }
        if(InputManager::isKeyPressed(Keys::S)){
            imageVel += {0.0f, 4.0f};
        }
        testImagePos += imageVel;

        mouse = InputManager::getMousePosWorld(testView);
        //'G' key will play a sound roughly where the test image is
        if(InputManager::wasKeyPressed(Keys::G)){           
            testSoundSource2.play();
        }

        testImage.setPosition(testImagePos);
        testPointerImage.setPosition(mouse + pointerDelta);
        testSoundSource2.setPosition(testImagePos);

}