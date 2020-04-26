

// This header file ties together all the modules automatically so any function or class is available anywhere.
#ifndef MODULES_H
#define MODULES_H


// core libraries
//#include <ArduinoSTL.h>
//#include "Arduino.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <deque>



using namespace std; //removes need for std:: prefix for standard library functions and classes

// HEADER FILES FOR CORE MODULES:
#include "main.h"
#include "./coreModules/toggleItem.h" // sends signal to move keys or stops
//include "recieveSignal.h" // recieves signals from the sensors / switches
#include "./coreModules/stateManager.h" // class storing keys or stops
#include "./coreModules/utility.h" // utility functions, such as printing vectors to console
#include "./coreModules/midiManager.h" // manages MIDI I/O and MIDI instruments
//#include "./coreModules/userInterface.h" allows user to configure settings for core modules and plugins
#include "./coreModules/pluginManager.h" // Movement commands are sent through here so plugin effects can be applied

// HEADER FILES FOR PLUGINS: (comment out to deactivate plugins)
#include "./pluginModules/testInterface.h" // a console interface for debugging
#include "./pluginModules/octaveCoupler.h" // replicates a keypress x octaves above or below
//#include "./pluginModules/arpeggiator.h" // plays a configurable arpeggio from the key pressed
//#include "./pluginModules/autoChord.h" // plays a configurable chord from the key pressed
//#include "./pluginModules/looper.h" // sets up a configurable loop
//#include "./pluginModules/sustain.h" // sustains notes configurably, controlled by a pedal or button
//#include "./pluginModules/legato.h" // holds each note you press until the next note is pressed, controlled by pedal or button



#endif
