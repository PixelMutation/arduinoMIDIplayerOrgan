#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "global_includes.h"



using fxData = std::vector<std::tuple<int,int,int,unsigned long>>;

class fxTemplate {
public:
    bool fxActive = false;
    virtual fxData applyEffect(fxData previousResult);

};
using fx = fxTemplate*;

class effectManager {
    
    std::deque<fx> activeFx; // stores pointers to all active effects
    std::deque<std::string> fxNames;
    int totalNumFx=0;
    
public:
    effectManager();


    void addEffect(fx effect, std::string name); // adds new effect to master list
    int numActiveFx();

    void moveBack(fx effect); // moves effect to end of list
    void moveBackwards(fx effect);
    void moveFront(fx effect); // moves effect to start of list
    void moveForwards(fx effect);
    void move(fx effect,int index);    //adds effect at a particular point (the end if invalid index given)
    
    std::string getName(fx effect);
    void printEffectOrder();
    
    void runFx(int manual, int key, int state);
};

extern effectManager * Fx;



#endif