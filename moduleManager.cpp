#include "moduleManager.h"

/* -------------------------------------------------------------------------- */
/*                     VIRTUAL HOOK CALL TEMPLATE METHODS                     */
/* -------------------------------------------------------------------------- */

void modules::onStart            (PARAM_onStart           ) {}
void modules::onLoop             (PARAM_onLoop            ) {}
void modules::onKeyMove          (PARAM_onKeyMove         ) {}
void modules::onUserKeyToggle    (PARAM_onUserKeyToggle   ) {}
void modules::onSystemKeyToggle  (PARAM_onSystemKeyToggle ) {}
void modules::onUserStopToggle   (PARAM_onUserStopToggle  ) {}
void modules::onSystemStopToggle (PARAM_onSystemStopToggle) {}
void modules::onPedalToggle      (PARAM_onPedalToggle     ) {}
void modules::onControlChange    (PARAM_onControlChange   ) {}
void modules::onMidiKey          (PARAM_onMidiKey         ) {}
void modules::onMidiCC           (PARAM_onMidiCC          ) {}
void modules::onMidiCCmod        (PARAM_onMidiCCmod       ) {}
void modules::onMidiCCsustain    (PARAM_onMidiCCsustain   ) {}
void modules::onMidiCCchorus     (PARAM_onMidiCCchorus    ) {}
void modules::onMidiCClegato     (PARAM_onMidiCClegato    ) {}
void modules::onMidiCCvolume     (PARAM_onMidiCCvolume    ) {}
void modules::onMidiInstrument   (PARAM_onMidiInstrument  ) {}
void modules::onSerialMessage    (PARAM_onSerialMessage   ) {}



/* -------------------------------------------------------------------------- */
/*                            HOOK TEMPLATE METHODS                           */
/* -------------------------------------------------------------------------- */



void Hooks::add(modules* module) { // appends module to hooks list, returning position for use in .remove
    numHooks+=1;
    hookModules.push_back(module);
    
}

/* -------------------------------------------------------------------------- */
/*                              HOOK CALL METHODS                             */
/* -------------------------------------------------------------------------- */

void Hooks::callOnStart
    (PARAM_onStart) 
    {for (auto& module : hooks->hookModules) {module->
    onStart
    (ARG_onStart);
    }}
void Hooks::callOnLoop
    (PARAM_onLoop) 
    {for (auto& module : hooks->hookModules) {module->
    onLoop
    (ARG_onLoop);
    }}
void Hooks::callOnKeyMove
    (PARAM_onKeyMove) 
    {for (auto& module : hooks->hookModules) {module->
    onKeyMove
    (ARG_onKeyMove);
    }}
void Hooks::callOnUserKeyToggle
    (PARAM_onUserKeyToggle) 
    {for (auto& module : hooks->hookModules) {module->
    onUserKeyToggle
    (ARG_onUserKeyToggle);
    }}
void Hooks::callOnSystemKeyToggle
    (PARAM_onSystemKeyToggle) 
    {for (auto& module : hooks->hookModules) {module->
    onSystemKeyToggle
    (ARG_onSystemKeyToggle);
    }}
void Hooks::callOnUserStopToggle
    (PARAM_onUserStopToggle) 
    {for (auto& module : hooks->hookModules) {module->
    onUserStopToggle
    (ARG_onUserStopToggle);
    }}
void Hooks::callOnSystemStopToggle
    (PARAM_onSystemStopToggle) 
    {for (auto& module : hooks->hookModules) {module->
    onSystemStopToggle
    (ARG_onSystemStopToggle);
    }}
    
void Hooks::callOnPedalToggle
    (PARAM_onPedalToggle) 
    {for (auto& module : hooks->hookModules) {module->
    onPedalToggle
    (ARG_onPedalToggle);
    }}
void Hooks::callOnControlChange
    (PARAM_onControlChange) 
    {for (auto& module : hooks->hookModules) {module->
    onControlChange
    (ARG_onControlChange);
    }}
void Hooks::callOnMidiKey
    (PARAM_onMidiKey) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiKey
    (ARG_onMidiKey);
    }}
void Hooks::callOnMidiCC
    (PARAM_onMidiCC) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCC
    (ARG_onMidiCC);
    }}
void Hooks::callOnMidiCCmod
    (PARAM_onMidiCCmod) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCCmod
    (ARG_onMidiCCmod);
    }}
void Hooks::callOnMidiCCsustain
    (PARAM_onMidiCCsustain) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCCsustain
    (ARG_onMidiCCsustain);
    }}
void Hooks::callOnMidiCCchorus
    (PARAM_onMidiCCchorus) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCCchorus
    (ARG_onMidiCCchorus);
    }}
void Hooks::callOnMidiCClegato
    (PARAM_onMidiCClegato) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCClegato
    (ARG_onMidiCClegato);
    }}
void Hooks::callOnMidiCCvolume
    (PARAM_onMidiCCvolume) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiCCvolume
    (ARG_onMidiCCvolume);
    }}
void Hooks::callOnMidiInstrument
    (PARAM_onMidiInstrument) 
    {for (auto& module : hooks->hookModules) {module->
    onMidiInstrument
    (ARG_onMidiInstrument);
    }}
void Hooks::callOnSerialMessage
    (PARAM_onSerialMessage) 
    {for (auto& module : hooks->hookModules) {module->
    onSerialMessage
    (ARG_onSerialMessage);
    }}


Hooks::Hooks()  {
    console->section("hooks",CORE_PREFIX);
    console->println((int)hookModules.size());
    console->sectionEnd("hooks initialised",CORE_PREFIX);
}
    


Hooks * hooks = nullptr;



