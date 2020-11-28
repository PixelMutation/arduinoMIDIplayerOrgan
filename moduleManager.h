#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include "global_includes.h"


//#include "stateManager.h"

//void keypressHandler(int keyNumber, int state);

/* ----------------------------- HOOK PARAMETERS ---------------------------- */
#define PARAM_onStart           
#define PARAM_onLoop            
#define PARAM_onKeyMove          int key   , int    newPos, int oldPos
#define PARAM_onUserKeyToggle    int manual, int    key   , int velocity, bool state, int pos
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
#define ARG_onUserKeyToggle     manual,  key   ,  velocity,  state,  pos
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


class moduleTemplate { // This base class contains placeholder functions called at various points during runtime
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
    class hookTemplate {
    public:
        hookTemplate();
        int hookNum;
        int add(moduleTemplate* module);
        bool activate(moduleTemplate* module, int pos);
        bool deactivate(int pos);
    };
    bool isSetup=false;
    void setup();

public:

    int numHooks=0; // increments each time a new hook is initialised
    std::vector<std::vector<moduleTemplate*>> hookModules; // stores pointers to the actual modules

    class onStart            : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onStart           );};
    class onLoop             : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onLoop            );};
    class onKeyMove          : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onKeyMove         );};
    class onUserKeyToggle    : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onUserKeyToggle   );};
    class onSystemKeyToggle  : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onSystemKeyToggle );};
    class onUserStopToggle   : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onUserStopToggle  );};
    class onSystemStopToggle : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onSystemStopToggle);};
    class onPedalToggle      : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onPedalToggle     );};
    class onControlChange    : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onControlChange   );};
    class onMidiKey          : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiKey         );};
    class onMidiCC           : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCC          );};
    class onMidiCCmod        : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCCmod       );};
    class onMidiCCsustain    : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCCsustain   );};
    class onMidiCCchorus     : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCCchorus    );};
    class onMidiCClegato     : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCClegato    );};
    class onMidiCCvolume     : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiCCvolume    );};
    class onMidiInstrument   : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onMidiInstrument  );};
    class onSerialMessage    : public hookTemplate{public: using hookTemplate::hookTemplate; void call (PARAM_onSerialMessage   );};
    
    onStart             OnStart;             
    onLoop              OnLoop;            
    onKeyMove           OnKeyMove;         
    onUserKeyToggle     OnUserKeyToggle;   
    onSystemKeyToggle   OnSystemKeyToggle; 
    onUserStopToggle    OnUserStopToggle;  
    onSystemStopToggle  OnSystemStopToggle;
    onPedalToggle       OnPedalToggle;     
    onControlChange     OnControlChange;   
    onMidiKey           OnMidiKey;         
    onMidiCC            OnMidiCC;          
    onMidiCCmod         OnMidiCCmod;       
    onMidiCCsustain     OnMidiCCsustain;   
    onMidiCCchorus      OnMidiCCchorus;    
    onMidiCClegato      OnMidiCClegato;    
    onMidiCCvolume      OnMidiCCvolume;    
    onMidiInstrument    OnMidiInstrument;  
    onSerialMessage     OnSerialMessage;   
    
    Hooks();
};

extern Hooks hooks;

#endif
