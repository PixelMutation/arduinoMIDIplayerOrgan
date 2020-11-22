#include "midiManager.h"

//TODO make this code handle the different stop divisions
// constructor (int middleCpos, std::vector<int> channels_) 
midiManager::midiManager() {
	console.section("midiManager",CORE_PREFIX);
	midi_to_key_offset = MIDImiddleCpos - keysMiddleCpos; //this offset is used when converting between MIDI key numbers and real key numbers

	hooks.OnLoop.add(this);
	console.sectionEnd("midiManager initialised",CORE_PREFIX);
}

// runs each loop
void midiManager::onLoop(){
	if (Serial1.available() > 2) {  // https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/
		MIDIreceive(Serial1.read(), Serial1.read(),Serial1.read());
	}
	if (Serial2.available() > 2) {
		MIDIreceive(Serial2.read(), Serial2.read(),Serial2.read());
	}
}

// checks for and handles incoming MIDI messages (use parameters ONLY for SIMULATING midi, otherwise ignores real midi input)
void midiManager::MIDIreceive(int status, int data1, int data2) { // parameters only for simulation purposes

	// the Status byte is split into 2 nibbles: the command type and the channel number
	int type = status / 16; // divides the status message by 16 to find the type of command, discarding the channel number
	int channel = status % 16; // finds the channel number
	bool found = false;
	for (auto i : channels) {
		if (i == channel) {
			found = true;
			break;
		}
	}
	if (found) {
		cout << "\nchannel " << channel << " active";
		cout << "\ntype " << type << " data1 " << data1 << " data2 " << data2 << "\n";
		int midiNumber, velocity, keyNumber;

		switch (type) { // using table of HEX midi commands at https://www.songstuff.com/recording/article/midi_message_format/
		case 0x9: // if it is a key on command
			
			midiNumber = data1;
			velocity = data2;
			keyNumber = midiNumber - midi_to_key_offset; //applies midi to real key offset
			if (velocity!=0) { // sometimes note off is sent as on with velocity 0
				stateManager.keys.requestActuatorState(0,keyNumber, 1); //toggles the key on
			} else {
				stateManager.keys.requestActuatorState(0,keyNumber, 0); //toggles the key off
			}
			//printKeyStates("header");
			//printKeyStates("full");

			// Calls all module functions for midi key on
			hooks.OnMidiKey.call(0,data1,data2);
			break;
		case 0x8: // if it is a key off command
			
			midiNumber = data1;	
			keyNumber = midiNumber - midi_to_key_offset; //applies midi to real key offset
			stateManager.keys.requestActuatorState(0,keyNumber, 0); //toggles the key off
			//printKeyStates("header");
			//printKeyStates("full");

			// Calls all module functions for midi key off
			hooks.OnMidiKey.call(0,data1,0);
			break;
		case 0xC: // if it is a program change (instrument change) command
			MIDI_to_stop(data1);

			// Calls all module functions for when a midi instrument change is requested
			hooks.OnMidiInstrument.call(data1);

			break;
		case 0xB: // if it is a control change
			// Calls all module functions for when there is a general CC message
			
			switch (data1) {

			case 1: // modulation wheel (vibrato)
				if (voxHumanaPos != -1) {
					if (data2 >= minModulationLevel) {
						stateManager.stops.requestActuatorState(0,voxHumanaPos, 1);
					}
					else {
						stateManager.stops.requestActuatorState(0,voxHumanaPos, 0);
					}
				}
				// Calls all module functions for midi mod messages
				hooks.OnMidiCCmod.call(data2);


				break;
			case 64: // sustain pedal
				if (data2 >= 64) {
					//sustain.active = true;
				}
				else {
					//sustain.active = false;
				}
				// Calls all module functions for midi sustain messages
				hooks.OnMidiCCsustain.call(data2);

				break;
			case 93: // chorus level (if high enough, pulls out all the stops and activates coupler)
				if (data2 >= minChorusLevel) {
					for (int i = 0; i < NUM_STOPS; i++) {
						stateManager.stops.requestActuatorState(0, i, 1);
					}
					//octaveCoupler.active = true;
				}

				// Calls all module functions for midi chorus messages
				hooks.OnMidiCCchorus.call(data2);

				break;
			case 68: // legato pedal (when pedal active, hold each note until the next is pressed)
				// Calls all module functions for midi chorus messages
				hooks.OnMidiCClegato.call(data2);


				break;
			case 7: // volume (whether to activate forte stops)
				if (! fortePos.empty()) {
					int state;
					if (data2 >= minForteLevel) {
						state = 1;
					}
					else {
						state = 0;
					}
					for (auto element : fortePos) {
						stateManager.stops.requestActuatorState(0, element, state);
					}
				}
				// Calls all module functions for midi volume messages
				hooks.OnMidiCCvolume.call(data2);


				break;
			default:
				break;
			}
		default:
			break;
		
		}


	}


}

// sends the required key state over MIDI (velocity and channel parameters are OPTIONAL)
void midiManager::MIDIsendKey(int keyNumber, int state, int velocity, int channel) {
	int midiNumber = keyNumber + midi_to_key_offset;
	int type;
	if (state == 1) {
		type = 0x9; // Note on status type
	}
	else {
		type = 0x8; // Note off status type
	}
	if (channel == -1) {
		channel = outputChannel; // if channel unspecified, use default
	}
	int status = type * 16 + channel;
	int data1 = keyNumber;
	int data2 = velocity;
	/*
	code to send midi here
	*/
}

// converts current stop positions to a MIDI instrument and sends a MIDI program change message with this
void midiManager::stops_to_MIDI() { //TODO reconnect this part to get the states vector
	std::vector<int> currentStops;// = Stops.getStatesVector("all"); // gets current stop positions
	// linear search through presets to find the preset matching current stop config
	for (int i = 0; i < 127; i++) { 
		bool foundPreset = true;			// defaults to true
		if (stopPresets.empty()) {	// check preset isn't empty
			for (int j = 0; j < (int)stopPresets[i].size(); j++) { // iterate through preset
				if (stopPresets[i][j] != -1 && stopPresets[i][j] != currentStops[j-1]) { // if preset stop pos doesn't match real stop pos
					bool foundPreset = false; 
					break; // break loop to try next preset
				}
			}
		}
		if (foundPreset) {
			int status = 0xC; // program change status
			int data1  = i  ;
			int data2  = 0  ;
			//cout << "\nsending preset: ";
			//printVector(stopPresets[i]);
			//cout << " as instrument " << i << "\n";
			/*
			code to send instrument (program) change signal via MIDI


			*/
			break;
		}
	}


}

// converts MIDI instrument program change messages to stop positions and moves the stops to those positions
void midiManager::MIDI_to_stop(int instrumentNumber) {
  bool found = false;
  for (int i = 0; i < (int)stopPresetsTable.size(); i++) {
  	if (stopPresetsTable[i][0] == instrumentNumber) {							// checks if that preset is available (has anything in it)
      found = true;
  		for (int i = 1; i < (int)stopPresetsTable[instrumentNumber].size(); i++) {	// for each item in the preset (excluding first item)
  			if (stopPresetsTable[instrumentNumber][i] != -1) {						// if it isn't -1 (ie. ignore it) then set each stop state to the preset value
  				stateManager.stops.requestActuatorState(0, i , stopPresetsTable[instrumentNumber][i]);
  			}
  				
  		}
		//printStopStates("overall");
      	break;
  	
  	}
  } 
	if (! found) { // if not found as one of the presets, set stops to default instrument preset 
		int defaultInstrument = 0; 
		for (int i = 1; i < (int)stopPresetsTable[defaultInstrument].size(); i++) {
			if (stopPresetsTable[defaultInstrument][i] != -1) {
				stateManager.stops.requestActuatorState(0, i, stopPresetsTable[defaultInstrument][i]);
			}

		}
		//printStopStates("overall");
	}
  
}


// create instance of MIDI class
midiManager MIDI;
