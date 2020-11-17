#include "octaveCoupler.h"

//UImoduleSettings octaveCouplerSettings([insert number of settings]);
//octaveCouplerSettings.addToggleSetting([args])

/*
toggles the next note up/down (direction "dir") by an octave for "number" octaves,
each time with a "delay" within the given range of notes ("min" and "max")
*/

octave_coupler::octave_coupler() {
	console.section("plugin octaveCoupler");
	hook.OnUserKeyToggle.push_back(this);
	
	
	console.sectionEnd("plugin octaveCoupler initialised");
}


void octave_coupler::run(int keyNumber, int state) { // main function which runs the coupler
	
	if (active) {
		//cout << "\noctaveCouplerActive";
		for (int i = 1; i <= number; i++) {						// repeats for the number of times specified
			int newKeyNumber = keyNumber + (i * dir * pitch);	// new key to be toggled  is one octave (12 semitones) above or below
			
			if (newKeyNumber <= max and newKeyNumber >= min) {	// check it is within the range where the coupler is active
				
				if (delay > 0) { // if a delay is wanted between each note
					stateManager.keys.scheduleActuatorState(0,newKeyNumber, state, delay * i);
				}
				else {
					stateManager.keys.requestActuatorState(0,newKeyNumber, state);
					//cout << "octave coupled\n";
				}

			}
		}
	}
	
}

void octave_coupler::onUserKeyToggle(int manual, int key, int velocity, bool state, int pos) {
	run(key, state);
}

octave_coupler octaveCoupler;
