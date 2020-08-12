#include "moduleManager.h"

/*
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
*/

void moduleTemplate::onStart() {}
void moduleTemplate::onLoop() {}


void moduleTemplate::onKeyMove(int key, int newPos, int oldPos) {}
void moduleTemplate::onUserKeyToggle(int manual, int key, int velocity, bool state, int pos) {}
void moduleTemplate::onSystemKeyToggle(int manual, int key, int velocity, bool state) {}

void moduleTemplate::onUserStopToggle(int stop, bool state) {}
void moduleTemplate::onSystemStopToggle(int stop, bool state) {}


void moduleTemplate::onPedalToggle(int pedal, bool state) {}


void moduleTemplate::onControlChange(int panel, int number, int state) {}


void moduleTemplate::onMidiKey(int manual, int key, bool state) {}
void moduleTemplate::onMidiCC(int data1, int data2) {}
void moduleTemplate::onMidiInstrument(int instrument) {}


void moduleTemplate::onSerialMessage(string module, string setting, int data) {}

ModuleCall moduleCall;


