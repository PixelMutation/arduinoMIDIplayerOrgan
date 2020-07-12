// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)


#include "EEPROM.h"

// Constructors

EEPROM_manager::block::block(int _size) { // creates a memory block. It is reccommended to set 'size' larger than needed for future proofing.
    size = _size;
    if (! blockAddresses.empty()) {
        start = blockAddresses.back()[1] + 1;
    } else {
        start = 0;
    }
    end = start + size - 1;
    blockAddresses[blockAddresses.size()][0] = start;
    blockAddresses[blockAddresses.size()][1] = end;
}

// Method definitions:

void EEPROM_manager::load() {  // loads EEPROM into memory
    for (int i = 0; i < size; i++) {
        table[i] = EEPROM.read(i);
    }
}
void EEPROM_manager::save() {  // saves all changed values from memory into EEPROM
    for (int i = 0; i < size; i++) {
        if (EEPROM.read(i) != table[i]) { // Only writes values that have not changed to save time and increase longevity. reading is faster and doesnt add to wear.
            EEPROM.write(table[i]);
        }
        
    }
}

int EEPROM_manager::fetch(int address) { // fetches the value from the version stored in memory
    if (address < size && address >= 0) { // these are the range of values possible
        return(EEPROM.read(address));
    }
	else {
		Serial.println("ERROR: Invalid EEPROM address");
		return 0;
	}
}

void EEPROM_manager::write(int address, int data, bool save) { // saves to the version stored in memory. 'save' controls whether it should save directly to EEPROM too (VERY SLOW, I reccomend only saving before shutting down, or as a button on a control panel)
    if (address >= 0 && address < size) {
        if (data < 256 && data >= 0) { // ensures within valid data range
            table[address] = data;
        }
        else {
            Serial.println("ERROR: Data out of bounds");
        }
        if (save) { // if you want to write directly to EEPROM
            EEPROM.write(address, data);
        }
    } else {
        Serial.println("ERROR: Invalid EEPROM address");
    }
}

int EEPROM_manager::block::blockFetch(int address) { // retrieves the value from the EEPROM table, indexed within the memory block of the block class instance (e.g. a block containing 61 key positions is indexed 0-60)
    if (address >= 0 && address < size) {
        return fetch(address + start); // returns the value from the EEPROM table stored in memory
    } else {
        Serial.println("ERROR: Invalid EEPROM address");
    }
}
    
void EEPROM_manager::block::blockWrite(int address, int data, bool save) { // writes the to address within the block
    if (address >= 0 && address < size) {
        if (data < 256 && data >= 0) { // ensures within valid data range {
            write(address + start, data);
            if (save) {
                EEPROM.write(address + start, data);
            }
        } else {
            Serial.println("ERROR: Data out of bounds");
    } else {
        Serial.println("ERROR: Invalid EEPROM address");
    }
}





EEPROM_manager eeprom;

