#pragma once

#include <vector>

class StateMachine{

public: 
    class State{

        protected:
            StateMachine* stateMachine;

        public:
            State(StateMachine* stateMachine = nullptr){
                setStateMachine(stateMachine);
            }
            virtual ~State(){
                
            }

            virtual void enter(int from){}
            virtual void exit(int to){}

            virtual void update() = 0;

            inline void setStateMachine(StateMachine* stateMachine){
                this->stateMachine = stateMachine;
            }

    };

protected:
    std::vector<State*> states;
    int currentStateID;

public:
    StateMachine();
    virtual ~StateMachine();

    void addState(State* state);
    void changeState(int nextStateID);

    void update();

    int getCurrentState() const;

};
