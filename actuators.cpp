#include "actuators.h"


keyActuators::keyActuators() {
    int expandersPerManual = (keysPerManual + 15)/16; // divides and rounds up to find the number of expanders required per manual
    if (expandersPerManual <= 8) {
        ports.push_back(new portExpander(0,expandersPerManual));// activates first port
        if (manuals * keysPerManual > 128) { // each port supports up to 128 keys
            ports.push_back(new portExpander(2,expandersPerManual)); // use second port as well
        }   
    } else {
        ports.push_back(new portExpander(0,8)); // uses all of port one
        ports.push_back(new portExpander(2,(expandersPerManual*manuals)-8)); //oveflows into second port
    }
    for (int i=0; i < manuals; i++) { // for every manual
        expanders.push_back({expandersPerManual*i,expandersPerManual*(i+1)-1}); // add the first and last expander for this manual
    }
}
// sets the state of the actuator for the given manual and key
void keyActuators::setState(int manual, int key, int state) {
    int manualExpander = key/16; // find the expander number within the manual
    int expander = expanders[manual][0] + manualExpander; // finds the overall expander number
    if (expander < 8) { // only 8 expanders per port, so selects the correct port
        ports[0]->writeToPin(key-expander*16,state,expander);
    } else {
        ports[1]->writeToPin(key-(expander-8)*16,state,expander-8);
    }
}

void keyActuators::test(string mode="legato") {
    // staccato test
    if (mode == "staccato" or mode == "all") {
        for (int i=0; i < manuals; i++) {
            for (int j=0; j < keysPerManual; j++) {
                for (int k=0; k < staccatoRepetitions; k++) {
                    setState(i,j,1);
                    delay(staccatoDuration);
                    setState(i,j,0);
                    delay(delayDuration);
                }
            }
        }
    }
    // legato test
    if (mode == "legato" or mode == "all") {
        for (int i=0; i < manuals; i++) {
            setState(i,0,1); // turns first key on
            for (int j=1; j < keysPerManual; j++) {
                setState(i,j-1,0); // turns previous key off
                setState(i,j,1);    // turns next key on
                delay(legatoDuration)
            }
            setState(i,keysPerManual-1,0); // turns the last key off
        }
    }
    // chord test
    if (mode == "arpeggio" or mode == "all" ) {
        for (int i=0; i < manuals; i++) {
            for (int j=0; j < keysPerManual; j++) {
                
            }
        }
    }
}