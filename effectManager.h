#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "global_includes.h"


class effectTemplate {
    bool skip; // whether the result of this one should be skipped
    vector<int> applyEffect(vector<int> original, vector<int>);
};


class effectManager {
    std::vector<effectTemplate*> allFx; // pointers to all effects available
    std::deque<effectTemplate*> activeFx; // stores pointers to all active effects
    
    
public:
    void addEffect(effectTemplate* effect); // adds new effect to master list
    int numActiveFx();

    void pushBackActive(effectTemplate* effect); // adds effect to end of list
    void pushFrontActive(effectTemplate* effect); // adds effect to start of list
    void insertActive(effectTemplate* effect,int pos);    //adds effect at a particular point (the end if invalid index given)
};

effectManager Effects



#endif