#ifndef I2C_ACTUATORS_H
#define I2C_ACTUATORS_H

#include "global_includes.h"
#include "I2Cmanager.h"

class keyActuators {
    int keysPerManual = KEYS_PER_MANUAL;
    int manuals       = NUM_MANUALS    ;
    std::vector<portExpander*  > ports    ; // stores expander objects (up to 2)
    std::vector<std::vector<int>> expanders; // stores the first and last expander for each manual

    
public:
    // test settings
    int staccatoRepetitions = 2 ;
    int staccatoDuration    = 10; // ms
    int delayDuration       = 10; // ms
    int legatoDuration      = 20;

    keyActuators();
    void setState(int manual, int key, int state);
    void test(std::string mode);
};

class stopActuators {
    int numActuators = NUM_STOPS;
    std::vector<int> divisions = DIVISIONS;
public:
    stopActuators();
    void setState(int division, int key, int state);
    void test();
};


extern keyActuators KeyActuators;
extern stopActuators StopActuators;

#endif