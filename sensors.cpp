#include "sensors.h"
#include <ADC.h>


// CONSTRUCTORS
Sensors::Sensors() : manuals(),stops(),bassPedals(),controlPanels() {
    console.section("Sensors",CORE_PREFIX);
    hooks.OnLoop.add(this);
      
    console.sectionEnd("Sensors initialised",CORE_PREFIX);
}
Sensors::Manuals::Manuals() {
    console.section("Sensors::Manuals",CORE_PREFIX);
    
    pin = KEY_SIG;
    muxPerManual = (KEYS_PER_MANUAL+15)/ 16;
    
    mux = new Multiplexer(true,true,muxPerManual*NUM_MANUALS,KEY_SIG); // creates mux for the manual Sensors
    /*
    if ((int)calibratedPositions.data[0][1][0] == 0) { // If keys not calibrated, apply defaults: If it is 0, it likely hasn't been calibrated yet.
        for (int x = 0; x < NUM_MANUALS; x++) { // for each manual
            for (int y = 0; y < 3; y++) { // for each type of position
                for (int z = 0; z < KEYS_PER_MANUAL; z++) { // for each key
                    calibratedPositions.data[x][y][z] = (byte)defaultPositions[y]; //set position to position type default
                }
            }
        }
    }
    */
    
    for (int x = 0; x < NUM_MANUALS; x++) {
        for (int y = 0; y < KEYS_PER_MANUAL; y++) {
            topPositions[x][y] = read(x,y);
        }
        multiplexers.push_back({muxPerManual*x,muxPerManual*(x+1)-1}); // adds the first and last mux in the manual to a list
    }
    
    
    console.sectionEnd("Sensors::Manuals initialised",CORE_PREFIX);
}

Sensors::Stops::Stops() {
    console.section("Sensors::Stops",CORE_PREFIX);
    pin = STOP_SIG;
    numMux = (NUM_STOPS + 15) / 16;
    mux = new Multiplexer(true,false,numMux,STOP_SIG); // creates mux for the manual Sensors
    
    
    console.sectionEnd("Sensors::Stops initialised",CORE_PREFIX);
}
Sensors::BassPedals::BassPedals() {
    console.section("Sensors::BassPedals",CORE_PREFIX);
    pin = PED_SIG;
    numMux = (NUM_BASS_PEDALS +15)/16;
    mux = new Multiplexer(true,false,numMux,PED_SIG); // creates mux for the manual Sensors


    console.sectionEnd("Sensors::BassPedals initialised",CORE_PREFIX);
}
Sensors::ControlPanels::ControlPanels() {
    console.section("Sensors::ControlPanels",CORE_PREFIX);
    pin = CTRL_SIG;
    numMux = (NUM_BASS_PEDALS +15)/16;
    mux = new Multiplexer(true,false,numMux,CTRL_SIG); // creates mux for the manual Sensors


    console.sectionEnd("Sensors::ControlPanels initialised",CORE_PREFIX);
}


void Sensors::sensorsTemplate::scan() {} // virtual
// MAIN FUNCTIONS

//READ VALUES

// reads the raw value from a key
int Sensors::Manuals::read(int manual, int key) {
    return mux->muxRead(manual*key+key,true,KEY_PULLUP,MICROSECOND_DELAY);
}
// reads the raw value from a stop
int Sensors::Stops::read(int division, int stop) {
    return mux->muxRead(division*stop + stop,analog,STOP_PULLUP,MICROSECOND_DELAY);
}
// reads the raw value from a bass pedal
int Sensors::BassPedals::read(int pedal) {
    return mux->muxRead(pedal,analog,PED_PULLUP,MICROSECOND_DELAY);
}
// reads the analog state of a control panel pin
int Sensors::ControlPanels::readAnalog(int pin) {
    return mux->muxRead(pin,true,inputMode[pin],MICROSECOND_DELAY);
}
// reads the digital state of a control panel pin
int Sensors::ControlPanels::readDigital(int pin) {
    return mux->muxRead(pin,false,inputMode[pin],MICROSECOND_DELAY);
}

// SCAN Sensors



// runs through key calibration
void Sensors::Manuals::calibrate(std::string mode = "all") {
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
double Sensors::Manuals::findGradient(int value, int manual, int key, double time) {
    if (value > TOP_THRESHOLD) {
        if (time > 0) {
            cycles=0;
            gradient[manual][key] = (double)(value-oldPositions[manual][key])/(time)*VELOCITY_MULTIPLIER;
            oldPositions[manual][key] = value;
            
        }
        
    } else {
        gradient[manual][key] = 0;
        oldPositions[manual][key] = 1;
    }
    return gradient[manual][key];
}

void Sensors::Manuals::scan() {
    cycles += 1;
    
    int val;
    //Serial.println(gradient[0][3]); 
    for (int manual = 0; manual < NUM_MANUALS; manual++) {
        for (int key = 0; key < KEYS_PER_MANUAL; key++) {
            val = standardizedRead(0,key);
            if (cycles >= VELOCITY_CYCLES) {
                findGradient(val,manual,key,measurementTime);
            }
            
            console.addPlotVar(val);
            console.addPlotVar(gradient[manual][key]);
            console.addPlotVar(oldPositions[manual][key]); 
            //console.addPlotVar(topPositions[manual][key]); 
            if (val > TOP_THRESHOLD) {
                if (predictKeyRelease) {
                    if (gradient[manual][key] < -VELOCITY_THRESHOLD && val < RELEASE_THRESHOLD) {
                        Fx.runFx(manual,key,0);
                        console.addPlotVar(0);
                        forceOff[manual][key]=true;
                    } else if (forceOff[manual][key] == 0){
                        Fx.runFx(manual,key,1);
                        console.addPlotVar(100);
                        if (gradient[manual][key] > 2) {
                            forceOff[manual][key]=false;
                        }
                    } else {
                        Fx.runFx(manual,key,0);
                        console.addPlotVar(0);
                    }
                } else {
                    Fx.runFx(manual,key,1);
                    console.addPlotVar(100);
                }
            } else {
                Fx.runFx(manual,key,0);
                console.addPlotVar(0);
                forceOff[manual][key]=false;
            }
        }
    }
    if (cycles >= VELOCITY_CYCLES) {
        measurementTime = 0;
    }
    //console.addPlotVar(gradient[0][3]);
    console.addPlotVar(0); 
    console.addPlotVar(0); 
    console.addPlotVar(110); 
    console.addPlotVar(-50); 


    measurementTime = 0;
}
int Sensors::Manuals::standardize(int value, int manual, int key) {
    
    int val = abs(value-topPositions[manual][key])-NOISE_LEVEL;
    if (val <0) {
        val = 0;
    }
    return ((int)(sqrt(SIGNAL_MULTIPLIER*val)))/SIGNAL_DIVIDER;
    
    //eturn abs(value-topPositions[manual][key]);
}
int Sensors::Manuals::standardizedRead(int manual, int key) {
    return standardize(read(manual,key),manual,key);
}
void Sensors::Stops::scan() {
    
}
void Sensors::BassPedals::scan() {

}
void Sensors::ControlPanels::scan() {

}
// runs all the scan operations each time the whole program loops
void Sensors::onLoop() {
    manuals.scan();
    stops.scan();
    bassPedals.scan();
    controlPanels.scan();
}


Sensors sensors;
