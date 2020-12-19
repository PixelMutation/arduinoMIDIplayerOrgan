#include "multiplexer.h"

#include "console.h"

analogManager::analogManager() {
    console->section("analogManager",CORE_PREFIX);
    //pinMode(KEY_SIG, INPUT); 
    
    adc->adc0->setResolution      (ADC_RESOLUTION);
    adc->adc0->setAveraging       (ADC_AVERAGING);
    adc->adc0->setConversionSpeed (ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
    adc->adc0->setSamplingSpeed   (ADC_SAMPLING_SPEED  ::HIGH_VERY_HIGH_SPEED);

    //adc->adc0->startContinuous(KEY_SIG);

    adc->adc1->setResolution      (ADC_RESOLUTION);
    adc->adc1->setAveraging       (ADC_AVERAGING);
    adc->adc1->setConversionSpeed (ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
    adc->adc1->setSamplingSpeed   (ADC_SAMPLING_SPEED  ::HIGH_VERY_HIGH_SPEED);
    //Serial.print("val "); Serial.println(adc->adc0->analogReadContinuous());
    console->sectionEnd("analogManager initialised",CORE_PREFIX);

}

analogManager * analog_manager = nullptr;


// constructor: (if an input mux,no. of muxes used in this I/O array, mux select pins (vector, ordered, 4 items), I/O pin for each mux (vector, ordered) )
Multiplexer::Multiplexer(bool _input, bool _continuous, int _numOfMux, int _IOpin) {
    console->section("multiplexer",CORE_PREFIX);
    //analogReadResolution(8); // the lower the resolution the faster
    //analogReadAveraging(8); // the higher the number of measurements, the more consistent the signal but the slower it is
    continuous = _continuous;
    numOfMux   = _numOfMux  ;
    IOpin      = _IOpin     ;
    input      = _input     ;
    
    for (int i = 0; i < 4; i++) {
        pinMode(selectPins[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(enablePins[i], OUTPUT);
    }
    if (input) {
        pinMode(IOpin, INPUT);
    }
    pullups.resize(numOfMux*16,false);
    
    
    console->sectionEnd("multiplexer initialised",CORE_PREFIX);

}
// sets 4 pins to represent a 4 bit binary value
inline void Multiplexer::writeBinary(int pins[4], int value) {
   // console->println("start binary write");
    
    for (int i = 0; i < 4; i++) { // for each pin, set the binary state to select the mux output https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide/all

        if (value & (1<<i)) {

            digitalWriteFast(pins[i], HIGH);

        } else {

            digitalWriteFast(pins[i], LOW);
            
        }
    }
}
// uses demux to select mux and selects mux pin given index out of all muxes
inline void Multiplexer::selectMuxAndPin(int index) {
    int mux = index/16; // each has 16 outputs so this finds which multiplexer is needed
    writeBinary(enablePins,mux);
    int selectNumber = index - 16 * mux; // the number (0-15) of the output on the corresponding multiplexer
    writeBinary(selectPins,selectNumber);
}
//called to change whether a pin is pullup or not, default is non pullup (meaning pulldown)
void Multiplexer::setPullup(int pin, bool pullup) {
    pullups[pin] = pullup;
}
// sets up multiplexer and IO pin for read
void Multiplexer::prepare(int pin) {
    selectMuxAndPin(pin);
    if (pullups[pin]) {
        pinMode(IOpin, INPUT_PULLUP);
    } else {
        pinMode(IOpin, INPUT);
    }
}
// does a quick single analog measurement
int Multiplexer::AnalogReadSingle(int pin) {
    prepare(pin);
    return analogRead(IOpin);
}
// returns the binary pin state
int Multiplexer::DigitalRead(int pin) {
    prepare(pin);
    return digitalRead(IOpin);
}

//Multiplexer testMux(true,true,1,{A8});
