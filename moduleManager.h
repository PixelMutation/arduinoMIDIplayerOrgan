#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include "global_includes.h"
//#include "stateManager.h"

//void keypressHandler(int keyNumber, int state);

class moduleTemplate { // This base class contains placeholder functions called at various points during runtime
public:

    void onStart();
    void onLoop();

    void onKeyMove(int key, int newPos, int oldPos);
    void onUserKeyToggle(int manual, int key, int velocity, bool state, int pos);
    void onSystemKeyToggle(int manual, int key, int velocity, bool state);

    void onUserStopToggle(int stop, bool state);
    void onSystemStopToggle(int stop, bool state);

    void onPedalToggle(int pedal, bool state);

    void onControlChange(int panel, int number, int state);

    void onMidiKey(int manual, int key, bool state);
    void onMidiCC(int data1, int data2);
    void onMidiInstrument(int instrument);

    void onSerialMessage(string module, string setting, int data);
    

};

struct ModuleCall { // This struct contains the vectors of references to objects for each trigger point
    vector<moduleTemplate*> OnStart;
    vector<moduleTemplate*> OnLoop;
    vector<moduleTemplate*> OnKeyMove;
    vector<moduleTemplate*> OnUserKeyToggle;
    vector<moduleTemplate*> OnSystemKeyToggle;
    vector<moduleTemplate*> OnUserStopToggle;
    vector<moduleTemplate*> OnSystemStopToggle;
    vector<moduleTemplate*> OnPedalToggle;
    vector<moduleTemplate*> OnControlChange;
    vector<moduleTemplate*> OnMidiKey;
    vector<moduleTemplate*> OnMidiCC;
    vector<moduleTemplate*> OnMidiInstrument;
    vector<moduleTemplate*> OnSerialMessage;
};

extern ModuleCall moduleCall;

#endif
