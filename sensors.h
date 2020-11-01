#ifndef SENSORS_H
#define SENSORS_H

#include "global_includes.h"
#include "EEPROM_manager.h"

class sensors : public moduleTemplate{
    
    /*
    const int noOfManuals = NUM_MANUALS; // supports up to 4 manuals (though I'm sure you can do more if you are insane enough)
    const int keysPerManual = KEYS_PER_MANUAL; // normally 61, especially when there are multiple manuals
    const int noOfBassPedals = NUM_BASS_PEDALS; // I have none sadly.
    const int noOfStops = NUM_STOPS; 
    const int controlPanels = 1; // typically each control panel will have up to 16 controls (one mux), though it can be more. Each control panel has pins starting from 0.
    const int controlPanelPins;
    */
public:
    sensors();
    onLoop();

    class manuals {
        int noOfPins;
        int multiplexers; // the number of multiplexers required
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
        int readval(int manual, int key);

    };

    class stops {


        int multiplexers; // the number of multiplexers required
        int onPosition;
        bool analog;
    public:
        stops();
    };

    class bassPedals {


        int multiplexers; // the number of multiplexers required
        bool analog;
        int onPosition;
    public:
        bassPedals();
    };

    class controlPanels {


        int multiplexers; // the number of multiplexers required

    public:
        controlPanels();
    };


};


extern sensors Sensors;

#endif
