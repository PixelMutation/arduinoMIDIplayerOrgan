#include "EEPROM.h"

void EEPROM_manager::load() {  // loads EEPROM into memory
    for (int i = 0; i < size; i++) {
        table[i] = EEPROM.read(i);
    }
}
void EEPROM_manager::save() {  // saves values from memory into EEPROM
    for (int i = 0; i < size; i++) {
        EEPROM.write(table[i])
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
    if (data < 256 && data >= 0) {
        table[address] = data;
    }
    else {
        Serial.println("ERROR: Data out of bounds");
    }
    if (save) {
        EEPROM.write(address, data);
    }
    
}

EEPROM_manager eeprom;

