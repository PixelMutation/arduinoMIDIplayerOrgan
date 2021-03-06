#ifndef I2C_MANAGER
#define I2C_MANAGER

#include "global_includes.h"
#include "console.h"
//#include "Wire.h"

//#include <i2c_t3.h>
//#include <Wire.h>
#include <Wire.h>

class I2C_manager {
    TwoWire * wire;
    int port; // which port on the Teensy is used (0-2)
    int numDevices; // the total number of expanders
    std::vector<signed> devices; // the device addresses
    int baseAddress;
public:
    I2C_manager     (int _port, int _numDevices, int _baseAddress);
    void write      (std::vector<int> bytes, int device);
    int  read       (int device);

};

class portExpander { // set up for the MCP23017
    int numDevices; // the number of port expanders
    int port;
    int baseAddress = 0x20;
    I2C_manager expanders;
    //void instantiateI2C();
    std::vector<int> regA;
    std::vector<int> regB;
public:
    portExpander            (int _port, int _numDevices);
    void write              (int data, int device );
    void writeToPin         (int pin, int state, int expander);
    void writeToPinCombined (int pin, int state);
    

};

#endif