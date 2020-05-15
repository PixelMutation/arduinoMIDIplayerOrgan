#ifndef OCTAVE_COUPLER_H
#define OCTAVE_COUPLER_H

#include "modules.h"

class octave_coupler {
public:
	int number = 3;
	int dir = 1;
	int min = 1;
	int max = 61;
	int delay = 10;
	int pitch = 12;
	bool active = false;
	void run(int keyNumber, int state);
};


extern octave_coupler octaveCoupler;

#endif

