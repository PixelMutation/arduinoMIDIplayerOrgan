#ifndef CONTROLS_H
#define CONTROLS_H
#include "global_includes.h"
#include "stateManager.h"
#include "utility.h"
#include "multiplexer.h"


class controls : public moduleTemplate {

    int noOfReedSwitches = 1;
    int reedSwitchFirstPin = 3;
    std::vector<std::vector<int>> reedSwitches;
    int reedSwitch;

public:

    controls();
    void onLoop();

    void checkPins();


};


extern controls Controls;
#endif