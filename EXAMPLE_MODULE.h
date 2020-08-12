// NOTICE: This does nothing. However, if you are developing a plugin, make a copy of this
// and EXAMPLE_MODULE.cpp, rename them and remove the functions you don't need. Include your .h in modules.h
#ifndef EXAMPLE_MODULE
#define EXAMPLE_MODULE

#include "global_includes.h"


class exampleModule : public moduleTemplate {
public:
    // All hooks that are needed for this module are redeclared as overrides here (uncomment what you need)
    
    //void onStart() override;
    //void onLoop() override;

    //void onKeyMove(int key, int newPos, int oldPos) override;
    //void onUserKeyToggle(int manual, int key, int velocity, bool state, int pos) override;
    //void onSystemKeyToggle(int manual, int key, int velocity, bool state) override;

    //void onUserStopToggle(int stop, bool state) override;
    //void onSystemStopToggle(int stop, bool state) override;

    //void onPedalToggle(int pedal, bool state) override;

    //void onControlChange(int panel, int number, int state) override;

    //void onMidiKey(int manual, int key, bool state) override;
    //void onMidiCC(int data1, int data2) override;
    //void onMidiInstrument(int instrument) override;

    //void onSerialMessage(string module, string setting, int data) override;

private:
    // Other functions within the module might be placed here:



};

extern exampleModule ExampleModule;
























#endif