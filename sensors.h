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
class sensors : public moduleTemplate{
public:
    sensors();
    void onLoop();
    class manuals : public sensorsTemplate {
        int muxPerManual; // the number of multiplexers per manual
        vector<int[2]> multiplexers; // the first and last multiplexer of each manual
        int uncertainty; // read values are compared to stored value +- this 
        int calibrationDelay = 500; // delay after keypress before measurement taken (ms)
    public:
        
        EEPROM_manager::block3d& calibratedPositions = eepromManager.newBlock(NUM_MANUALS,3,KEYS_PER_MANUAL);
        int oldPositions[NUM_MANUALS][KEYS_PER_MANUAL]; // the position of each key at the last measurement, indexed as [manual][key]. used to compare to see if the key has moved
        int topPositions[NUM_MANUALS][KEYS_PER_MANUAL]; // the position when key is at the top, measued upon system start
        int defaultPositions[3] = {
            220, // pos when sound produced
            200, // pos when held by system
            170  // pos at bottom
        };
        manuals();
        int read(int manual, int key);
        void calibrate(std::string mode);
    };

    class stops : public sensorsTemplate{

        int onPosition;
        bool analog;
    public:
        stops();
        int read(int division, int stop);
    };

    class bassPedals : public sensorsTemplate{

        bool analog;
        int onPosition;
        
    public:
        bassPedals();
        int read(int pedal);
    };

    class controlPanels : public sensorsTemplate{
        vector<int> inputMode; // which sensors are pullups
    public:
        controlPanels();
        int readAnalog(int sensor);
        int readDigital(int sensor);
    };

    sensors::manuals       Manuals      ;
    sensors::stops         Stops        ;
    sensors::bassPedals    BassPedals   ;
    sensors::controlPanels ControlPanels;

};


extern sensors Sensors;



#endif
