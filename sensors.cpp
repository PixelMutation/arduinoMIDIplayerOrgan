#include "sensors.h"

// CONSTRUCTORS
sensors::sensors() {

}

sensors::manuals::manuals() {
    multiplexers = KEYS_PER_MANUAL / 16;
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
            //topPositions[x][y] = readval(x,y);
        }
    }

    


}


sensors::stops::stops() {
    
}
sensors::bassPedals::bassPedals() {
    
}
sensors::controlPanels::controlPanels() {
    
}

// MAIN FUNCTIONS


int sensors::manuals::readval(int manual, int key) {
    return 0; // PLACEHOLDER!!
}

int sensors::OnLoop() {
    
}


sensors Sensors;
