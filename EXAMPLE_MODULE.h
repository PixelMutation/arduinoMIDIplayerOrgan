// NOTICE: This does nothing. However, if you are developing a plugin, make a copy of this
// and EXAMPLE_MODULE.cpp, rename them and remove the functions you don't need. Include your .h in modules.h
#ifndef EXAMPLE_MODULE
#define EXAMPLE_MODULE

#include "global_includes.h"


class exampleModule : public moduleTemplate {
public:
    exampleModule();


    //All hooks that are needed for this module are redeclared as overrides here (uncomment what you need, then add them in modules)
    
    void OnStart                (PARAM_onStart              ) ;
    void OnLoop                 (PARAM_onLoop               ) ;
    void OnKeyMove              (PARAM_onKeyMove            ) ;
    void OnUserKeyToggle        (PARAM_onUserKeyToggle      ) ;
    void OnSystemKeyToggle      (PARAM_onSystemKeyToggle    ) ;
    void OnUserStopToggle       (PARAM_onUserStopToggle     ) ;
    void OnSystemStopToggle     (PARAM_onSystemStopToggle   ) ;
    void OnPedalToggle          (PARAM_onPedalToggle        ) ;
    void OnControlChange        (PARAM_onControlChange      ) ;
    void OnMidiKey              (PARAM_onMidiKey            ) ;
    void OnMidiCC               (PARAM_onMidiCC             ) ;
    void OnMidiCCmod            (PARAM_onMidiCCmod          ) ;
    void OnMidiCCsustain        (PARAM_onMidiCCsustain      ) ;
    void OnMidiCCchorus         (PARAM_onMidiCCchorus       ) ;
    void OnMidiCClegato         (PARAM_onMidiCClegato       ) ;
    void OnMidiCCvolume         (PARAM_onMidiCCvolume       ) ;
    void OnMidiInstrument       (PARAM_onMidiInstrument     ) ;
    void OnSerialMessage        (PARAM_onSerialMessage      ) ;
    
/* --------- Other members within the module might be placed here: -------- */



};

//extern exampleModule ExampleModule;
























#endif