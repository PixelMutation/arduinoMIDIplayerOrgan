#include "I2Cmanager.h"

I2C_manager::I2C_manager(int _port, int _numDevices, int _baseAddress) {
    console.section("I2Cmanager",CORE_PREFIX);
    port        = _port       ;
    numDevices  = _numDevices ;
    baseAddress = _baseAddress;
    switch (port) {
    case 0:
        Wire.begin();
        console.println("started wire");
        wire = &Wire;
        break;
    case 1:
        Wire1.begin();
        console.println("started wire1");
        wire = &Wire1;
        break;
    case 2:
        Wire2.begin();
        console.println("started wire2");
        wire = &Wire2;
        break;
    }
    for (int i=0; i< numDevices; i++) {
        devices.push_back((signed)(baseAddress+i));
    }
    console.sectionEnd("I2Cmanager initialised",CORE_PREFIX);
}

void I2C_manager::write(std::vector<int> bytes, int device) {
    console.println("start I2C write");
    console.println(device);
    wire->beginTransmission((signed)devices[device]);
    for (int deviceNo : devices) {
        console.println(deviceNo);
    }
    console.println(devices[0]);
    for (int byte : bytes) {
        wire->write(byte);
        console.printByte(byte);
        
    }
    wire->endTransmission();
    console.println("finish I2C write");
    
    
  
}
int I2C_manager::read(int device) {
    if (wire->available() > 0) {
        return wire->read();
    } else {
        return 0;
    }
}

portExpander::portExpander(int _port, int _numDevices) : expanders(_port,_numDevices,baseAddress) {
    console.section("portExpander",CORE_PREFIX);
    port = _port;
    numDevices = _numDevices;
    for (int i = 0; i < numDevices; i++) {
        expanders.write({0x00,0x00},i); // A register set to output
        expanders.write({0x01,0x00},i); // B register set to output
        console.println("I2C device configured");
        regA.push_back(0); // sets stored pin states to 0
        regB.push_back(0);
        //console.println("reg modified");
    }
    //instantiateI2C(); // instantiates the "expanders" object
    console.sectionEnd("portExpander initialised",CORE_PREFIX);
}
/*
void portExpander::instantiateI2C() 
    : expanders(port,numDevices,baseAddress)
{}
*/
void portExpander::write(int data, int device) {
    expanders.write({data},device);
}
//writes to a pin on a specific expander
void portExpander::writeToPin(int pin, int state, int expander) {
    int reg;
    if (pin < 8) { // if in register A
        reg = 0x12;        //set register address
        regA[expander]  ^= (-state ^ regA[expander]) & (1UL << pin); // updates byte containing states using individual bit changing method from https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
        expanders.write({reg,regA[expander]},expander); // writes byte to register
    } else {
        reg = 0x13;
        regB[expander] ^= (-state ^ regA[expander]) & (1UL << (pin-8));
        expanders.write({reg,regB[expander]},expander);
    }
}
    
// writes to expanders as if they are combined together
void portExpander::writeToPinCombined(int pin, int state) {
    int device    =  pin/16;                // finds device number
    int devicePin = (pin-device*16);        // finds the pin on the specific expander
    writeToPin(devicePin, state, device);   // writes to the relevant pin
    
}
