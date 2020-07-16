#include "multiplexer.h"


analogManager::analogManager() {
    pinMode(A8, INPUT); 

  
    adc->adc0->setAveraging(16);
    adc->adc0->setResolution(16);
    adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
    adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

    adc->adc0->startContinuous(A8);

    adc->adc1->setAveraging(16);
    adc->adc1->setResolution(16);
    adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
    adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

}

analogManager analog_manager;

// constructor: (if an input mux,no. of muxes used in this I/O array, mux select pins (vector, ordered, 4 items), I/O pin for each mux (vector, ordered) )
Multiplexer::Multiplexer(bool _input, int _numberOfMultiplexers, vector<int> _selectPins, vector<int> _IOpins) {

    
    //analogReadResolution(8); // the lower the resolution the faster
    //analogReadAveraging(8); // the higher the number of measurements, the more consistent the signal but the slower it is
    
    

    numberOfMultiplexers = _numberOfMultiplexers;
    selectPins = _selectPins;
    IOpins = _IOpins;
    input = _input;


    for (int i = 0; i < (int)selectPins.size(); i++) {
        pinMode(selectPins[i], OUTPUT);
    }


    for (int i = 0; i < (int)IOpins.size(); i++) {      
        pinMode(IOpins[i], INPUT);
    }


}

// returns the value of the input (input number, if you want analog result, if a pullup sensor)
int Multiplexer::muxRead(int inputNumber, bool analog, bool pullup, int microsecondDelay) {
    if (input) { // sanity check: output mux cannot act as input
        //Serial.println("a");
        int multiplexer = inputNumber/16; // each has 16 outputs so this finds which multiplexer is needed
        byte selectNumber = inputNumber - 16 * multiplexer; // the number (0-15) of the output on the corresponding multiplexer
        int IOpin = IOpins[multiplexer]; // the pin of the multiplexer being used
        //int reading1, reading2, reading3, reading4; //used to bin first (usually dodgey) reading. Analog interference: https://forum.arduino.cc/index.php?topic=70013.0
        //printVector(IOpins, true);
        //cout << "\nmultiplexer " << multiplexer << " selectNumber " << selectNumber << " iopin " << IOpin << " ";
        if (multiplexer < numberOfMultiplexers) { // sanity check!
            int binarySelect[4] = {0,0,0,0};
            //Serial.println("b");
            for (int i = 0; i < 4; i++) { // for each select pin, set the binary state to select the mux output https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide/all
                //Serial.println("c");
                if (selectNumber & (1<<i)) {
                    digitalWrite(selectPins[i], HIGH);
                    binarySelect[i] = 1;
                } else {
                    digitalWrite(selectPins[i], LOW);
                    binarySelect[i] = 0;
                }
                
                //binarySelect[i] = bitRead(selectNumber,3- i)  + 48;
                //digitalWrite(selectPins[i], bitRead(selectNumber, i)); // write the bit value to select the right output
                
            }
            /*
            Serial.println("binary output ");
            for (auto i: binarySelect) {
              Serial.println(i);
            }
            Serial.println("\n");
            */
            if (pullup) { // if it is a pullup sensor
                pinMode(IOpin, INPUT_PULLUP);
            } else {
                pinMode(IOpin, INPUT);
            }
            if (analog) { // whether an analog response is wanted
                //Serial.println("d");
                //delayMicroseconds(10);
                delayMicroseconds(microsecondDelay); // delay so analog has time to stabilise
                //return (analogRead(IOpin)); 
                return(analog_manager.adc->adc0->analogReadContinuous());
            } else {
                return digitalRead(IOpin);
            }
        } else {
            
            return 0;
        }
    } else {
        return 0;
    }
    //delay(10);
}

void Multiplexer::muxActive(bool active) {
    //if (active)

}
bool Multiplexer::muxActive() {
    return true; // TEMP
}


Multiplexer testMux(true,1,{2,3,4,5},{A8});
