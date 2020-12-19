// NOTICE: This does nothing. However, if you are developing a plugin, make a copy of this
// and EXAMPLE_MODULE.cpp, rename them and remove the parts you don't need. Include your .h in modules.h
#ifndef EXAMPLE_MODULE
#define EXAMPLE_MODULE

#include "global_includes.h"

#include "moduleManager.h" // used to add module to hooks

#include "effectManager.h" // comment out if plugin isn't an effect

                    // if called by hooks  // if plugin is an effect
class exampleModule : public modules, public fxTemplate {
public: 
    exampleModule();


    //All hooks that are needed for this module are redeclared as overrides here (comment what you don't need)
    // Once defined, uncomment /*override*/ to ensure it overrides 
    void onStart                (PARAM_onStart              ) /*override*/;
    void onLoop                 (PARAM_onLoop               ) /*override*/;
    void onKeyMove              (PARAM_onKeyMove            ) /*override*/;
    void onUserKeyToggle        (PARAM_onUserKeyToggle      ) /*override*/;
    void onSystemKeyToggle      (PARAM_onSystemKeyToggle    ) /*override*/;
    void onUserStopToggle       (PARAM_onUserStopToggle     ) /*override*/;
    void onSystemStopToggle     (PARAM_onSystemStopToggle   ) /*override*/;
    void onPedalToggle          (PARAM_onPedalToggle        ) /*override*/;
    void onControlChange        (PARAM_onControlChange      ) /*override*/;
    void onMidiKey              (PARAM_onMidiKey            ) /*override*/;
    void onMidiCC               (PARAM_onMidiCC             ) /*override*/;
    void onMidiCCmod            (PARAM_onMidiCCmod          ) /*override*/;
    void onMidiCCsustain        (PARAM_onMidiCCsustain      ) /*override*/;
    void onMidiCCchorus         (PARAM_onMidiCCchorus       ) /*override*/;
    void onMidiCClegato         (PARAM_onMidiCClegato       ) /*override*/;
    void onMidiCCvolume         (PARAM_onMidiCCvolume       ) /*override*/;
    void onMidiInstrument       (PARAM_onMidiInstrument     ) /*override*/;
    void onSerialMessage        (PARAM_onSerialMessage      ) /*override*/;
    
    // This is run when the module acts as an 'effect', so comment out if your plugin isn't one
    fxData applyEffect(fxData previousResult);
    
/* --------- Other members within the module might be placed here: -------- */



};
// uncommen to instantiate
extern exampleModule * ExampleModule;
























#endif