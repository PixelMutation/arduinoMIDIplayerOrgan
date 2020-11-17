#ifndef SENSORS_H
#define SENSORS_H

#include "global_includes.h"
#include "EEPROM_manager.h"
#include "I2Cactuators.h"
#include "multiplexer.h"

// all sensors inherit from this
class sensorsTemplate {
public:
    int pin;
    int numMux;
    Multiplexer* mux;
    void scan();
};

// contains the various sensor objects
class Sensors : public moduleTemplate{
public:
    
    
    class Manuals : public sensorsTemplate {
        int muxPerManual; // the number of multiplexers per manual
        std::vector<std::array<int,2>> multiplexers; // the first and last multiplexer of each manual
        int uncertainty; // read values are compared to stored value +- this 
        int calibrationDelay = 500; // delay after keypress before measurement taken (ms)
    public:
        
        EEPROM_manager::block3d& calibratedPositions = eepromManager.newBlock(NUM_MANUALS,3,KEYS_PER_MANUAL);
        byte oldPositions[NUM_MANUALS][KEYS_PER_MANUAL]; // the position of each key at the last measurement, indexed as [manual][key]. used to compare to see if the key has moved
        byte topPositions[NUM_MANUALS][KEYS_PER_MANUAL]; // the position when key is at the top, measued upon system start
        byte defaultPositions[3] = {
            220, // pos when sound produced
            200, // pos when held by system
            170  // pos at bottom
        };
        Manuals();
        int read(int manual, int key);
        void calibrate(std::string mode);
    };

    class Stops : public sensorsTemplate{

        int onPosition;
        bool analog;
    public:
        Stops();
        int read(int division, int stop);
    };

    class BassPedals : public sensorsTemplate{

        bool analog;
        int onPosition;
        
    public:
        BassPedals();
        int read(int pedal);
    };

    class ControlPanels : public sensorsTemplate{
        vector<int> inputMode; // which sensors are pullups
    public:
        ControlPanels();
        int readAnalog(int sensor);
        int readDigital(int sensor);
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
