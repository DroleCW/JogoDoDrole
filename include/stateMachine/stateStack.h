#pragma once

#include <stack>

class StateStack{

public: class State{

            protected:
                StateStack* stateStack;

            public:
                State(StateStack* stateStack = nullptr){
                    setStateStack(stateStack);
                }
                virtual ~State(){

                }

                virtual void enter(){}
                virtual void exit(){}

                virtual void update() = 0;

                inline void setStateStack(StateStack* stateStack){
                    this->stateStack = stateStack;
                }

            };

protected:
    std::stack<StateStack::State*> states;

public:
    StateStack();
    virtual ~StateStack();

    void push(StateStack::State* state);
    void pop();

    void update();


};
