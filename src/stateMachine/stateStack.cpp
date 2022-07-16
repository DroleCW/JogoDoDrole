#include "stateMachine/stateStack.h"
#include <stdio.h>


StateStack::StateStack(){

}

StateStack::~StateStack(){
    while(states.size())
        pop();
}

void StateStack::push(StateStack::State* state){
    state->enter();
    states.push(state);
}

void StateStack::pop(){
    states.top()->exit();
    delete states.top();
    states.pop();
}

void StateStack::update(){
    states.top()->update();
}