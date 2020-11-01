// The main config for the code - replace these values to match your setup.

// BASICS

// Microcontroller Settings:
#define EEPROM_SIZE  1024   // amount in Teensy 4.0, for 4.1 it is larger
#define NUM_I2C_PORTS 2     // there are 2 on Teensy 4.0 and 3 and Teensy 4.1

// Pins



// Keyboard / Manuals Settings:
#define NUM_MANUALS 1 
#define KEYS_PER_MANUAL  61  // the product of NUM_MANUALS and KEYS_PER_MANUAL must not exceed 256

#define FIRST_NOTE "A"  // the first key of the manual

#define POLYPHONY  20   // number of keys the system can hold down at once per manual (otherwise draws too much power)
#define MAX_ON_TIME 60  // the longest a single note can be held on in seconds (else solenoid overheats)
#define COOLDOWN_TRIGGER 60 // any keypresses longer than this require a cooldown before being used again
#define COOLDOWN 0      // the cooldown duration

// Sensors settings:
#define INTERNAL_ADC false // whether the internal ADC is used 

// Stops settings:
#define NUM_STOPS  11   // total number of stops (<=128)
#define DIVISIONS {11}  // defines how the stops are split into different divisions


// Bass pedals settings: (currently not actuated)
#define NUM_BASS_PEDALS 0
#define FIRST_BASS_NOTE "A" // the first key of the bass pedals


// Control panel settings:
