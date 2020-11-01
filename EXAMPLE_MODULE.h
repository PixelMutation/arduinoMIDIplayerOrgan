// NOTICE: This does nothing. However, if you are developing a plugin, make a copy of this
// and EXAMPLE_MODULE.cpp, rename them and remove the functions you don't need. Include your .h in modules.h
#ifndef EXAMPLE_MODULE
#define EXAMPLE_MODULE

#include "global_includes.h"


class exampleModule : public moduleTemplate {
public:
    exampleModule();


    // All hooks that are needed for this module are redeclared as overrides here (uncomment what you need, then add them in modules)
    
    //void onStart();
    //void onLoop();

    //void onKeyMove(int key, int newPos, int oldPos);
    //void onUserKeyToggle(int manual, int key, int velocity, bool state, int pos);
    //void onSystemKeyToggle(int manual, int key, int velocity, bool state);

    //void onUserStopToggle(int stop, bool state);
    //void onSystemStopToggle(int stop, bool state);

    //void onPedalToggle(int pedal, bool state);

    //void onControlChange(int panel, int number, int state);

    //void onMidiKey(int manual, int key, int velocity);
    //void onMidiCC(int data1, int data2);
    //void onMidiCCmod(int data);
    //void onMidiCCsustain(int data);
    //void onMidiCCchorus(int data);
    //void onMidiCClegato(int data);
    //void onMidiCCvolume(int data);
    //void onMidiInstrument(int instrument);

    //void onSerialMessage(string module, string setting, int data) ;



    // Other functions within the module might be placed here:



};

extern exampleModule ExampleModule;
























#endif