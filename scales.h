#ifndef SCALES_H
#define SCALES_H
#include "modules.h"

// stores the patterns used to construct scales, chords and arpeggios
class scale_manager {
	
	vector<vector<string>> chordPatterns { // stores the patterns (in terms of notes within a scale) of various supported scales
		{"triad","024"},
		{"seventh","0246"}
	};
	
	vector<vector<string>> scalePatterns { // stores the patterns of various supported scales (in terms of a list of half and whole steps) https://www.musictheory.net/lessons https://en.wikipedia.org/wiki/List_of_musical_scales_and_modes https://gumroad.com/l/tldrmusic
		//type						|half-steps|divisions|      Formula			   | Steps |	Semitones
		// 12 divsions
		//{"chromatic",				"11111111111","12"},//										all
		// 8 divisions
		//{"diminished",				"12121212", "8"},	// 1^2 3^4 5^6 7^8 1		hWhWhWhW	1-2 3-4 5-6 7-8 
		// 7 divisions
		{"major",					"2212221", "7"},	// 1 2 3^4 5 6 7^1			WWhWWWh		3-4 7-8
		{"harmonic minor",			"2122121", "7"},	// 1 2^b3 4 5^b6 7^1		WhWWhWh		2-3 5-6 7-8
		//{"melodic minor ascending", "2122221", "7"},	// 1 2^b3 4 5 6 7^1			WhWWWWh		2-3 7-8
		//{"melodic minor descending","2122122", "7"},	// 1 2^b3 4 5^b6 7 1		WhWWhWW		2-3 5-6
		//{"aeolian/natural minor",	"2122122", "7"},	//							WhWWhWW		2-3 5-6
		// 6 divisions
		//{"blues",					"321132", "6"},		// 1 b3 4 b5 5 b7			3hWhh3hW
		//{"whole tone",				"222222", "6"},		//							WWWWWW		none
		//{"augmented",				"313131", "6"},
		// 5 divisions
		//{"black key pentatonic",	"22323", "5"},		// 1 b3 4 5 b7				WW3hW3h		
		// 4 divisions
		//{"diminished 7th",			"3333",	"4"},		//
		//{"dominant 7th",			"3333",	"4"}		//
	
	};
	
	vector<string> modes { // stores the names of the different major scale modes, indexed by their note offset from the first note of the scale
		"ionian","dorian","phygrian","lydian","mixolydian","aeolian","locrian"
	};
	vector<int> halfStepPattern; // stores the pattern of half steps from the current note 

public:

	bool active = true;
	string scale = "major";
	string mode = "ionian";
	string chordType = "triad";
	int delay = 10; // delay between notes (when > 0 causes arpeggio)

	void updatePatterns();

	void autoChord(int startNote, int state);

};

extern scale_manager scaleManager;


#endif
