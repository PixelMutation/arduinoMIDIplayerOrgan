#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "global_includes.h"
#include "stateManager.h"

typedef std::vector<std::tuple<int,int,int,unsigned long>> fxData;

class effectTemplate {
protected:
    int fxIndex;
    fxData output;
public:
    
    friend class effectManager; // the effectManager is a friend so can access the private variables
    bool skip; // whether the result of this one should be skipped
    virtual fxData applyEffect(fxData previousResult);

};


class effectManager {
    std::vector<effectTemplate*> allFx; // pointers to all effects available
    std::deque<int> activeFx; // stores pointers to all active effects
    int totalNumFx=0;
    
public:
    effectManager();


    void addEffect(effectTemplate* effect); // adds new effect to master list
    int numActiveFx();

    void pushBackActive(effectTemplate* effect); // adds effect to end of list
    void pushFrontActive(effectTemplate* effect); // adds effect to start of list
    void insertActive(effectTemplate* effect,int pos);    //adds effect at a particular point (the end if invalid index given)
    void removeActive(int index);
    void popBackActive();
    void popFrontActive();
    
    void runFx(int manual, int key, int state);
};

extern effectManager Fx;



#endif