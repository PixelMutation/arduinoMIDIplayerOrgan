
#ifndef MODULES_H
#define MODULES_H
// This header file ties together all the modules automatically so any function or class is available anywhere.

// core libraries

#include "Arduino.h"
#include <ArduinoSTL.h>

//#include <iostream>
#include <vector>
//#include <chrono>
#include <deque>



using namespace std; //removes need for std:: prefix for standard library functions and classes

// HEADER FILES FOR CORE MODULES:
//#include "main.h"
#include "scheduler.h"
#include "toggleItem.h" // sends signal to move keys or stops
//include "recieveSignal.h" // recieves signals from the sensors / switches
#include "stateManager.h" // class storing keys or stops
#include "utility.h" // utility functions, such as printing vectors to console
#include "midiManager.h" // manages MIDI I/O and MIDI instruments
//#include "userInterface.h" allows user to configure settings for core modules and plugins
#include "pluginManager.h" // Movement commands are sent through here so plugin effects can be applied

// HEADER FILES FOR PLUGINS: (comment out to deactivate plugins)
//#include "testInterface.h" // a console interface for debugging
#include "octaveCoupler.h" // replicates a keypress x octaves above or below
//#include "arpeggiator.h" // plays a configurable arpeggio from the key pressed
//#include "autoChord.h" // plays a configurable chord from the key pressed
//#include "looper.h" // sets up a configurable loop
//#include "sustain.h" // sustains notes configurably, controlled by a pedal or button
//#include "legato.h" // holds each note you press until the next note is pressed, controlled by pedal or button



#endif
