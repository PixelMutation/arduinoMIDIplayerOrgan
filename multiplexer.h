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
class Multiplexer {
    std::vector<int> selectPins = MUX_SELECT_PINS;
    std::vector<int> enablePins = MUX_ENABLE_PINS;
    int numOfMux; 
    int IOpin;

    bool input;
    bool pullup;
    bool continuous;
    void writeBinary(std::vector<int>& pins, int value);
    void setEnablePins(int mux);

public:
    Multiplexer(bool _input, bool _continuous, int number, int _IOpin);

    int muxRead(int index, bool analog, bool pullup, int microsecondDelay);

};


//extern Multiplexer testMux;

#endif
