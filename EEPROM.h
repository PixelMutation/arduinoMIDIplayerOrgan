// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)

#ifndef EEPROM_H
#define EEPROM_H

#include "modules.h"


#include <gsl/span.h> // span type used as reference to vector, using Galik's solution from https://stackoverflow.com/questions/44216283/is-it-possible-to-send-part-of-vector-as-a-vector-to-a-function


class EEPROM_manager {
    int EEPROMsize = 1024; // The size of the EEPROM on the microcontroller in bytes. 1024 on Teensy 4.0 but 4284 on Teensy 4.1
    vector<vector<int>> blockAddresses {} // stores the start and end of the addresses of EEPROM 'blocks'
    vector<int> table; // Stores a live version of the EEPROM
    //vector<reference_wrapper<int>> tableRef;
    //gsl::span<int> tableSpan; // stores a reference to EEPROM table
public:
    EEPROM_manager();
    void load(); // loads EEPROM into memory
    void save(); // saves values from memory into EEPROM
    int fetch(int address); // fetches the value from the version stored in memory
    void write(int address, int data, bool save=false); // saves to the version stored in memory

    class block {
        vector<int> dimensions;
        int noOfDimensions;
        int size, start, end;
        
        int blockIndex(vector<int> index); // returns the index within block given the array dimensions
        /*
        gsl::span<int> data1D;
        gsl::span<gsl::span<int>> data2D;
        gsl::span<gsl::span<gsl::span<int>>> data3D;
        vector<reference_wrapper<int>> data1D;
        vector<reference_wrapper<int>> data2D;
        vector<reference_wrapper<int>> data3D;
        */
        
    public:
        block(int size, vector<int> _dimensions); // creates an EEPROM 'block'. It is reccommended to set 'size' larger than needed for future proofing.
        int blockFetch(int address); // returns single value from 'local' address within block
        //int& blockRefFetch(int address); // returns a reference to an item in the block
        void blockWrite(int address, int data, bool save=false);
        gsl::span<int> fetchSpan(int startAddress, int endAddress = -1); // returns a vector referencing part of or all of the block
    }
}





#endif