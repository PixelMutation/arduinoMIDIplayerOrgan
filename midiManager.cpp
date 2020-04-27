#include "midiManager.h"

// constructor (int middleCpos, vector<int> channels_) 
midiManager::midiManager() {
	midi_to_key_offset = MIDImiddleCpos - keysMiddleCpos; //this offset is used when converting between MIDI key numbers and real key numbers
	// initializes the stops presets, taking the user friendly table and converting it to be read quickly by putting the row at the correct position.



	//stopPresets.assign(128,{}); // fills with empty vectors
  /*
	stopPresets = vector<vector<int> >(128, vector<int>(Stops.size()));
  int noOfPresets = (int)stopPresetsTable.size();
	for (int i = 0; i < noOfPresets; i++) { // for each row of the presets table
		int instrumentNumber = stopPresetsTable[i][0];
		for (int j = 1; j <= Stops.size(); j++) { // for each item in the row (except the first)
      Serial.println(i);

			stopPresets[instrumentNumber].push_back(stopPresetsTable[i][j]); // add it to the row ( which is at the index of the first item in the old row) in the new vector
		}
	}
  */
 
 


}

// checks for and handles incoming MIDI messages (use parameters ONLY for SIMULATING midi, otherwise ignores real midi input)
void midiManager::MIDIrecieve(int status, int data1, int data2) { // parameters only for simulation purposes
	//int status, data1, data2; // midi messages comprise a status byte and 2 data bytes https://www.songstuff.com/recording/article/midi_message_format/
	bool recieved = false;
	if (status == -1 && data1 == -1 && data2 == -1) { // if being called with no parameters (ie. to recieve actual MIDI)
		cout << "checking serial\n";
		
		do {
			if (Serial3.available() > 2) { // https://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/
				status = Serial3.read();
				data1 = Serial3.read();
				data2 = Serial3.read();
				cout << "recieved\n";
				recieved = true;
				digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  				delay(100);                       // wait for a second
  				digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW

			}
		} while (! Serial3.available() > 2);
		
	} else { recieved = true;}

	if (recieved) {
		// the Status byte is split into 2 nibbles: the command type and the channel number
		int type = status / 16; // divides the status message by 16 to find the type of command, discarding the channel number
		//cout << type << " " << status << "\n";
		int channel = status % 16; // finds the channel number
		if (find(channels.begin(), channels.end(), channel) != channels.end()) {// checks if the channel is active using vector search method at https://www.techiedelight.com/check-vector-contains-given-element-cpp/
			//cout << "channel active\n";
			int midiNumber, velocity, keyNumber;

			switch (type) { // using table of HEX midi commands at https://www.songstuff.com/recording/article/midi_message_format/
			case 0x8: // if it is a key on command

				midiNumber = data1;
				velocity = data2;
				keyNumber = midiNumber - midi_to_key_offset; //applies midi to real key offset
				Keys.requestSystemState(keyNumber, 1); //toggles the key on

				break;
			case 0x9: // if it is a key off command

				midiNumber = data1;
				keyNumber = midiNumber - midi_to_key_offset; //applies midi to real key offset
				Keys.requestSystemState(keyNumber, 0); //toggles the key off

				break;
			case 0xC: // if it is a program change (instrument change) command
				MIDI_to_stop(data1);

				break;
			case 0xB: // if it is a control change
				switch (data1) {

				case 1: // modulation wheel (vibrato)
					if (voxHumanaPos != -1) {
						if (data2 >= minModulationLevel) {
							Stops.requestSystemState(voxHumanaPos, 1);
						}
						else {
							Stops.requestSystemState(voxHumanaPos, 0);
						}
					}
					break;
				case 64: // sustain pedal
					if (data2 >= 64) {
						//sustain.active = true;
					}
					else {
						//sustain.active = false;
					}
					break;
				case 93: // chorus level (if high enough, pulls out all the stops and activates coupler)
					if (data2 >= minChorusLevel) {
						for (int i = 0; i < (int)Stops.size(); i++) {
							Stops.requestSystemState(i, 1);
						}
						octaveCoupler.active = true;
					}
					else {
						octaveCoupler.active = false;
					}
					break;
				case 68: // legato pedal (when pedal active, hold each note until the next is pressed)
					if (data2 >= 64) {
						//legato.active = true;
					}
					else {
						//legato.active = false;
					}

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
							Stops.requestSystemState(element, state);
						}
					}
					break;
				}
			
			}


		}
  cout << "\nkey requests  buffer  : ";    Keys.getStatesVector("buffer", true, false);
  cout << "\nkeys pressed by system: ";    Keys.getStatesVector("system", true, false);
  cout << "\nkeys pressed by user  : ";    Keys.getStatesVector("user", true, false);
  cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);
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
void midiManager::stops_to_MIDI() {
	vector<int> currentStops = Stops.getStatesVector("all"); // gets current stop positions
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
			int data1 = i;
			int data2 = 0;
			//cout << "\nsending preset: ";
			printVector(stopPresets[i]);
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
  				Stops.requestSystemState(i , stopPresetsTable[instrumentNumber][i]);
  			}
  				
  		}
      break;
  	
  	}
  } 
	if (! found) { // if not found as one of the presets, set stops to default instrument preset 
		int defaultInstrument = 0; 
		for (int i = 1; i < (int)stopPresetsTable[defaultInstrument].size(); i++) {
			if (stopPresetsTable[defaultInstrument][i] != -1) {
				Stops.requestSystemState(i, stopPresetsTable[defaultInstrument][i]);
			}

		}
	}
  
}


// create instance of MIDI class
midiManager MIDI;
