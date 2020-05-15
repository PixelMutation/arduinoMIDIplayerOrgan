#include "pluginManager.h"




void keypressHandler(int keyNumber, int state) { // use this to set key states as it checks which plugins are available and runs them 
	Keys.setSensorState(keyNumber, state);
	if (state == 1) {
        Serial1.write(0x90);
    } else {
        Serial1.write(0x80);
    }
    Serial1.write(keyNumber + 16);
    Serial1.write(100);
	// compiler checks to see what plugins are available, then runs all that are
#ifdef OCTAVE_COUPLER_H 
	octaveCoupler.run(keyNumber, state); 
#endif
#ifdef SCALES_H
	scaleManager.autoChord(keyNumber, state);
#endif

		
	
		

	
}