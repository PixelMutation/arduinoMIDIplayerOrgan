#include "controls.h"


controls::controls() {
    /*
    for (int i = reedSwitchFirstPin; i < (reedSwitchFirstPin + noOfReedSwitches); i++) {
        pinMode(i, INPUT_PULLUP);
        reedSwitches.push_back({i,digitalRead(i)});
    }
    */
   pinMode(3, INPUT_PULLUP);

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
   if (reedSwitch != digitalRead(3)) {
        reedSwitch = digitalRead(3);
        int note = analogRead(0) / 17; // pot gives values from 0-1023, integer division by 17 moves this within 1-60 //reading a potentionmeter https://www.arduino.cc/en/tutorial/potentiometer
        if (note > 0 && note < 62) {
            if (reedSwitch == LOW) {
                keypressHandler(note,1);
                cout << "\nreed switch activated";
                printKeyStates("overall");
                cout << "hall sensor: " << analogRead(1);
            } else {
                keypressHandler(note,0);
                printKeyStates("overall");
            }
        }
   }
   
}

// create instance
controls Controls;





