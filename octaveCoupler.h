#ifndef OCTAVE_COUPLER_H
#define OCTAVE_COUPLER_H

#include "modules.h"

class octave_coupler {
public:
	octave_coupler();
	bool active;
	int number, dir, min, max, delay, pitch;
	void run(int keyNumber, int state);
};


extern octave_coupler octaveCoupler;

#endif

