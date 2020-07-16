#ifndef CONTROLS_H
#define CONTROLS_H
#include "global_includes.h"
#include "stateManager.h"
#include "utility.h"
#include "multiplexer.h"
#include "pluginManager.h"

class controls {

    int noOfReedSwitches = 1;
    int reedSwitchFirstPin = 3;
    vector<vector<int>> reedSwitches;
    int reedSwitch;

public:

    controls();

    void checkPins();


};


extern controls Controls;
#endif