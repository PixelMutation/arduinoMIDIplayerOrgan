#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "global_includes.h"
#include <ADC.h>


class analogManager {
    public:
    const ADC *adc = new ADC();
    analogManager();
};
extern analogManager * analog_manager;

// Instantiated for each chain of multiplexers connected to the control board. Can be used as input or output (though should use I2C port expanders for digital input or output)
class Multiplexer {

    
    int selectPins[4] = MUX_SELECT_PINS;
    int enablePins[4] = MUX_ENABLE_PINS;
    
    int numOfMux; 
    int IOpin;

    bool input;
    //bool pullup;
    bool continuous;
    
    std::vector<bool> pullups;
    
    void writeBinary(int pins[4], int value);
    void prepare(int pin);

public:
    Multiplexer(bool _input, bool _continuous, int number, int _IOpin);
    
    void selectMuxAndPin(int index);
    void setPullup(int pin, bool pullup);
    int AnalogReadSingle(int pin);
    int DigitalRead(int pin);
};


//extern Multiplexer testMux;

#endif
