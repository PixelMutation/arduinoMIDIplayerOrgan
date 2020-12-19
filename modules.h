
#ifndef MODULES_H
#define MODULES_H

// core libraries

// HEADER FILES FOR CORE MODULES (probably don't deactivate any!):
//#include "main.h"


#include "configuration.h" // GO HERE FOR GENERAL SETUP

#include "global_includes.h" // stores includes for the globally required libraries

/* -------------------------------------------------------------------------- */
/*                                MAIN MODULES                                */
/* -------------------------------------------------------------------------- */

#include "multiplexer.h"     // controls the multiplexers used by sensors
#include "sensors.h"         // manages the sensors in the program

#include "stateManager.h"    // class storing keys or stops
#include "scheduler.h"       // tracks time and activates any scheduled events when the time is right

//#include "controls.h"        // just for testing various analog and digital input devices

#include "midiManager.h"     // manages MIDI I/O and MIDI instruments

#include "moduleManager.h"   // Movement commands are sent through here so plugin effects can be applied
#include "EEPROM_manager.h"  // Stores a live version of EEPROM in memory in the form of 'blocks' which are objects with the appropriate data structure for what is needed.

#include "controls.h"        // just for testing various analog and digital input devices

#include "I2Cmanager.h"      // allows easy use of I2C ports and I/O expanders
#include "I2Cactuators.h"    // sends signals to I2C actuators

#include "utility.h"         // utility functions, such as printing things to console
#include "console.h"         // manages messages sent to the console
/* -------------------------------------------------------------------------- */
/*                      PLUGINS (COMMENT OUT TO DISABLE)                      */
/* -------------------------------------------------------------------------- */

#include "EXAMPLE_MODULE.h"  // If developing a plugin, look at this. 


//#include "testInterface.h"   // a console interface for debugging
//#include "octaveCoupler.h"   // replicates a keypress x octaves above or below
//#include "scales.h"          // plays patterns such as chords and arpeggios within scales
//#include "looper.h" // sets up a configurable loop
//#include "sustain.h" // sustains notes configurably, controlled by a pedal or button
//#include "legato.h" // holds each note you press until the next note is pressed, controlled by pedal or button




/*

vector<stateManager*> manuals;
void instantiateModules();
*/

#endif
