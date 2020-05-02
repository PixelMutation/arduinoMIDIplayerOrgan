#include "controls.h"


controls::controls() {
    /*
    for (int i = reedSwitchFirstPin; i < (reedSwitchFirstPin + noOfReedSwitches); i++) {
        pinMode(i, INPUT_PULLUP);
        reedSwitches.push_back({i,digitalRead(i)});
    }
    */


}

void controls::checkPins() { //  guide on detecting pin states https://www.arduino.cc/en/Tutorial/DigitalInputPullup
    /*
    for (int i = 0; i < noOfReedSwitches; i++) {
        if (reedSwitches[i][1] != digitalRead(reedSwitches[i][0])) {
            reedSwitches[i][1] = digitalRead(reedSwitches[i][0]);
            
            if (reedSwitches[i][1] == LOW) {
                Keys.setSensorState(50,1);
            } else {
                Keys.setSensorState(50,0);
            }
            
        }
        
    }
    */
   
   int newReedSwitchState = testMux.muxRead(9,false,false);
   if (reedSwitch != newReedSwitchState) {
        reedSwitch = newReedSwitchState;
        
        int note = testMux.muxRead(10,true,true) / 17; // pot gives values from 0-1023, integer division by 17 moves this within 1-60 //reading a potentionmeter https://www.arduino.cc/en/tutorial/potentiometer
        if (note > 0 && note < 62) {
            if (reedSwitch == LOW) {
                keypressHandler(note,1);
                cout << "\nreed switch activated";
                printKeyStates("overall");
                cout << "hall sensor: " << testMux.muxRead(8,true,true);
            } else {
                keypressHandler(note,0);
                printKeyStates("overall");
            }
        }
   }
   
}

// create instance
controls Controls;





