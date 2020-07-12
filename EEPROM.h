// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)

#ifndef EEPROM_H
#define EEPROM_H

#include "modules.h"

class EEPROM_manager {
    int size = 1024; // The size of the EEPROM on the microcontroller in bytes. 1024 on Teensy 4.0 but 4284 on Teensy 4.1
    vector<vector<int>> blockAddresses {} // stores the start and end of the addresses of EEPROM 'blocks'
public:
    vector<int> table; // Stores a live version of the EEPROM for quick access
    void load(); // loads EEPROM into memory
    void save(); // saves values from memory into EEPROM
    int fetch(int address); // fetches the value from the version stored in memory
    void write(int address, int data, bool save=false); // saves to the version stored in memory

    class block {

    public:
        int size, start, end;
        block(int size); // creates an EEPROM 'block'. It is reccommended to set 'size' larger than needed for future proofing.
        int blockFetch(int address);
        void blockWrite(int address, int data, bool save=false);
    }
}





#endif