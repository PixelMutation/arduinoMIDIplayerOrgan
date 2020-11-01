#include "I2Cmanager.h"

I2C_manager::I2C_manager (int _port, int _numDevices, int _baseAddress) {
    port = _port;
    numDevices = _numDevices;
    baseAddress = _baseAddress;
    switch (port) {
    case 0:
        Wire.begin();
        wire = &Wire;
        break;
    case 1:
        Wire1.begin();
        wire = &Wire1;
        break;
    case 2:
        Wire2.begin();
        wire = &Wire2;
        break;
    }
    for (int i=0; i< numDevices; i++) {
        devices.push_back(baseAddress+i);
    }
}

void I2C_manager::write(vector<int> bytes, int device) {
    wire->beginTransmission(devices[device]);
    for (int byte : bytes) {
        wire->write(byte);
    }
    wire->endTransmission();
}
int I2C_manager::read(int device) {
    if (wire->available() > 0) {
        return wire->read();
    }
}

portExpander::portExpander(int _port, int _numDevices) {
    port = _port;
    numDevices = _numDevices;
    I2C_manager expanders(port,numDevices,baseAddress);
    for (int i = 0; i < numDevices; i++) { 
        expanders.write({0x00,0x00},i); // A register set to output
        expanders.write({0x01,0x00},i); // B register set to output
        regA.push_back(0); // sets stored pin states to 0
        regB.push_back(0);
    }
}

void portExpander::write(int data, int device) {
    expanders.write({data},device);
}
//writes to a pin on a specific expander
void portExpander::writeToPin(int pin, int state, int expander) {
    int reg;
    if (pin < 8) { // if in register A
        reg = 0x12;        //set register address
        regA[expander]  ^= (-state ^ regA[expander]) & (1UL << pin); // updates byte containing states using individual bit changing method from https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
        expanders.write({reg},regA[expander]); // writes byte to register
    } else {
        reg = 0x13;
        regB[expander] ^= (-state ^ regA[expander]) & (1UL << pin-8);
        expanders.write({reg},regA[expander]);
    }
}
    
// writes to expanders as if they are combined together
void portExpander::writeToPinCombined(int pin, int state) {
    int device = pin/16; // finds device number
    int devicePin = (pin-device*16); // finds the pin on the specific expander
    writeToPin(devicePin, state, device); // writes to the relevant pin
    
}
