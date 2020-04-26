#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include "../modules.h"

class midiManager { // handles MIDI I/O
	int MIDImiddleCpos = 48;		// leave this alone
	int midi_to_key_offset;			// offset between MIDI key number and real key number

	int outputChannel = 0;	// channel on which notes are sent

	int minForteLevel = 64;			// volume level (0-127) at which forte stops activated
	int minChorusLevel = 64;		// chorus level at which all stops activated
	int minModulationLevel = 64;	// level at which vox humana activated

	

	vector<vector<int>> stopPresets;// a 2D vector table containing all the possible reed stop configurations indexed by their MIDI instrument assignment
public:
	vector<int> channels{ 0,1,2,3,4 };// the MIDI channels the system responds to
	int keysMiddleCpos = 32;		// the key number (index starting at 0) of middle C on your organ

	// Special stops positions
	int voxHumanaPos = 5;			// stop number of the vox humana (-1 if not present)
	vector<int> fortePos = { 4,6 }; // stop number(s) for forte stop(s) (empty if not present)
	
	// function declarations
	midiManager(); // constructor

	void MIDIrecieve(int status = -1, int data1 = -1, int data2 = -1);	// checks for and handles MIDI input

	void MIDIsendKey(int keyNumber, int state, int velocity = 63, int channel = -1);				// sends the required key state over MIDI

	void stops_to_MIDI();						// converts current stop positions to a MIDI instrument and sends a MIDI program change message with this

	void MIDI_to_stop(int instrumentNumber);	// converts MIDI instrument program change messages to stop positions and moves the stops to those positions
};

extern midiManager MIDI;


#endif

