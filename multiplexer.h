#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "global_includes.h"
#include <ADC.h>

class analogManager {
    public:
    ADC *adc = new ADC();
    analogManager();
};
extern analogManager analog_manager;

// Takes the I/O number and configures the mux to switch to the correct pin, then reads / outputs to it. constructor:(if an input mux,  no. of muxes used in this I/O array, mux select pins (vector, ordered, 4 items), I/O pin for each mux (vector, ordered) )
class Multiplexer : public moduleTemplate {
    

    int numberOfMultiplexers;
    vector<int> selectPins;
    vector<int> IOpins;
    bool input;
    bool pullup;
    
public:
    Multiplexer(bool input, int number, vector<int> _selectInputPins, vector<int> _IOpins);
    
    void muxActive(bool active);
    bool muxActive();
    int muxRead(int number, bool analog, bool pullup, int microsecondDelay=0);

};


extern Multiplexer testMux;

#endif
