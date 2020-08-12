#include "EXAMPLE_MODULE.h"


// All hooks needed for this module are redefined here (uncomment what you need)

//void exampleModule::onStart() {}
//void exampleModule::onLoop() {}


//void exampleModule::onKeyMove(int key, int newPos, int oldPos) {}
//void exampleModule::onUserKeyToggle(int manual, int key, int velocity, bool state, int pos) {}
//void exampleModule::onSystemKeyToggle(int manual, int key, int velocity, bool state) {}

//void exampleModule::onUserStopToggle(int stop, bool state) {}
//void exampleModule::onSystemStopToggle(int stop, bool state) {}


//void exampleModule::onPedalToggle(int pedal, bool state) {}


//void exampleModule::onControlChange(int panel, int number, int state) {}


//void exampleModule::onMidiKey(int manual, int key, bool state) {}
//void exampleModule::onMidiCC(int data1, int data2) {}
//void exampleModule::onMidiInstrument(int instrument) {}


//void exampleModule::onSerialMessage(string module, string setting, int data) {}



exampleModule ExampleModule;

moduleCall.OnStart.push_back(exampleModule);
