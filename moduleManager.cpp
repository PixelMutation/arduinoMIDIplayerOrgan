#include "moduleManager.h"

/* -------------------------------------------------------------------------- */
/*                     VIRTUAL HOOK CALL TEMPLATE METHODS                     */
/* -------------------------------------------------------------------------- */

void moduleTemplate::onStart            (PARAM_onStart           ) {}
void moduleTemplate::onLoop             (PARAM_onLoop            ) {}
void moduleTemplate::onKeyMove          (PARAM_onKeyMove         ) {}
void moduleTemplate::onUserKeyToggle    (PARAM_onUserKeyToggle   ) {}
void moduleTemplate::onSystemKeyToggle  (PARAM_onSystemKeyToggle ) {}
void moduleTemplate::onUserStopToggle   (PARAM_onUserStopToggle  ) {}
void moduleTemplate::onSystemStopToggle (PARAM_onSystemStopToggle) {}
void moduleTemplate::onPedalToggle      (PARAM_onPedalToggle     ) {}
void moduleTemplate::onControlChange    (PARAM_onControlChange   ) {}
void moduleTemplate::onMidiKey          (PARAM_onMidiKey         ) {}
void moduleTemplate::onMidiCC           (PARAM_onMidiCC          ) {}
void moduleTemplate::onMidiCCmod        (PARAM_onMidiCCmod       ) {}
void moduleTemplate::onMidiCCsustain    (PARAM_onMidiCCsustain   ) {}
void moduleTemplate::onMidiCCchorus     (PARAM_onMidiCCchorus    ) {}
void moduleTemplate::onMidiCClegato     (PARAM_onMidiCClegato    ) {}
void moduleTemplate::onMidiCCvolume     (PARAM_onMidiCCvolume    ) {}
void moduleTemplate::onMidiInstrument   (PARAM_onMidiInstrument  ) {}
void moduleTemplate::onSerialMessage    (PARAM_onSerialMessage   ) {}



/* -------------------------------------------------------------------------- */
/*                            HOOK TEMPLATE METHODS                           */
/* -------------------------------------------------------------------------- */

Hooks::hookTemplate::hookTemplate() {
    console.println("hook template setup");
    hookNum = hooks.numHooks;
    hooks.numHooks+=1;
    hooks.hookModules.resize(hooks.numHooks);
}

int Hooks::hookTemplate::add(moduleTemplate* module) { // appends module to hooks list, returning position for use in .remove
    hooks.setup();
    console.println("add hook");
    int pos;
    if (hooks.hookModules.empty()) {console.println("empty");}
    if (!! hooks.hookModules[hookNum].empty()) {
         pos = (int)hooks.hookModules[hookNum].size();
    }  else {pos=0;}
    console.println(pos);
    console.println(hookNum);

    hooks.hookModules[hookNum].push_back(module);
    console.println("added");
    return pos;
}
bool Hooks::hookTemplate::activate(moduleTemplate* module, int pos) { // reinstates the module at a position
    if (pos >= 0 && pos < (int)hooks.hookModules[hookNum].size()) {
        hooks.hookModules[hookNum][pos] = module;
        return true;
    } else {return false;}
}
bool Hooks::hookTemplate::deactivate(int pos) { // sets the value here to NULL so nothing happens. Reinstated with .activate
    if (pos >= 0 && pos < (int)hooks.hookModules[hookNum].size()) {
        hooks.hookModules[hookNum][pos] = NULL; // replaces it with NULL to preserve positions of other elements
        return true;
    } else {return false;}
}

/* -------------------------------------------------------------------------- */
/*                              HOOK CALL METHODS                             */
/* -------------------------------------------------------------------------- */

void Hooks::onStart::call
    (PARAM_onStart) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onStart
    (ARG_onStart);
    }}
void Hooks::onLoop::call
    (PARAM_onLoop) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onLoop
    (ARG_onLoop);
    }}
void Hooks::onKeyMove::call
    (PARAM_onKeyMove) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onKeyMove
    (ARG_onKeyMove);
    }}
void Hooks::onUserKeyToggle::call
    (PARAM_onUserKeyToggle) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onUserKeyToggle
    (ARG_onUserKeyToggle);
    }}
void Hooks::onSystemKeyToggle::call
    (PARAM_onSystemKeyToggle) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onSystemKeyToggle
    (ARG_onSystemKeyToggle);
    }}
void Hooks::onUserStopToggle::call
    (PARAM_onUserStopToggle) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onUserStopToggle
    (ARG_onUserStopToggle);
    }}
void Hooks::onSystemStopToggle::call
    (PARAM_onSystemStopToggle) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onSystemStopToggle
    (ARG_onSystemStopToggle);
    }}
    
void Hooks::onPedalToggle::call
    (PARAM_onPedalToggle) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onPedalToggle
    (ARG_onPedalToggle);
    }}
void Hooks::onControlChange::call
    (PARAM_onControlChange) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onControlChange
    (ARG_onControlChange);
    }}
void Hooks::onMidiKey::call
    (PARAM_onMidiKey) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiKey
    (ARG_onMidiKey);
    }}
void Hooks::onMidiCC::call
    (PARAM_onMidiCC) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCC
    (ARG_onMidiCC);
    }}
void Hooks::onMidiCCmod::call
    (PARAM_onMidiCCmod) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCCmod
    (ARG_onMidiCCmod);
    }}
void Hooks::onMidiCCsustain::call
    (PARAM_onMidiCCsustain) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCCsustain
    (ARG_onMidiCCsustain);
    }}
void Hooks::onMidiCCchorus::call
    (PARAM_onMidiCCchorus) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCCchorus
    (ARG_onMidiCCchorus);
    }}
void Hooks::onMidiCClegato::call
    (PARAM_onMidiCClegato) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCClegato
    (ARG_onMidiCClegato);
    }}
void Hooks::onMidiCCvolume::call
    (PARAM_onMidiCCvolume) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiCCvolume
    (ARG_onMidiCCvolume);
    }}
void Hooks::onMidiInstrument::call
    (PARAM_onMidiInstrument) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onMidiInstrument
    (ARG_onMidiInstrument);
    }}
void Hooks::onSerialMessage::call
    (PARAM_onSerialMessage) 
    {for (auto& module : hooks.hookModules[hookNum]) {module->
    onSerialMessage
    (ARG_onSerialMessage);
    }}


Hooks::Hooks() : 
        OnStart(),
        OnLoop(),
        OnKeyMove(),
        OnUserKeyToggle(),
        OnSystemKeyToggle(),
        OnUserStopToggle(),
        OnSystemStopToggle(),
        OnPedalToggle(),
        OnControlChange(),
        OnMidiKey(),
        OnMidiCC(),
        OnMidiCCmod(),
        OnMidiCCsustain(),
        OnMidiCCchorus(),
        OnMidiCClegato(),
        OnMidiCCvolume(),
        OnMidiInstrument(),
        OnSerialMessage()
    {
    console.section("hooks",CORE_PREFIX);
    isSetup = true;
    
    
    
    console.sectionEnd("hooks initialised",CORE_PREFIX);
}
    

void Hooks::setup() {
    if (!isSetup) {
       console.section("hooks",CORE_PREFIX);
        onStart            OnStart;
        onLoop             OnLoop;
        onKeyMove          OnKeyMove;
        onUserKeyToggle    OnUserKeyToggle;
        onSystemKeyToggle  OnSystemKeyToggle;
        onUserStopToggle   OnUserStopToggle;
        onSystemStopToggle OnSystemStopToggle;
        onPedalToggle      OnPedalToggle;
        onControlChange    OnControlChange;
        onMidiKey          OnMidiKey;
        onMidiCC           OnMidiCC;
        onMidiCCmod        OnMidiCCmod;
        onMidiCCsustain    OnMidiCCsustain;
        onMidiCCchorus     OnMidiCCchorus;
        onMidiCClegato     OnMidiCClegato;
        onMidiCCvolume     OnMidiCCvolume;
        onMidiInstrument   OnMidiInstrument;
        onSerialMessage    OnSerialMessage;   
        isSetup = true; 
        console.sectionEnd("hooks initialised",CORE_PREFIX);
    }
    
    
    
    
    
}


Hooks hooks;


