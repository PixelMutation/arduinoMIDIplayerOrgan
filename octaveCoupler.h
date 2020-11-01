#ifndef OCTAVE_COUPLER_H
#define OCTAVE_COUPLER_H

#include "global_includes.h"
#include "stateManager.h"

class octave_coupler : public moduleTemplate {
public:
	octave_coupler();
	int number = 3;
	int dir = 1;
	int min = 1;
	int max = 61;
	int delay = 10;
	int pitch = 12;
	bool active = false;
	void run(int keyNumber, int state);

	void onUserKeyToggle(int manual, int key, int velocity, bool state, int pos);
};


extern octave_coupler octaveCoupler;

#endif

