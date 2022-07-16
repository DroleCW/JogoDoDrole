#include "stateMachine/stateMachine.h"
#include <stdio.h>

StateMachine::StateMachine(){
    currentStateID = -1;
}

StateMachine::~StateMachine(){
    states[currentStateID]->exit(-1);
    for(auto i = 0; i<states.size(); i++)
        delete states[i];
}

void StateMachine::addState(State* state){
    states.push_back(state);
}

void StateMachine::changeState(int nextStateID){
    if(currentStateID != -1)//Se houver um estado atual
        states[currentStateID]->exit(nextStateID);
    
    states[nextStateID]->enter(currentStateID);

    currentStateID = nextStateID;
    

}

void StateMachine::update(){
    states[currentStateID]->update();
}



int StateMachine::getCurrentState() const{
    return currentStateID;
}
