#include "stateMachine/stateStack.h"
#include <stdio.h>


StateStack::StateStack(){

}

StateStack::~StateStack(){
    while(states.size())
        pop();
}

void StateStack::push(StateStack::State* state){
    if(states.size())
        states.top()->onInactive();
    state->onActive();
    states.push(state);
}

void StateStack::pop(){
    states.top()->onInactive();
    delete states.top();
    
    states.pop();
    if(states.size())
        states.top()->onActive();
}

void StateStack::update(){
    states.top()->update();
}