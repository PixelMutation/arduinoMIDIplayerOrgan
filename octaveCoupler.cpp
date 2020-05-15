#include "octaveCoupler.h"

//UImoduleSettings octaveCouplerSettings([insert number of settings]);
//octaveCouplerSettings.addToggleSetting([args])

/*
toggles the next note up/down (direction "dir") by an octave for "number" octaves,
each time with a "delay" within the given range of notes ("min" and "max")
*/




void octave_coupler::run(int keyNumber, int state) { // main function which runs the coupler
	
	if (active) {
		cout << "\noctaveCouplerActive";
		for (int i = 1; i <= number; i++) {						// repeats for the number of times specified
			int newKeyNumber = keyNumber + (i * dir * pitch);	// new key to be toggled  is one octave (12 semitones) above or below
			
			if (newKeyNumber <= max and newKeyNumber >= min) {	// check it is within the range where the coupler is active
				
				if (delay > 0) { // if a delay is wanted between each note
					Keys.requestDelayedSystemState(delay * i, newKeyNumber, state);
				}
				else {
					Keys.requestSystemState(newKeyNumber, state);
					cout << "octave coupled\n";
				}

			}
		}
	}
	
}


octave_coupler octaveCoupler;
