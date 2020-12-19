#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include "global_includes.h"

#include "console.h"
//#include "stateManager.h"

//void keypressHandler(int keyNumber, int state);

/* ----------------------------- HOOK PARAMETERS ---------------------------- */
#define PARAM_onStart           
#define PARAM_onLoop            
#define PARAM_onKeyMove          int key   , int    newPos, int oldPos
#define PARAM_onUserKeyToggle    int manual, int    key   , int velocity, bool state
#define PARAM_onSystemKeyToggle  int manual, int    key   , int velocity, bool state
#define PARAM_onUserStopToggle   int stop  , bool   state
#define PARAM_onSystemStopToggle int stop  , bool   state
#define PARAM_onPedalToggle      int pedal , bool   state
#define PARAM_onControlChange    int panel , int number, int state
#define PARAM_onMidiKey          int manual, int key, int velocity
#define PARAM_onMidiCC           int data1 , int data2
#define PARAM_onMidiCCmod        int data
#define PARAM_onMidiCCsustain    int data
#define PARAM_onMidiCCchorus     int data
#define PARAM_onMidiCClegato     int data
#define PARAM_onMidiCCvolume     int data
#define PARAM_onMidiInstrument   int instrument
#define PARAM_onSerialMessage    std::string target, std::string setting, int data

/* ----------------------------- HOOK ARGUMENTS ----------------------------- */
#define ARG_onStart           
#define ARG_onLoop            
#define ARG_onKeyMove           key   ,  newPos,  oldPos
#define ARG_onUserKeyToggle     manual,  key   ,  velocity,  state
#define ARG_onSystemKeyToggle   manual,  key   ,  velocity,  state
#define ARG_onUserStopToggle    stop  ,  state
#define ARG_onSystemStopToggle  stop  ,  state
#define ARG_onPedalToggle       pedal ,  state
#define ARG_onControlChange     panel ,  number,  state
#define ARG_onMidiKey           manual,  key,     velocity
#define ARG_onMidiCC            data1 ,  data2
#define ARG_onMidiCCmod         data
#define ARG_onMidiCCsustain     data
#define ARG_onMidiCCchorus      data
#define ARG_onMidiCClegato      data
#define ARG_onMidiCCvolume      data
#define ARG_onMidiInstrument    instrument
#define ARG_onSerialMessage     target,  setting,  data


class modules { // This base class contains placeholder functions called at various points during runtime
public:
    

    virtual void onStart            (PARAM_onStart           );
    virtual void onLoop             (PARAM_onLoop            );
    virtual void onKeyMove          (PARAM_onKeyMove         );
    virtual void onUserKeyToggle    (PARAM_onUserKeyToggle   );
    virtual void onSystemKeyToggle  (PARAM_onSystemKeyToggle );
    virtual void onUserStopToggle   (PARAM_onUserStopToggle  );
    virtual void onSystemStopToggle (PARAM_onSystemStopToggle);
    virtual void onPedalToggle      (PARAM_onPedalToggle     );
    virtual void onControlChange    (PARAM_onControlChange   );
    virtual void onMidiKey          (PARAM_onMidiKey         );
    virtual void onMidiCC           (PARAM_onMidiCC          );
    virtual void onMidiCCmod        (PARAM_onMidiCCmod       );
    virtual void onMidiCCsustain    (PARAM_onMidiCCsustain   );
    virtual void onMidiCCchorus     (PARAM_onMidiCCchorus    );
    virtual void onMidiCClegato     (PARAM_onMidiCClegato    );
    virtual void onMidiCCvolume     (PARAM_onMidiCCvolume    );
    virtual void onMidiInstrument   (PARAM_onMidiInstrument  );
    virtual void onSerialMessage    (PARAM_onSerialMessage   );


};


class Hooks { // This struct contains the vectors of references to objects for each trigger point

    int numHooks=0; // increments each time a new hook is initialised
    std::vector<modules*> hookModules; // stores pointers to the actual moduless

public:

    void add(modules* modules);
    
    void callOnStart            (PARAM_onStart           );
    void callOnLoop             (PARAM_onLoop            );
    void callOnKeyMove          (PARAM_onKeyMove         );
    void callOnUserKeyToggle    (PARAM_onUserKeyToggle   );
    void callOnSystemKeyToggle  (PARAM_onSystemKeyToggle );
    void callOnUserStopToggle   (PARAM_onUserStopToggle  );
    void callOnSystemStopToggle (PARAM_onSystemStopToggle);
    void callOnPedalToggle      (PARAM_onPedalToggle     );
    void callOnControlChange    (PARAM_onControlChange   );
    void callOnMidiKey          (PARAM_onMidiKey         );
    void callOnMidiCC           (PARAM_onMidiCC          );
    void callOnMidiCCmod        (PARAM_onMidiCCmod       );
    void callOnMidiCCsustain    (PARAM_onMidiCCsustain   );
    void callOnMidiCCchorus     (PARAM_onMidiCCchorus    );
    void callOnMidiCClegato     (PARAM_onMidiCClegato    );
    void callOnMidiCCvolume     (PARAM_onMidiCCvolume    );
    void callOnMidiInstrument   (PARAM_onMidiInstrument  );
    void callOnSerialMessage    (PARAM_onSerialMessage   );
    
    Hooks();
};

extern Hooks * hooks;

#endif
