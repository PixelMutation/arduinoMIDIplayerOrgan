// This header file ties together all the modules automatically so any function or class is available anywhere.
#ifndef MODULES_H
#define MODULES_H

// core libraries
#include <iostream>
#include <vector>

using namespace std; //removes need for std:: prefix for standard library functions and classes

// HEADER FILES FOR CORE MODULES:
#include "./coreModules/toggleItem.h" // sends signal to move keys or stops
//include "./coreModules/recieveSignal.h" // recieves signals from the sensors / switches
#include "./coreModules/stateManager.h" // class storing keys or stops
#include "./coreModules/utility.h" // utility functions, such as printing vectors to console
//#include "./coreModules/instrumentManager.h" // manages MIDI instruments in relation to stop positions
//#include "./coreModules/MIDI_IN.h" // recieves MIDI input
//#include "./coreModules/MIDI_OUT.h" // sends MIDI output
//#include "./coreModules/userInterface.h" allows user to configure settings for core modules and plugins

// HEADER FILES FOR PLUGINS: (comment out to deactivate plugins)
#include "./pluginModules/testInterface.h" // a console interface for debugging
#include "./pluginModules/octaveCoupler.h" // replicates a keypress x octaves above or below
//#include "./pluginModules/arpeggiator.h" // plays a configurable arpeggio from the key pressed
//#include "./pluginModules/autoChord.h" // plays a configurable chord from the key pressed
//#include "./pluginModules/looper.h" // sets up a configurable loop
//#include "./pluginModules/midiController.h" // sets a configurable zone of the keys to act as a midi controller for a synth (i.e. output MIDI)

#endif
