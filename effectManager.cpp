#include "effectManager.h"

fxData effectTemplate::applyEffect(fxData previousResult){}



effectManager::effectManager() {
    console.section("effectManager",CORE_PREFIX);
    
    
    
    console.sectionEnd("effectManager initialised",CORE_PREFIX);
}

void effectManager::addEffect(effectTemplate* effect) {
    totalNumFx +=1;
    
    
}


void effectManager::runFx(int manual, int key, int state) {
    if (!activeFx.empty()){
        fxData result; // stores the result after each effect applied
        result.emplace_back(manual,key,state,0); // adds the first keypress to the list
        for (int i = 0; i < totalNumFx; i++) {
            result = allFx[i]->applyEffect(result);
        }
        for (auto & keypress : result) {        
            stateManager.keys.requestActuatorState(
                std::get<0>(keypress),
                std::get<1>(keypress),
                std::get<2>(keypress),
                std::get<3>(keypress)
            );
            
        }
    }
    
}

effectManager Fx;