#include "pluginManager.h"




void keypressHandler(int keyNumber, int state) { // use this to set key states as it checks which plugins are available and runs them 
	Keys.setSensorState(keyNumber, state);

	// compiler checks to see what plugins are available, then runs all that are
#ifdef OCTAVE_COUPLER_H 
	octaveCoupler.run(keyNumber, state); 
#endif


		
	
		

	
}