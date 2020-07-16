// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)

#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include "global_includes.h"
#include <EEPROM.h>


class EEPROM_manager {
    vector<vector<int>> blockAddresses; // stores the start and end of the addresses of EEPROM 'blocks'
    vector<vector<int>> blockDimensions;
    int nullVal = 0; // used as a reference to return (e.g. if address out of bounds))

    

    int index(int x, int blockNumber);
    int index(int x, int y, int blockNumber);
    int index(int x, int y, int z, int blockNumber);

    void constructBlock(vector<int> dimensions);
    int fetch(int address); // fetches the value from the version stored in EEPROM
    void write(int address, int data); // saves to the version stored in EEPROM
public:
    //EEPROM_manager();

    class block1d {
        public:
        int blockNumber;
        vector<int> data;
    };

    class block2d {
        public:
        int blockNumber;
        
        vector<vector<int>> data;
    };
    class block3d {
        public:
        int blockNumber;
        
        vector<vector<vector<int>>> data;
    };

    block1d& newBlock(int x);
    block2d& newBlock(int x, int y);
    block3d& newBlock(int x, int y, int z);

    void load(); // loads the EEPROM block into memory
    void save(); // saves values from memory into EEPROM
    void clear(); // clears of values from EEPROM
protected:
    vector<block1d> blocks1d; // stores the memory block objects
    vector<block2d> blocks2d; // stores the memory block objects
    vector<block3d> blocks3d; // stores the memory block objects
    
};



extern EEPROM_manager eepromManager;

#endif