#include "modules.h"


void instantiateModules() {
    for (int i=0; i < NUM_MANUALS; i++) {
        manuals.push_back(new stateManager("keys", KEYS_PER_MANUAL, POLYPHONY, i));
    }
    stateManager Stops("stops", NUM_STOPS, NUM_STOPS);

}