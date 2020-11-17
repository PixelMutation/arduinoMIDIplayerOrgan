// The main config for the code - replace these values to match your setup.

// BASICS

/* -------------------------------------------------------------------------- */
/*                         SERIAL AND CONSOLE SETTINGS                        */
/* -------------------------------------------------------------------------- */

#define DEBUG true  // whether debug messages should be printed
#define CORE_PREFIX "CORE: "
#define PLUGIN_PREFIX "PLUG: "
#define INFO_PREFIX "INFO: "

#define SERIAL_BAUDRATE 115200
#define MIDI_BAUDRATE 31250
#define SERIAL_DELAY 5


/* -------------------------------------------------------------------------- */
/*                          MICROCONTROLLER SETTINGS:                         */
/* -------------------------------------------------------------------------- */

#define MICROCONTROLLER
//define TEENSY 4_1

#define EEPROM_SIZE   1080 // amount in Teensy 4.0, for 4.1 it is larger
#define NUM_I2C_PORTS 2    // there are 2 on Teensy 4.0 and 3 and Teensy 4.1


/* -------------------------------------------------------------------------- */
/*                          KEYBOARD/MANUAL SETTINGS:                         */
/* -------------------------------------------------------------------------- */

#define NUM_MANUALS     1
#define KEYS_PER_MANUAL 16 // the product of NUM_MANUALS and KEYS_PER_MANUAL must not exceed 256

#define FIRST_NOTE "A"  // the first key of the manual

#define POLYPHONY        20 // number of keys the system can hold down at once per manual (otherwise draws too much power)
#define MAX_ON_TIME      60 // the longest a single note can be held on in seconds (else solenoid overheats)
#define COOLDOWN_TRIGGER 60 // any keypresses longer than this require a cooldown before being used again
#define COOLDOWN         0  // the cooldown duration

#define _I2C_TIMEOUT 50
/* -------------------------------------------------------------------------- */
/*                              SENSORS SETTINGS:                             */
/* -------------------------------------------------------------------------- */

#define INTERNAL_ADC      false // whether the internal ADC is used //TODO add alternative
#define ANALOG            true  // whether the sensors are analog (should be)
#define ADC_AVERAGING     16    // the averaging level of the ADCs
#define MICROSECOND_DELAY 0     // the delay in microseconds before taking a measurement to allow stabilisation

/* ---------------------------------- PINS ---------------------------------- */
#define KEY_SIG  A9 // has to be supported by Continuous read
#define STOP_SIG A8
#define PED_SIG  A7
#define CTRL_SIG A6

#define KEY_PULLUP  false // whether the sensors are pullup or not (can be a mix for CTRL)
#define STOP_PULLUP false
#define PED_PULLUP  false

#define CONFIRM_PIN 14 // connected to a button as a method of confirming something (such as proceeding to next calibration step)
#define CONFIRM_PIN_MODE INPUT // either INPUT or INPUT_PULLUP depending on the button's wiring

#define MUX_SELECT_PINS {2,3,4,5} // the pins used to select an individual I/O pin on a mux
#define MUX_ENABLE_PINS {9,10,11,12} // the pins used to select which mux to enable via a 4-16 inverting demux (or two 3-8 inverting demuxes)

/* -------------------------------------------------------------------------- */
/*                               STOPS SETTINGS:                              */
/* -------------------------------------------------------------------------- */

#define NUM_STOPS  11   // total number of stops (<=128)
#define DIVISIONS {11}  // defines how the stops are split into different divisions


/* -------------------------------------------------------------------------- */
/*               BASS PEDALS SETTINGS: (currently not actuated)               */
/* -------------------------------------------------------------------------- */

#define NUM_BASS_PEDALS 0
#define FIRST_BASS_NOTE "A" // the first key of the bass pedals


/* -------------------------------------------------------------------------- */
/*                           CONTROL PANEL SETTINGS:                          */
/* -------------------------------------------------------------------------- */
