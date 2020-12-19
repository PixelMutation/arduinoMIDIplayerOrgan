#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include "global_includes.h"

#include "moduleManager.h"

//#include "octaveCoupler.h"

class MidiManager : public moduleTemplate { // handles MIDI I/O
  int MIDImiddleCpos     = 48;	// leave this alone
	
  bool sendSystemKeypress = false;
  int outputChannel      = 0;	  // channel on which notes are sent

  int minForteLevel      = 64;	// volume level (0-127) at which forte stops activated
  int minChorusLevel     = 64;	// chorus level at which all stops activated
  int minModulationLevel = 64;	// level at which vox humana activated
  bool midiStates[KEYS_PER_MANUAL];

  std::vector<std::array<int8_t,NUM_STOPS+1>> stopPresetsTable { // This is just some preset stop positions assigned to MIDI instruments, change these to some presets for your own instrument. Use -1 to indicate that that stop should be ignored (e.g. if it can't be moved, or won't affect anything.)
    //No.  |            Stops state          |      General MIDI instrument   
    // all off                          SFX
    {127,  0, 0, 0,  -1,-1,-1,-1,-1,  0, 0, 0},   //      Gunshot 
    // bass only                        Bass
    {32,  0, 0, 1,  -1,-1,-1,-1,-1,  0, 0, 0},    //    Accoustic Bass
    {33,  0, 1, 0,  -1,-1,-1,-1,-1,  0, 0, 0},    //    Electric Bass (finger)
    {34,  1,-1, 0,  -1,-1,-1,-1,-1,  0, 0, 0},    //    Electric Bass (pick)
    {35,  0, 1, 1,  -1,-1,-1,-1,-1,  0, 0, 0},    //    Fretless Bass
    {36,  1,-1, 1,  -1,-1,-1,-1,-1,  0, 0, 0},      //    Slap Bass 1
    // treble only                        Ensemble 
    {48,  0, 0, 0,  -1,-1,-1,-1,-1,  0, 1, 0},    //    String Ensemble 1   
    {49,  0, 0, 0,  -1,-1,-1,-1,-1,  0,-1, 1},    //    String Ensemble 2
    {50,  0, 0, 0,  -1,-1,-1,-1,-1,  1, 0, 0},    //    Synth Strings 1
    {51,  0, 0, 0,  -1,-1,-1,-1,-1,  1, 1, 0},    //    Synth Strings 2
    {52,  0, 0, 0,  -1,-1,-1,-1,-1,  1,-1, 1},    //    Choir Aahs
    // bass: sub bass only                    Brass
    {56,  0, 0, 1,  -1,-1,-1,-1,-1,  0, 1, 0},    //    Trumpet
    {57,  0, 0, 1,  -1,-1,-1,-1,-1,  0,-1, 1},    //    Trombone
    {58,  0, 0, 1,  -1,-1,-1,-1,-1,  1,-1, 1},    //    Tuba
    {59,  0, 0, 1,  -1,-1,-1,-1,-1,  1, 1, 0},    //    Muted Trumpet
    {60,  0, 0, 1,  -1,-1,-1,-1,-1,  1, 0, 0},    //    French Horn
    // bass: bassoon/diapason only                Reed
    {64,  0, 1, 0,  -1,-1,-1,-1,-1,  1, 1, 0},    //    Soprano Sax
    {65,  1,-1, 0,  -1,-1,-1,-1,-1,  1, 1, 0},    //    Alto Sax
    {66,  0, 1, 0,  -1,-1,-1,-1,-1,  1,-1, 1},    //    Tenor Sax
    {67,  1,-1, 0,  -1,-1,-1,-1,-1,  1,-1, 1},    //    Baritone Sax
    // treble: vox angelica only                Piano
    {0,   1,-1, 1,  -1,-1,-1,-1,-1,  1, 0, 0},      //    Accoustic Grand
    {1,   0, 1, 0,  -1,-1,-1,-1,-1,  1, 0, 0},    //    Bright Accoustic Grand
    {2,   1,-1, 0,  -1,-1,-1,-1,-1,  1, 0, 0},    //    Electric Grand
    {3,   0, 1, 1,  -1,-1,-1,-1,-1,  1, 0, 0},    //    Honky Tonk
    // treble: echo/melodia only
    // bass:  bassoon/diapason only               Organ
    {17,  0, 1, 0,  -1,-1,-1,-1,-1,   0, 1, 0},   //    Percussive Organ
    {21,  1,-1, 0,  -1,-1,-1,-1,-1,   0, 1, 0},   //    Accordion
    {22,  0, 1, 0,  -1,-1,-1,-1,-1,   0,-1, 1},   //    Harmonica
    {23,  1,-1, 0,  -1,-1,-1,-1,-1,   0,-1, 1},   //    Tango Accordion
    // treble: echo/melodia only                Strings
    {40,  0, 1, 1,  -1,-1,-1,-1,-1,   0, 1, 0},   //    Violin
    {41,  1,-1, 1,  -1,-1,-1,-1,-1,   0, 1, 0},   //    Viola
    {42,  0, 1, 1,  -1,-1,-1,-1,-1,   0,-1, 1},   //    Cello
    {44,  1,-1, 1,  -1,-1,-1,-1,-1,   0,-1, 1},   //    Tremolo Strings
    // remaining combos                     Organ
    {16,  1,-1, 1,  -1,-1,-1,-1,-1,   1, 1, 0},   //    Drawbar Organ
    {18,  0, 1, 1,  -1,-1,-1,-1,-1,   1, 1, 0},   //    Rock Organ
    {20,  0, 1, 1,  -1,-1,-1,-1,-1,   1,-1, 1},   //    Reed Organ
    // all on                         
    {19,  1,-1, 1,  -1,-1,-1,-1,-1,   1,-1, 1}    //    Church Organ
  };
	
	
	std::array<std::array<int8_t,NUM_STOPS>,128> stopPresets;// a 2D std::vector table containing all the possible reed stop configurations indexed by their MIDI instrument assignment
public:
	std::vector<byte> channels { 0,1,2,3,4 }; // the MIDI channels the system responds to
  int midi_to_key_offset;			             // offset between MIDI key number and real key number
	int keysMiddleCpos = 32;		             // the key number (index starting at 0) of middle C on your organ

	// Special stops positions
	int voxHumanaPos = 5;			// stop number of the vox humana (-1 if not present)
	std::vector<int> fortePos = { 4,6 }; // stop number(s) for forte stop(s) (empty if not present)
	
	// function declarations
	MidiManager(); // constructor

  void onLoop            (PARAM_onLoop            ) override; // this part is called each time the program loops
  void onUserKeyToggle   (PARAM_onUserKeyToggle   ) override;
  void onSystemKeyToggle (PARAM_onSystemKeyToggle ) override;

  
	void receive(int status , int data1 , int data2 );	// checks for and handles MIDI input
	void sendKey(int keyNumber, int state, int velocity = 63, int channel = -1);				// sends the required key state over MIDI
	void stops_to_MIDI();						              // converts current stop positions to a MIDI instrument and sends a MIDI program change message with this
	void MIDI_to_stop(int instrumentNumber);	    // converts MIDI instrument program change messages to stop positions and moves the stops to those positions
};

extern MidiManager * MIDI ;


#endif
