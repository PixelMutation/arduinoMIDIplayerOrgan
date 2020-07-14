// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)


#include "EEPROM_manager.h"

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
    if (end >= EEPROM_SIZE) {
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



// Method definitions:

int EEPROM_manager::block::blockIndex(vector<int> index) { // returns the index within block given the array dimensions
    switch (noOfDimensions) {
        case 1: 
            return index[0];
        case 2:
            return index[0]*dimensions[1] + index[1] - 1;
        case 3:
            return index[0]*dimensions[1]*dimensions[2] + index[1]*dimensions[2] + index[0] - 1;
    }
}

EEPROM_manager::block& EEPROM_manager::createBlock(vector<int> dims) {
    blocks.push_back(block(dims)); // Creates a block and adds it to the block vector using Cameron's answer to adding an object to a vector inline from https://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-vector
}

void EEPROM_manager::load() {  // loads EEPROM into memory
    
}
void EEPROM_manager::save() {  // saves all changed values from memory into EEPROM
    
}

int& EEPROM_manager::fetch(int address) { // fetches a reference (allowing direct modification) to the value from the version stored in memory
    
}

void EEPROM_manager::write(int address, int data, bool save) { // saves to the version stored in memory. 'save' controls whether it should save directly to EEPROM too (VERY SLOW, I reccomend only saving before shutting down, or as a button on a control panel)
    if (address >= 0 && address < size) {
        if (data < 256 && data >= 0) { // ensures within valid data range
            
            if (save) { // if you want to write directly to EEPROM
            
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

EEPROM_manager eepromManager;

