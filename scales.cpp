#include "scales.h"


scale_manager::scale_manager() {
    console.section("scale_manager",CORE_PREFIX);
    
    
    console.sectionEnd("scale_manager initialised",CORE_PREFIX);
}
// called when any parameters (except arpeggio) are changed to update the active patterns
void scale_manager::updatePatterns() {
    
    std::vector<int> chordPattern {0,2,4,6}; // default is a seventh
    /*
    // The following loop converts the string containing the chosen chord pattern into a std::vector
    for (auto element : chordPatterns) { // linear search to find chosen chord pattern
        if (element[0] == chordType) {
            for (int i = 0; i < (int)element[1].size(); i++) {
                chordPattern[i] = (int)element[1][i] - 48;
                //cout << "\nelement: " << element[1][i];
            }
            break;
        }
    }

    std::vector<int> scalePattern {2,2,1,2,2,2,1}; // default is major scale
    // The following loop converts the string containing the half steps patterns for the chosen scale into a single std::vector
    for (auto element : scalePatterns) { // linear search to find chosen chord pattern
        if (element[0] == scale) {
            for (int i = 0; i < element[1].size(); i++) {
                scalePattern[i] = (int)element[1][i] - 48;
                //cout << "\nelement: " << element[1][i] << " " << scalePattern[i];
            }
            break;
        }
    }

    // The following loop finds which major scale mode is in use and thus the offset to the major scale to be applied
    int startPosition = 0; // offset to the starting position in the scale (affected by major modes)
    if (scale == "major") { // modes only apply to the major scale
        for (int i = 0; i < (int)modes.size(); i++) { // linear search for that mode
            if (modes[i] == mode) {
                startPosition = i; // the modes are indexed by their offset to the major scale 
                break;
            }
            
        }
    }

    // The following builds the half step pattern for each note in the chosen chord pattern in the chosen scale, used when a chord or arpeggio is played
    int steps = 0;
    halfStepPattern.clear();
    for (int i = 1; i < (int)chordPattern.size(); i++) { // for each note in the chord (except the first, as it is already being played)
        steps = 0;
        for (int j = startPosition; j < (chordPattern[i] + startPosition); j++) { // for each note in the scale between the previous note in the chord and the next
            if (j >= (int)scalePattern.size()) { // if the note is beyond the scale pattern's range, subtract the scale pattern size to return to the start
                steps += scalePattern[j - (int)scalePattern.size()]; 
            } else {
                steps += scalePattern[j]; // add to the number of half steps to get to the next note in the chord
            }
            //cout << "\nscalePatternJ: " << scalePattern[j] << "\nsteps: " << steps;
            
        }
        halfStepPattern.push_back(steps); // sets the number of half steps above the root to get to that note
    }
    */
    

}

// plays a chord in a given pattern within the scale
void scale_manager::autoChord(int startNote, int state) {
    
    if (active) {

        for (int i = 0; i < (int)halfStepPattern.size(); i++) { // for each note in the pattern
            cout << halfStepPattern[i];
            if (delay > 0) { // if there is a delay, play as an arpeggio
                stateManager.keys.scheduleActuatorState(0,startNote + halfStepPattern[i], state, delay * i); // request a keypress offset from the current note by the number of half steps for the new note
            } else {
                stateManager.keys.requestActuatorState(0,startNote + halfStepPattern[i], state); // request a keypress offset from the current note by the number of half steps for the new note
            }
        }
    }
}



scale_manager scaleManager;
