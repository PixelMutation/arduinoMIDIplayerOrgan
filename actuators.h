#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "global_includes.h"
#include "I2Cmanager.h"

class keyActuators {
    int keysPerManual = KEYS_PER_MANUAL;
    int manuals = NUM_MANUALS;
    vector<portExpander*> ports;    // stores expander objects (up to 2)
    vector<int[2]> expanders; // stores the first and last expander for each manual

    
public:
    // test settings
    int staccatoRepetitions = 2;
    int staccatoDuration = 10; // ms
    int delayDuration = 10; // ms
    int legatoDuration = 20;

    keyActuators();
    void setState(int manual, int key, int state);
    void test(string mode);
};

class stopActuators {
    int numActuators = NUM_STOPS;
    vector<int> divisions = DIVISIONS;
public:
    stopActuators();
    void setState(int manual, int key, int state);
    void test();
};


extern keyActuators KeyActuators;

#endif