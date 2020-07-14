// A class which stores and manages EEPROM data. Mainly used for calibrated sensor positions (e.g. the position at which keys activate)

#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include "modules.h"
#include <cassert>
//#include <boost\multi_array.hpp> // multi array library for variable dimension numbers


//#include <gsl/span.h> // span type used as reference to vector, using Galik's solution from https://stackoverflow.com/questions/44216283/is-it-possible-to-send-part-of-vector-as-a-vector-to-a-function


class EEPROM_manager {
    vector<vector<int>> blockAddresses; // stores the start and end of the addresses of EEPROM 'blocks'
    class block {
        vector<int> dimensions;
        int noOfDimensions;
        int size, start, end; // size of block, indices within EEPROM
        
        int data1d[];       // The blocks can be either 1d, 2d or 3d
        int data2d[][];
        int data3d[][][];
        

        //typedef boost::multi_array<int, nofOfDimensions> array_type 
        //boost::
        int blockIndex(vector<int> index); // returns the index within block given the array dimensions

    public:
        block(vector<int> _dimensions); // creates an EEPROM 'block'. It is reccommended to set 'size' larger than needed for future proofing.
        int blockFetch(int address); // returns single value from 'local' address within block
        //int& blockRefFetch(int address); // returns a reference to an item in the block
        void blockWrite(int address, int data, bool save=false);
        
    };
    
    vector<block> blocks; // stores the memory block objects
public:
    EEPROM_manager();
    void load(); // loads EEPROM into memory
    void save(); // saves values from memory into EEPROM
    int fetch(int address); // fetches the value from the version stored in memory
    void write(int address, int data, bool save=false); // saves to the version stored in memory
    block& createBlock(vector<int> dims);
    
};





#endif