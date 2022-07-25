#include "engine/stateMachine/stateStack.h"

#include "math/vec2f.h"
#include "input/inputManager.h"
#include "sound/soundManager.h"
#include "graphics/graphicManager.h"
#include "engine/graphics/text/fontManager.h"
#include "physics/collisionManager.h"

class PlayState: public StateStack::State{

    private:
        View testView;

        Text testText;

        Sprite testSprite;

        Image testImage;
        Image testPointerImage;

        ParticleSystem testParticleSystem;

        SoundSource testSoundSource1;
        SoundSource testSoundSource2;

        short i;

        vec2f mouse;
        vec2f imageVel;
        vec2f testImagePos;
        vec2f pointerDelta;

    public:
        PlayState(StateStack* gameStateStack = nullptr);
        ~PlayState();

        void update();

};