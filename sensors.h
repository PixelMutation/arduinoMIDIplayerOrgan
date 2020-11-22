#ifndef SENSORS_H
#define SENSORS_H

#include "global_includes.h"
#include "EEPROM_manager.h"
#include "I2Cactuators.h"
#include "multiplexer.h"
#include <elapsedMillis.h>
#include "effectManager.h"

// all sensors inherit from this


// contains the various sensor objects
class Sensors : public moduleTemplate{
    class sensorsTemplate {
    public:
        int pin;
        int numMux;
        Multiplexer* mux;
        virtual void scan();
    };
public:
    class Manuals : public sensorsTemplate {
        int muxPerManual; // the number of multiplexers per manual
        std::vector<std::array<int,2>> multiplexers; // the first and last multiplexer of each manual
        int uncertainty; // read values are compared to stored value +- this 
        int calibrationDelay = 500; // delay after keypress before measurement taken (ms)
        double  findGradient      (int value, int manual, int key, double time);
        int     standardize       (int value, int manual, int key);
        int     standardizedRead  (int manual, int key);
        //double gradient;
        elapsedMillis measurementTime;
        int cycles;
        int x=-1;
        
        int     oldPositions[NUM_MANUALS][KEYS_PER_MANUAL] = {{}}; // the position of each key at the last measurement, indexed as [manual][key]. used to compare to see if the key has moved
        int     topPositions[NUM_MANUALS][KEYS_PER_MANUAL]       ; // the position when key is at the top, measued upon system start
        double  gradient    [NUM_MANUALS][KEYS_PER_MANUAL]       ;
        bool    forceOff    [NUM_MANUALS][KEYS_PER_MANUAL] = {{}};
    public:
        
        bool predictKeyRelease = true;
        
        eepromBlock3D calibratedPositions = eepromManager.newBlock(NUM_MANUALS,3,KEYS_PER_MANUAL);
        
        int defaultPositions[3] = {
            220, // pos when sound produced
            200, // pos when held by system
            170  // pos at bottom
        };
        Manuals();
        int read(int manual, int key);
        void calibrate(std::string mode);
        void scan();
    };

    class Stops : public sensorsTemplate{

        int onPosition;
        bool analog;
    public:
        Stops();
        int read(int division, int stop);
        void scan();
    };
 
    class BassPedals : public sensorsTemplate{

        bool analog;
        int onPosition;
        
    public:
        BassPedals();
        int read(int pedal);
        void scan();
    };

    class ControlPanels : public sensorsTemplate{
        std::vector<int> inputMode; // which sensors are pullups
    public:
        ControlPanels();
        int readAnalog(int sensor);
        int readDigital(int sensor);
        void scan();
    };

    Sensors::Manuals       manuals      ;
    Sensors::Stops         stops        ;
    Sensors::BassPedals    bassPedals   ;
    Sensors::ControlPanels controlPanels;
    
    
    
    void onLoop();
    
    Sensors();
};


extern Sensors sensors;


#endif
