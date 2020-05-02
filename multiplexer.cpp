#include "multiplexer.h"



// constructor: (if an input mux,no. of muxes used in this I/O array, mux select pins (vector, ordered, 4 items), I/O pin for each mux (vector, ordered) )
Multiplexer::Multiplexer(bool _input, int _numberOfMultiplexers, vector<int> _selectPins, vector<int> _IOpins) {
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
    
        int multiplexer = inputNumber/16; // each has 16 outputs so this finds which multiplexer is needed
        byte selectNumber = inputNumber - 16 * multiplexer; // the number (0-15) of the output on the corresponding multiplexer
        int IOpin = IOpins[multiplexer]; // the pin of the multiplexer being used
        int firstReading; //used to bin first (usually dodgey) reading. Analog interference: https://forum.arduino.cc/index.php?topic=70013.0
        //printVector(IOpins, true);
        //cout << "\nmultiplexer " << multiplexer << " selectNumber " << selectNumber << " iopin " << IOpin << " ";
        if (multiplexer < numberOfMultiplexers) { // sanity check!
            //char binarySelect[] = "0000";
            for (int i = 0; i < 4; i++) { // for each select pin, set the binary state to select the mux output https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide/all
                if (selectNumber & (1<<i)) {
                    digitalWrite(selectPins[i], HIGH);
                } else {
                    digitalWrite(selectPins[i], LOW);
                }
                /*
                binarySelect[i] = bitRead(selectNumber,3- i)  + 48;
                digitalWrite(selectPins[i], bitRead(selectNumber, i)); // write the bit value to select the right output
                */
            }
            //cout << "\nbinary output: " << binarySelect << "\n";
            if (pullup) { // if it is a pullup sensor
                pinMode(IOpin, INPUT_PULLUP);
            } else {
                pinMode(IOpin, INPUT);
            }
            if (analog) { // whether an analog response is wanted
                delayMicroseconds(10);
                firstReading = analogRead(IOpin); // first reading is typically bad
                delayMicroseconds(microsecondDelay); // delay so analog has time to stabilise
                return (analogRead(IOpin) + firstReading)/2; 
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

Multiplexer testMux(true,1,{50,51,52,53},{A0});