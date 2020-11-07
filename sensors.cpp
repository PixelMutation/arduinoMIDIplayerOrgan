#include "sensors.h"

// CONSTRUCTORS
sensors::sensors() {
    hook.OnLoop.push_back(this);
}
sensors::manuals::manuals() {
    pin = KEY_SIG;
    muxPerManual = (KEYS_PER_MANUAL+15)/ 16;

    mux = new Multiplexer(true,true,muxPerManual*NUM_MANUALS,KEY_SIG); // creates mux for the manual sensors
 
    if (calibratedPositions.data[0][1][0] == 0) { // If keys not calibrated, apply defaults: If it is 0, it likely hasn't been calibrated yet.
        for (int x = 0; x < NUM_MANUALS; x++) { // for each manual
            for (int y = 0; y < 3; y++) { // for each type of position
                for (int z = 0; z < KEYS_PER_MANUAL; z++) { // for each key
                    calibratedPositions.data[x][y][z] = defaultPositions[y]; //set position to position type default
                }
            }
        }
    }

    for (int x = 0; x < NUM_MANUALS; x++) {
        for (int y = 0; y < KEYS_PER_MANUAL; y++) {
            topPositions[x][y] = read(x,y);
        }
        multiplexers.push_back({muxPerManual*x,muxPerManual*(x+1)-1}); // adds the first and last mux in the manual to a list
    }

}

sensors::stops::stops() {
    pin = STOP_SIG;
    numMux = (NUM_STOPS + 15) / 16;
    mux = new Multiplexer(true,false,numMux,STOP_SIG); // creates mux for the manual sensors
}
sensors::bassPedals::bassPedals() {
    pin = PED_SIG;
    numMux = (NUM_BASS_PEDALS +15)/16;
    mux = new Multiplexer(true,false,numMux,PED_SIG); // creates mux for the manual sensors

}
sensors::controlPanels::controlPanels() {
    pin = CTRL_SIG;
    numMux = (NUM_BASS_PEDALS +15)/16;
    mux = new Multiplexer(true,false,numMux,CTRL_SIG); // creates mux for the manual sensors
}



// MAIN FUNCTIONS

//READ VALUES

// reads the raw value from a key
int sensors::manuals::read(int manual, int key) {
    return mux->muxRead(manual*key+key,true,KEY_PULLUP,MICROSECOND_DELAY);
}
// reads the raw value from a stop
int sensors::stops::read(int division, int stop) {
    return mux->muxRead(division*stop + stop,analog,STOP_PULLUP,MICROSECOND_DELAY);
}
// reads the raw value from a bass pedal
int sensors::bassPedals::read(int pedal) {
    return mux->muxRead(pedal,analog,PED_PULLUP,MICROSECOND_DELAY);
}
// reads the analog state of a control panel pin
int sensors::controlPanels::readAnalog(int pin) {
    return mux->muxRead(pin,true,inputMode[pin],MICROSECOND_DELAY);
}
// reads the digital state of a control panel pin
int sensors::controlPanels::readDigital(int pin) {
    return mux->muxRead(pin,false,inputMode[pin],MICROSECOND_DELAY);
}

// SCAN SENSORS



// runs through key calibration
void sensors::manuals::calibrate(std::string mode = "all") {
    for (int x = 0; x < NUM_MANUALS; x++) {
        for (int y = 0; y < KEYS_PER_MANUAL; y++) {
            if (mode == "top" or mode == "all") {
                topPositions[x][y] = read(x,y); // calibrates top position from key current pos
                delay(50);
            }
            if (mode == "system" or mode == "all") {
                KeyActuators.setState(x,y,1);   // presses the key then measures the position
                delay(calibrationDelay);        // waits for sig stabilisation
                calibratedPositions.data[x][y][1] = read(x,y); // reads position when system presses key
                KeyActuators.setState(x,y,0);   // releases key
            } 
            if (mode == "sound" or mode =="all") {
                awaitConfirmation();
                calibratedPositions.data[x][y][0] = read(x,y); // reads pos when key held to point sound is made by user
            } 
            if (mode == "bottom" or mode =="all") {
            
                awaitConfirmation();
                calibratedPositions.data[x][y][2] = read(x,y);  // reads pos when key held down fully by user
            }
        } 
    }
}

// runs all the scan operations each time the whole program loops
void sensors::onLoop() {
    Manuals.scan();
    Stops.scan();
    BassPedals.scan();
    ControlPanels.scan();
}


sensors Sensors;
