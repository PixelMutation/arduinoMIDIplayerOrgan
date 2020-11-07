#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include "global_includes.h"
#include <vector>
using namespace std;
//#include "stateManager.h"

//void keypressHandler(int keyNumber, int state);

class moduleTemplate { // This base class contains placeholder functions called at various points during runtime
public:
    void onStart();
    void onLoop();

    void onKeyMove         (int key   , int    newPos, int oldPos);
    void onUserKeyToggle   (int manual, int    key   , int velocity, bool state, int pos);
    void onSystemKeyToggle (int manual, int    key   , int velocity, bool state);
    void onUserStopToggle  (int stop  , bool   state);
    void onSystemStopToggle(int stop  , bool   state);
    void onPedalToggle     (int pedal , bool   state);
    void onControlChange   (int panel , int number, int state);

    void onMidiKey         (int manual, int key, int velocity);
    void onMidiCC          (int data1 , int data2);
    void onMidiCCmod       (int data);
    void onMidiCCsustain   (int data);
    void onMidiCCchorus    (int data);
    void onMidiCClegato    (int data);
    void onMidiCCvolume    (int data);
    void onMidiInstrument  (int instrument);

    void onSerialMessage(std::string module, std::string setting, int data);


};


class Hooks { // This struct contains the vectors of references to objects for each trigger point
public:
    std::vector<moduleTemplate*> OnStart;               void start();
    std::vector<moduleTemplate*> OnLoop;                void loop();
    
    std::vector<moduleTemplate*> OnKeyMove;             void keyMove(int key, int newPos, int oldPos);
    std::vector<moduleTemplate*> OnUserKeyToggle;       void userKeyToggle(int manual, int key, int velocity, bool state, int pos);
    std::vector<moduleTemplate*> OnSystemKeyToggle;     void systemKeyToggle(int manual, int key, int velocity, bool state);

    std::vector<moduleTemplate*> OnUserStopToggle;      void userStopToggle(int stop, bool state);
    std::vector<moduleTemplate*> OnSystemStopToggle;    void systemStopToggle(int stop, bool state);

    std::vector<moduleTemplate*> OnPedalToggle;         void pedalToggle(int pedal, bool state);

    std::vector<moduleTemplate*> OnControlChange;       void controlChange(int panel, int number, int state);

    std::vector<moduleTemplate*> OnMidiKey;             void midiKey(int manual, int key, int velocity);
    std::vector<moduleTemplate*> OnMidiCC;              void midiCC(int data1, int data2);
    std::vector<moduleTemplate*> OnMidiCCmod;           void midiCCmod(int data);
    std::vector<moduleTemplate*> OnMidiCCsustain;       void midiCCsustain(int data);
    std::vector<moduleTemplate*> OnMidiCCchorus;        void midiCCchorus(int data);
    std::vector<moduleTemplate*> OnMidiCClegato;        void midiCClegato(int data);
    std::vector<moduleTemplate*> OnMidiCCvolume;        void midiCCvolume(int data);
    std::vector<moduleTemplate*> OnMidiInstrument;      void midiInstrument(int instrument);

    std::vector<moduleTemplate*> OnSerialMessage;       void serialMessage(string module, string setting, int data);

};

extern Hooks hook;

#endif
