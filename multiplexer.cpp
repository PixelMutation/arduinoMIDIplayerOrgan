#include "multiplexer.h"


analogManager::analogManager() {
    console.section("analogManager",CORE_PREFIX);
    pinMode(KEY_SIG, INPUT); 

    adc->adc0->setResolution      (ADC_RESOLUTION);
    adc->adc0->setAveraging       (ADC_AVERAGING);
    adc->adc0->setConversionSpeed (ADC_CONVERSION_SPEED::MED_SPEED);
    adc->adc0->setSamplingSpeed   (ADC_SAMPLING_SPEED  ::MED_SPEED);

    adc->adc0->startContinuous(KEY_SIG);

    adc->adc1->setResolution      (ADC_RESOLUTION);
    adc->adc1->setAveraging       (ADC_AVERAGING);
    adc->adc1->setConversionSpeed (ADC_CONVERSION_SPEED::MED_SPEED);
    adc->adc1->setSamplingSpeed   (ADC_SAMPLING_SPEED  ::MED_SPEED);
    //Serial.print("val "); Serial.println(adc->adc0->analogReadContinuous());
    console.sectionEnd("analogManager initialised",CORE_PREFIX);

}

analogManager analog_manager;

// constructor: (if an input mux,no. of muxes used in this I/O array, mux select pins (vector, ordered, 4 items), I/O pin for each mux (vector, ordered) )
Multiplexer::Multiplexer(bool _input, bool _continuous, int _numOfMux, int _IOpin) {
    console.section("multiplexer",CORE_PREFIX);
    //analogReadResolution(8); // the lower the resolution the faster
    //analogReadAveraging(8); // the higher the number of measurements, the more consistent the signal but the slower it is
    continuous = _continuous;
    numOfMux   = _numOfMux  ;
    IOpin      = _IOpin     ;
    input      = _input     ;
    
    for (int i = 0; i < (int)selectPins.size(); i++) {
        pinMode(selectPins[i], OUTPUT);
    }
    for (int i = 0; i < (int)enablePins.size(); i++) {
        pinMode(enablePins[i], OUTPUT);
    }
    if (input) {
        pinMode(IOpin, INPUT);
    }
    
    console.sectionEnd("multiplexer initialised",CORE_PREFIX);

}
// sets 4 pins to represent a 4 bit binary value
void Multiplexer::writeBinary(vector<int>& pins, int value) {
   // console.println("start binary write");

    for (int i = 0; i < (int)pins.size(); i++) { // for each pin, set the binary state to select the mux output https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide/all

        if (value & (1<<i)) {

            digitalWrite(pins[i], HIGH);

        } else {

            digitalWrite(pins[i], LOW);

        }
    }
}
// uses the demux to set all but the selected mux to be disabled
void Multiplexer::setEnablePins(int mux) {
    writeBinary(enablePins,mux);
}


// returns the value of the input (input number, if you want analog result, if a pullup sensor)
int Multiplexer::muxRead(int index, bool analog, bool pullup, int microsecondDelay) {
    console.println("startRead");
    int multiplexer = index/16; // each has 16 outputs so this finds which multiplexer is needed
    setEnablePins(multiplexer); // enables the chosen multiplexer
    int selectNumber = index - 16 * multiplexer; // the number (0-15) of the output on the corresponding multiplexer
    writeBinary(selectPins,selectNumber);   // sets mux to point to selectNumber
    if (input) {                      // sanity check: output mux cannot act as input
        if (multiplexer < numOfMux) { // sanity check!
            if (pullup) {             // if it is a pullup sensor
                pinMode(IOpin, INPUT_PULLUP);
            } else {
                pinMode(IOpin, INPUT);
            }
            if (analog) { // whether an analog response is wanted
                delayMicroseconds(microsecondDelay); // delay so analog has time to stabilise
                if (continuous) {
                    console.println("reach cont");
                    return(/*analog_manager.adc->adc0->analogReadContinuous()*/analogRead(23)); //TODO make continous reads work again
                } else {
                    return /*analog_manager.adc->adc1->analogRead(IOpin)*/ analogRead(23);
                }

            } else {
                return digitalRead(IOpin);
            }
        } else {
            
            return 0;
        }
    } else {
        return 0;
    }
}


//Multiplexer testMux(true,true,1,{A8});
