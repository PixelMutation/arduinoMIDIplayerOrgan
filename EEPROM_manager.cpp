// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)



#include "EEPROM_manager.h"


EEPROM_manager::EEPROM_manager() {
    console.section("eepromManager",CORE_PREFIX);
    hooks.OnStart.add(this); 
    
    
    console.sectionEnd("eepromManager initialized",CORE_PREFIX);
}


// The following return the index within the actual EEPROM given the coordinates and block number
int EEPROM_manager::index(int x, int blockNumber) {
    return blockDimensions[blockNumber][0] + x;
}
int EEPROM_manager::index(int x, int y, int blockNumber) {
    return blockDimensions[blockNumber][0] + x*blockDimensions[blockNumber][1] + y - 1;
}
int EEPROM_manager::index(int x, int y, int z, int blockNumber) {
    return blockDimensions[blockNumber][0] + x*blockDimensions[blockNumber][1]*blockDimensions[blockNumber][2] + y*blockDimensions[blockNumber][2] + z - 1;
}

// Updates class data regarding the new block, such as its shape and its start and end within the EEPROM
void EEPROM_manager::constructBlock(std::vector<int> dimensions) { // creates a memory block of dimensions {x,y,z} (max 3D) e.g a 1D array of 10: {10}
    //int noOfDimensions = dimensions.size();
    int size, start, end;
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
        Serial.println("ERROR: Block exceeds EEPROM size");
    } else {
        blockDimensions.push_back(dimensions);
        blockAddresses.push_back({start,end}); // adds the new block to the address list
 
    }
    numBlocks +=1;
}

// Creates a new block according to the shape given, and returns a reference to it


EEPROM_manager::block1d& EEPROM_manager::newBlock(int x) { // Creates a new block according to the shape given, and returns a reference to it
    int blockNum = blocks1d.size();
    blocks1d.push_back(block1d()); // Creates a block and adds it to the block std::vector using Cameron's answer to adding an object to a std::vector inline from https://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-std::vector
    constructBlock({x});
    blocks1d[blockNum].blockNumber = blockNum;
    blocks1d[blockNum].data.resize(x);
    
    return blocks1d[blockNum];
}
EEPROM_manager::block2d& EEPROM_manager::newBlock(int x, int y) { // Creates a new block according to the shape given, and returns a reference to it
    int blockNum =  blocks2d.size();
    blocks2d.push_back(block2d()); // Creates a block and adds it to the block std::vector using Cameron's answer to adding an object to a std::vector inline from https://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-std::vector
    constructBlock({x,y});
    blocks2d[blockNum].blockNumber = blockNum;
    blocks2d[blockNum].data.resize(x);
    for (int i = 0; i < x; i++) {
        blocks2d[blockNum].data[i].resize(y);
    }
    
    return blocks2d[blockNum];
}
EEPROM_manager::block3d& EEPROM_manager::newBlock(int x, int y, int z) { // Creates a new block according to the shape given, and returns a reference to it
    int blockNum =  blocks3d.size();
    blocks3d.push_back(block3d()); // Creates a block and adds it to the block std::vector using Cameron's answer to adding an object to a std::vector inline from https://stackoverflow.com/questions/15802006/how-can-i-create-objects-while-adding-them-into-a-std::vector
    constructBlock({x,y,z});
    blocks3d[blockNum].blockNumber = blockNum;
    blocks3d[blockNum].data.resize(x);
    for (int i = 0; i < x; i++) {
        blocks3d[blockNum].data[i].resize(y);
        for (int j = 0; j < y; j++) {
            blocks3d[blockNum].data[i][j].resize(z);
        }
    }
    
    return blocks3d[blockNum];
}

void EEPROM_manager::onStart() {
    console.println("reached eeprom load");
    load();
}


void EEPROM_manager::clear() { // clears all from EEPROM
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.update(i, 0); // sets all non 0 values to 0
    }
}

void EEPROM_manager::load() {  // loads EEPROM into memory
    // Loads every 1d, 2d and 3d block in turn
    for (unsigned int blockNum = 0; blockNum < blocks1d.size(); blockNum++) {
        for (int x=0; x <= blockDimensions[blockNum][0]; x++) {
            blocks1d[blockNum].data[x] = fetch(index(x,blockNum));
        }
    }
    for (unsigned int blockNum = 0; blockNum < blocks2d.size(); blockNum++) {
        for (int x = 0; x <= blockDimensions[blockNum][0]; x++) {
            for (int y=0; y <= blockDimensions[blockNum][1]; y++) {
                blocks2d[blockNum].data[x][y] = fetch(index(x,y,blockNum));
            }
        } 
    }
    for (unsigned int blockNum = 0; blockNum < blocks2d.size(); blockNum++) {
        for (int x = 0; x <= blockDimensions[blockNum][0]; x++) {
            for (int y=0; y <= blockDimensions[blockNum][1]; y++) {
                for (int z=0; z <= blockDimensions[blockNum][2]; z++) {
                    blocks3d[blockNum].data[x][y][z] = fetch(index(x,y,z,blockNum));
                }
            }   
        }
    }
}

void EEPROM_manager::save() {  // saves all changed values from memory into EEPROM
    for (unsigned int blockNum = 0; blockNum < blocks1d.size(); blockNum++) { // for each 1d block
        if (blocks1d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][0]) { // checks if std::vector's dimensions match those stored
            for (int x=0; x <= blockDimensions[blockNum][0]; x++) { 
                EEPROM.update(index(x,blockNum),blocks1d[blockNum].data[x]);
            }
        } else {
            Serial.println("ERROR: EEPROM block changed size");
        }
        
    }
    for (unsigned int blockNum = 0; blockNum < blocks2d.size(); blockNum++) { // for each 2d block
        if (blocks2d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][0] && blocks2d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][1]) {// checks if std::vector's dimensions match those stored
            for (int x=0; x <= blockDimensions[blockNum][0]; x++) {
                for (int y=0; y <= blockDimensions[blockNum][1]; y++) {
                    EEPROM.update(index(x,y,blockNum),blocks2d[blockNum].data[x][y]);
                }
            } 
        } else {
            Serial.println("ERROR: EEPROM block changed size");
        }
        
    }
    for (unsigned int blockNum = 0; blockNum < blocks2d.size(); blockNum++) { // for each 3d block
        if (blocks3d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][0] && blocks3d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][1] && blocks3d[blockNum].data.size() == (unsigned)blockDimensions[blockNum][2] ) { // checks if std::vector's dimensions match those stored
            for (int x = 0; x <= blockDimensions[blockNum][0]; x++) {
                for (int y=0; y <= blockDimensions[blockNum][1]; y++) {
                    for (int z=0; z <= blockDimensions[blockNum][2]; z++) {
                        EEPROM.update(index(x,y,z,blockNum),blocks3d[blockNum].data[x][y][z]);
                    }
                }   
            }
        } else {
            Serial.println("ERROR: EEPROM block changed size");
        }
    }
}

int EEPROM_manager::fetch(int address) { // returns the EEPROM value at that location
    if (address < EEPROM_SIZE && address >= 0) { // these are the range of values possible
        return(EEPROM.read(address));
    }
	else {
		Serial.println("ERROR: Invalid EEPROM address");
        return nullVal;
	}
}

void EEPROM_manager::write(int address, byte data) { // writes to the EEPROM
    if (address < EEPROM_SIZE && address >= 0) {
        if (data < 256 && data >= 0) { // ensures within valid data range
            EEPROM.update(address, data);
        } else {
            Serial.println("ERROR: Data out of bounds");
        }
        
    } else {
        Serial.println("ERROR: Invalid EEPROM address");
    }
}



EEPROM_manager eepromManager;


