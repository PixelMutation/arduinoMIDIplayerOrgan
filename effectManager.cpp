#include "effectManager.h"

#include "stateManager.h"
#include "console.h"
#include "moduleManager.h"


// applies an effect to the keypress and output of previous effects
fxData fxTemplate::applyEffect(fxData previousResult){
    return previousResult;
}



effectManager::effectManager() {
    console->section("effectManager",CORE_PREFIX);
    
    console->println((unsigned int)fxNames.size());
    
    console->sectionEnd("effectManager initialised",CORE_PREFIX);
}

void effectManager::addEffect(fx effect, std::string name) {
    if (listFind(effect,activeFx)==-1) {
        activeFx.push_back(effect);
        fxNames.push_back(name);
        console->println("addedEffect");
        console->println((unsigned int)activeFx.size());
        console->println((unsigned int)fxNames.size());
        totalNumFx+=1;
    }
}
void effectManager::moveBack(fx effect) {
    move(effect,totalNumFx-1);
}
void effectManager::moveBackwards(fx effect) {
    int index = listFind(effect,activeFx)-1;
    if (index>=0) {
        move(effect,index);
    }
    
}
void effectManager::moveFront(fx effect) {
    move(effect,0);
}
void effectManager::moveForwards(fx effect) {
    int index = listFind(effect,activeFx)+1;
    if (index<totalNumFx) {
        move(effect,index);
    }
    
}
inline void effectManager::move(fx effect, int index) {
    int oldIndex = listFind(effect,activeFx);
    if (oldIndex!=-1) {
        if (index < totalNumFx) {
            fx currentFx = activeFx[index]; // the effect already at that position
            std::string currentName = fxNames[index];
            fx newFx = activeFx[oldIndex]; // the effect already at that position
            std::string newName = fxNames[oldIndex];
            
            activeFx[index] = newFx;
            fxNames[index] = newName;
            
            activeFx[oldIndex] = currentFx;
            fxNames[oldIndex] = currentName;
        }

        
    } 
    
}
std::string effectManager::getName(fx effect) {
    int index = listFind(effect,activeFx)-1;
    if (index!=-1) {
        return fxNames[listFind(effect,activeFx)];
    }
    else {
        return "INVALID";
    }
}
 void effectManager::printEffectOrder() {
    console->printPrefix("FX  : ");
    for (auto name : fxNames) {
       console->print(name);
       console->print("");
    }
 }

// runs through all active effects (checks if fxActive==true)
void effectManager::runFx(int manual, int key, int state) {
    if (state == 0) {
        console->println("runFx 0");
    } else {
        console->println("runFx");
    }
    
    if (!activeFx.empty()){
        console->println("foundFx");
        fxData result; // stores the result after each effect applied
        result.emplace_back(manual,key,state,0); // adds the first keypress to the list
        for (int i = 0; i < totalNumFx; i++) {
            if (activeFx[i]->fxActive) { // only runs effect when active
                result = activeFx[i]->applyEffect(result); // runs each effect, feeding the next one the result of the previous
            }
        }
        for (int i = 1; i < (int)result.size(); i++) {  // requests actuation of all resulting keypresses except the first      
            stateManager->keys.requestActuatorState(
                std::get<0>(result[i]),
                std::get<1>(result[i]),
                std::get<2>(result[i]),
                std::get<3>(result[i])
            );
            hooks->callOnSystemKeyToggle(
                std::get<0>(result[i]),
                std::get<1>(result[i]),
                std::get<2>(result[i]),
                std::get<3>(result[i])
            );
            
        }
    }
    
}

effectManager * Fx = nullptr;