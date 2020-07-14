#ifndef SENSORS_H
#define SENSORS_H

#include "modules.h"


class sensors {
    const int noOfManuals = 1; // supports up to 4 manuals (though I'm sure you can do more if you are insane enough)
    const int keysPerManual = 61; // normally 61, especially when there are multiple manuals
    const int noOfBassPedals = 0; // I have none sadly.
    const int noOfStops = 11; 
    const int controlPanels = 1; // typically each control panel will have up to 16 controls (one mux), though it can be more. Each control panel has pins starting from 0.
    const int controlPanelPins;

public:
    void sensors();

    class manuals {
        int noOfPins;
        int multiplexers; // the number of multiplexers required
    public:
        int defaultPositions[4] = {
            220, // pos when sound produced
            200, // pos when held by system
            170  // pos at bottom
        }
        eeprom.block calibratedPositions;
        //int calibratedPositions[][][4]; // positions (0-255) for each key (top, pos. when sound produced, pos. where held by actuators, bottom) at which certain actions are taken, indexed as [manual][key][position]
        int oldPositions[][]; // the position of each key at the last measurement, indexed as [manual][key]. used to compare to see if the key has moved.
    
        manuals();
        int fetchCalibratedPosition(int key, int manual, int posType);

    }

    class stops {


        int multiplexers; // the number of multiplexers required
        int onPosition;
        bool analog;
    public:
        stops();
    }

    class bassPedals {


        int multiplexers; // the number of multiplexers required
        bool analog;
        int onPosition;
    public:
        bassPedals();
    }

    class controlPanels {


        int multiplexers; // the number of multiplexers required

    public:
        controlPanels();
    }


}




#endif