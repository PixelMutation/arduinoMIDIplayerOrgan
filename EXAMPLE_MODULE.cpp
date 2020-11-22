#include "EXAMPLE_MODULE.h"



exampleModule::exampleModule() { // The constructor must add the object to the std::vectors of hooks in use. uncomment / copy as needed.
    console.section("exampleModule","PLUG: "); // any console .println will be indented within the section
    
    //All hooks that are needed for this module are activated here (uncomment what you need)

    hooks.OnStart               .add(this);
    hooks.OnLoop                .add(this);
    hooks.OnKeyMove             .add(this);
    hooks.OnUserKeyToggle       .add(this);
    hooks.OnSystemKeyToggle     .add(this);
    hooks.OnUserStopToggle      .add(this);
    hooks.OnSystemStopToggle    .add(this);
    hooks.OnPedalToggle         .add(this);
    hooks.OnControlChange       .add(this);
    hooks.OnMidiKey             .add(this);
    hooks.OnMidiCC              .add(this);
    hooks.OnMidiCCmod           .add(this);
    hooks.OnMidiCCsustain       .add(this);
    hooks.OnMidiCCchorus        .add(this);
    hooks.OnMidiCClegato        .add(this);
    hooks.OnMidiCCvolume        .add(this);
    hooks.OnMidiInstrument      .add(this);
    hooks.OnSerialMessage       .add(this);

    
    
    console.sectionEnd("exampleModule initialised","PLUG: ");
}

//All hooks that are needed for this module are defined here (uncomment what you need)

void exampleModule::OnStart           (PARAM_onStart           ) {}
void exampleModule::OnLoop            (PARAM_onLoop            ) {}
void exampleModule::OnKeyMove         (PARAM_onKeyMove         ) {}
void exampleModule::OnUserKeyToggle   (PARAM_onUserKeyToggle   ) {}
void exampleModule::OnSystemKeyToggle (PARAM_onSystemKeyToggle ) {}
void exampleModule::OnUserStopToggle  (PARAM_onUserStopToggle  ) {}
void exampleModule::OnSystemStopToggle(PARAM_onSystemStopToggle) {}
void exampleModule::OnPedalToggle     (PARAM_onPedalToggle     ) {}
void exampleModule::OnControlChange   (PARAM_onControlChange   ) {}
void exampleModule::OnMidiKey         (PARAM_onMidiKey         ) {}
void exampleModule::OnMidiCC          (PARAM_onMidiCC          ) {}
void exampleModule::OnMidiCCmod       (PARAM_onMidiCCmod       ) {}
void exampleModule::OnMidiCCsustain   (PARAM_onMidiCCsustain   ) {}
void exampleModule::OnMidiCCchorus    (PARAM_onMidiCCchorus    ) {}
void exampleModule::OnMidiCClegato    (PARAM_onMidiCClegato    ) {}
void exampleModule::OnMidiCCvolume    (PARAM_onMidiCCvolume    ) {}
void exampleModule::OnMidiInstrument  (PARAM_onMidiInstrument  ) {}
void exampleModule::OnSerialMessage   (PARAM_onSerialMessage   ) {}


// uncomment to instantiate
//exampleModule ExampleModule;

