// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)


#include "EEPROM.h"

// Constructors
EEPROM_manager::EEPROM_manager() {
    //tableRef = table;
    //tableSpan = gsl::make_span(table); // Creates the span referencing the EEPROM table
}

EEPROM_manager::block::block(vector<int> _dimensions) { // creates a memory block of dimensions {x,y,z} (max 3D) e.g a 1D array of 10: {10}
    auto dimensions = _dimensions;
    noOfDimensions = dimensions.size();
    size = 1;
    for (auto i : dimensions) {
        size = size * i; // finds the total size of the block as the product of its dimensions
    }
    if (! blockAddresses.empty()) {
        start = blockAddresses.back()[1] + 1; // new memory block starts after the last listed block
    } else {
        start = 0;
    }
    end = start + size - 1;
    if (end >= EEPROMsize) {
        Serial.println("ERROR: Block exceeds EEPROM size")
        break;
    }
    blockAddresses[blockAddresses.size()][0] = start; // adds the new block to the address list
    blockAddresses[blockAddresses.size()][1] = end;
    /*
    switch (noOfDimensions) {
        case 1:

        case 2:

        case 3:
            for (int i = 0; i <= dimensions[0]; i++) {
                for (int j=0; j <= dimensions[1]; j++) {
                    data3D[i][j]= tableSpan.subspan()
                }   
            }
    }
    */
}

EEPROM_manager::block::blockIndex(vector<int> index[]) { // returns the index within block given the array dimensions
    switch (noOfDimensions) {
        case 1: 
            return index[0];
        case 2:
            return index[0]*dimensions[1] + index[1] - 1
        case 3:
            return index[0]*dimensions[1]*dimensions[2] + index[1]*dimensions[2] + index[0] - 1
    }
}

// Method definitions:

void EEPROM_manager::load() {  // loads EEPROM into memory
    for (int i = 0; i < size; i++) {
        table[i] = EEPROM.read(i);
    }
}
void EEPROM_manager::save() {  // saves all changed values from memory into EEPROM
    for (int i = 0; i < size; i++) {
        /* DEPRECATED
        if (EEPROM.read(i) != table[i]) { // Only writes values that have not changed to save time and increase longevity. reading is faster and doesnt add to wear.
            EEPROM.write(i,table[i]);
        }
        */
       EEPROM.update(i,table[i]); // update only writes when the value is different
        
    }
}

int& EEPROM_manager::fetch(int address) { // fetches a reference (allowing direct modification) to the value from the version stored in memory
    if (address < size && address >= 0) { // these are the range of values possible
        return(table[address]);
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
            if (save) { // if you want to write directly to EEPROM
            EEPROM.write(address, data);
            }
        }
        else {
            Serial.println("ERROR: Data out of bounds");
        }
        
    } else {
        Serial.println("ERROR: Invalid EEPROM address");
    }
}

int& EEPROM_manager::block::blockFetch(vector<int> index) { // fetches a reference to the value in the EEPROM table (thus can be modified directly), indexed within the memory block of the block class instance. E.g. for a 1D block: {5} or 5; or for a 2D block: {3,5}
    return fetch(blockIndex(index) + start);
}
int& EEPROM_manager::block::blockFetch(int index) { // fetches a reference to the value in the EEPROM table (thus can be modified directly), indexed within the memory block of the block class instance. E.g. for a 1D block: {5} or 5; for a 2D block: {3,5}
    return fetch(index + start);
}
    
void EEPROM_manager::block::blockWrite(vector<int> index, int data, bool save) { // writes the to address within the block
    write(blockIndex(index) + start, data, save);
}

gsl::span<int> EEPROM_manager::block::fetchSpan(int startAddress, int endAddress) { // returns a span (similar to vector) for the given range which acts as a reference to the relevant part of the EEPROM. Set endAddress to -1 to fetch the entire block
    if (endAddress == -1) { // if the whole block is wanted
        return tableSpan.subspan(0, size - 1);
    } else {  // if a section of the block is wanted
        return tableSpan.subspan(startAddress, endAddress);
    }
}




EEPROM_manager eeprom;

