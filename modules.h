
#ifndef MODULES_H
#define MODULES_H
// This header file ties together all the modules automatically so any function or class is available anywhere.

// core libraries


//#include <ArduinoSTL.h>
#include <Arduino.h>

#include <vector>
//#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>



using namespace std; //removes need for std:: prefix for standard library functions and classes

// HEADER FILES FOR CORE MODULES (probably don't deactivate any!):
//#include "main.h"

#include "configuration.h" // GO HERE FOR GENERAL SETUP

#include "multiplexer.h" // controls the multiplexers used by sensors
#include "scheduler.h" // tracks time and activates any scheduled events when the time is right
#include "controls.h" // just for testing various analog and digital input devices
#include "toggleItem.h" // sends signal to move keys or stops
//include "recieveSignal.h" // recieves signals from the sensors / switches
#include "stateManager.h" // class storing keys or stops
#include "utility.h" // utility functions, such as printing vectors to console
#include "midiManager.h" // manages MIDI I/O and MIDI instruments
//#include "userInterface.h" allows user to configure settings for core modules and plugins
#include "pluginManager.h" // Movement commands are sent through here so plugin effects can be applied
#include "EEPROM_manager.h" // Stores a live version of EEPROM in memory in the form of 'blocks' which are objects with the appropriate data structure for what is needed.
#include "sensors.h" // manages the sensors in the program


// HEADER FILES FOR PLUGINS: (comment out to deactivate plugins)
#include "testInterface.h" // a console interface for debugging
#include "octaveCoupler.h" // replicates a keypress x octaves above or below
#include "scales.h" // plays patterns such as chords and arpeggios within scales
//#include "looper.h" // sets up a configurable loop
//#include "sustain.h" // sustains notes configurably, controlled by a pedal or button
//#include "legato.h" // holds each note you press until the next note is pressed, controlled by pedal or button



#endif
