#include "engine/stateMachine/stateStack.h"
#include "engine/graphics/text/fontManager.h"
#include "engine/graphics/graphicManager.h"

class MainMenuState: public StateStack::State{

    private:
        View testView;
        Text initText;


    public:
        MainMenuState(StateStack* gameStateStack = nullptr);
        ~MainMenuState();

        virtual void onActive() override;
        virtual void onInactive() override;

        void update();

};