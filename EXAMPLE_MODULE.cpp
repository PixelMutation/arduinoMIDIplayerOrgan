#include "EXAMPLE_MODULE.h"


// All hooks needed for this module are redefined here (uncomment what you need)

exampleModule::exampleModule() { // The constructor must add the object to the std::vectors of hooks in use. uncomment / copy as needed.
    hook.OnStart.push_back(this);
    hook.OnLoop.push_back(this);

    hook.OnKeyMove.push_back(this);
    hook.OnUserKeyToggle.push_back(this);
    hook.OnSystemKeyToggle.push_back(this);

    hook.OnUserStopToggle.push_back(this);
    hook.OnSystemStopToggle.push_back(this);

    hook.OnPedalToggle.push_back(this);

    hook.OnControlChange.push_back(this);

    hook.OnMidiKey.push_back(this);
    hook.OnMidiCC.push_back(this);
    hook.OnMidiCCmod.push_back(this);
    hook.OnMidiCCsustain.push_back(this);
    hook.OnMidiCCchorus.push_back(this);
    hook.OnMidiCClegato.push_back(this);
    hook.OnMidiCCvolume.push_back(this);
    hook.OnMidiInstrument.push_back(this);

    hook.OnSerialMessage.push_back(this);

    
}


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
//void exampleModule::onMidiCCmod(int data){}}
//void exampleModule::onMidiCCsustain(int data){}}
//void exampleModule::onMidiCCchorus(int data){}}
//void exampleModule::onMidiCClegato(int data){}}
//void exampleModule::onMidiCCvolume(int data){}}
//void exampleModule::onMidiInstrument(int instrument) {}


//void exampleModule::onSerialMessage(string module, string setting, int data) {}



exampleModule ExampleModule;

// Now go to modules.cpp and add the ExampleModule object to whichever hooks you require