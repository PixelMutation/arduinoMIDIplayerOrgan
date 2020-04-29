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
        if (reedSwitch == LOW) {
            keypressHandler(50,1);
            cout << "\nreed switch activated";
            //cout << "\n                        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 ";
            cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);
        } else {
            keypressHandler(50,0);
            //cout << "\n                        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 ";
            cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);
        }
   }
   
}

// create instance
controls Controls;





