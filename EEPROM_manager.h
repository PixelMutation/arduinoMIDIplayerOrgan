// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)

#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include "global_includes.h"

#include "moduleManager.h"


class EEPROM_manager : public moduleTemplate{
    int numBlocks;
    std::vector<std::array<int,2>> blockAddresses; // stores the start and end of the addresses of EEPROM 'blocks'
    std::vector<std::vector<int>> blockDimensions;
    int nullVal = 0; // used as a reference to return (e.g. if address out of bounds))

    

    int index(int x, int blockNumber);
    int index(int x, int y, int blockNumber);
    int index(int x, int y, int z, int blockNumber);

    void constructBlock(std::vector<int> dimensions);
    int  fetch(int address);           // fetches the value from the version stored in EEPROM
    void write(int address, byte data); // saves to the version stored in EEPROM
public:
    
    EEPROM_manager();
    
    class block1d{
        friend EEPROM_manager;
        int blockNumber;
        public:
        std::vector<byte> data;
    };

    class block2d{
        friend EEPROM_manager;
        int blockNumber;
        public:
        std::vector<std::vector<byte>> data;
    };
    class block3d{
        friend EEPROM_manager;
        int blockNumber;
        public:
        std::vector<std::vector<std::vector<byte>>> data;
    };

    block1d& newBlock(int x);
    block2d& newBlock(int x, int y);
    block3d& newBlock(int x, int y, int z);

    void onStart();

    void load(); // loads the EEPROM block into memory
    void save(); // saves values from memory into EEPROM
    void clear(); // clears of values from EEPROM
protected:
    std::vector<block1d> blocks1d; // stores the memory block objects
    std::vector<block2d> blocks2d; // stores the memory block objects
    std::vector<block3d> blocks3d; // stores the memory block objects
    
};

using eepromBlock1D = EEPROM_manager::block1d&;
using eepromBlock2D = EEPROM_manager::block2d&;
using eepromBlock3D = EEPROM_manager::block3d&;

extern EEPROM_manager * eepromManager;

#endif