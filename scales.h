#ifndef SCALES_H
#define SCALES_H
#include "global_includes.h"

#include "moduleManager.h"
#include "effectManager.h"


// stores the patterns used to construct scales, chords and arpeggios
class scale_manager {
	
	std::vector<std::string> chordPatternNames { // stores the patterns (in terms of notes within a scale) of various supported scales
		"triad", "seventh"
	};
	std::vector<std::vector<int>> chordPatterns {
		{0,2,4},
		{0,2,4,6}
	};
	/*
	std::vector<std::vector<std::string>> scalePatterns { // stores the patterns of various supported scales (in terms of a list of half and whole steps) https://www.musictheory.net/lessons https://en.wikipedia.org/wiki/List_of_musical_scales_and_modes https://gumroad.com/l/tldrmusic
		//type						|half-steps|divisions|      Formula			   | Steps |	Semitones
		// 12 divsions
		{"chromatic",				"11111111111","12"},//										all
		// 8 divisions
		{"diminished",				"12121212", "8"},	// 1^2 3^4 5^6 7^8 1		hWhWhWhW	1-2 3-4 5-6 7-8 
		// 7 divisions
		{"major",					"2212221", "7"},	// 1 2 3^4 5 6 7^1			WWhWWWh		3-4 7-8
		{"harmonic minor",			"2122121", "7"},	// 1 2^b3 4 5^b6 7^1		WhWWhWh		2-3 5-6 7-8
		{"melodic minor ascending", "2122221", "7"},	// 1 2^b3 4 5 6 7^1			WhWWWWh		2-3 7-8
		{"melodic minor descending","2122122", "7"},	// 1 2^b3 4 5^b6 7 1		WhWWhWW		2-3 5-6
		{"aeolian/natural minor",	"2122122", "7"},	//							WhWWhWW		2-3 5-6
		// 6 divisions
		{"blues",					"321132", "6"},		// 1 b3 4 b5 5 b7			3hWhh3hW
		{"whole tone",				"222222", "6"},		//							WWWWWW		none
		{"augmented",				"313131", "6"},
		 5 divisions
		{"black key pentatonic",	"22323", "5"},		// 1 b3 4 5 b7				WW3hW3h		
		// 4 divisions
		{"diminished 7th",			"3333",	"4"},		//
		{"dominant 7th",			"3333",	"4"}		//
	
	};
  */
	const std::string scalePatternNames[12] = {
		"chrom",  // chromatic
		
		"dim",    // diminished
		
		"maj",    // major
		"harmMin",// harmonic minor
		"melMin", // melodic minor ascending
		"natMin", // natural minor
		
		"blues",
		"whole tone",
		"aug",    // augmented
		
		"pent",   // pentatonic
		
		"dim7th", // diminished 7th
		"dom7th"  // dominant 7th
	};
	const std::vector<std::vector<byte>> scalePatterns  {	
		{12,1,1,1,1,1,1,1,1,1,1,1},													

		{8,	1,2,1,2,1,2,1,2},								// 1^2 3^4 5^6 7^8 1		hWhWhWhW	1-2 3-4 5-6 7-8 						

		{7,	2,2,1,2,2,2,1},	// "major"						// 1 2 3^4 5 6 7^1			WWhWWWh		3-4 7-8
		{7,	2,1,2,2,1,2,1},	// "harmonic minor"				// 1 2^b3 4 5^b6 7^1		WhWWhWh		2-3 5-6 7-8
		{7,	2,1,2,2,2,2,1},	// "melodic minor ascending"	// 1 2^b3 4 5 6 7^1			WhWWWWh		2-3 7-8
		{7,	2,1,2,2,1,2,2},	// "melodic minor descending"	// 1 2^b3 4 5^b6 7 1		WhWWhWW		2-3 5-6
		{7,	2,1,2,2,1,2,2},	// "aeolian/natural minor"		//							WhWWhWW		2-3 5-6
																				
		{6,	3,2,1,1,3,2},	// blues						
		{6,	2,2,2,2,2,2},	// whole tone					
		{6,	3,1,3,1,3,1},	// augmented					

		{5,	2,2,3,2,3},		// black key pentatonic			

		{4,	3,3,3,3},		// diminished 7th				
		{4,	3,3,3,3}		// dominant 7th					
	};
	
	const std::string modes[7] = { // stores the names of the different major scale modes, indexed by their note offset from the first note of the scale
		"ion",    // ionian
		"dor",    // dorian
		"phy",    // phygrian
		"lyd",    // lydian
		"mix",    // mixolydian
		"aeo",    // aeolian
		"loc"     // locrian
	};
	std::vector<int> halfStepPattern; // stores the pattern of half steps from the current note 

public:

	bool active = true;
	std::string scale = "major";
	std::string mode = "ionian";
	std::string chordType = "triad";
	int delay = 10; // delay between notes (when > 0 causes arpeggio)

	scale_manager();

	void updatePatterns();

	void autoChord(int startNote, int state);

};

extern scale_manager * scaleManager;


#endif
