#include "EXAMPLE_MODULE.h"
#include "console.h"       // used for printing to console


exampleModule::exampleModule() { // The constructor must add the object to the std::vectors of hooks in use. uncomment / copy as needed.
    console->section("exampleModule"); // any console->println with a section is indented
    
/* ----------- All hooks needed for this module are activated here ---------- */

    hooks->OnStart               ->add(this);
    hooks->OnLoop                ->add(this);
    hooks->OnKeyMove             ->add(this);
    hooks->OnUserKeyToggle       ->add(this);
    hooks->OnSystemKeyToggle     ->add(this);
    hooks->OnUserStopToggle      ->add(this);
    hooks->OnSystemStopToggle    ->add(this);
    hooks->OnPedalToggle         ->add(this);
    hooks->OnControlChange       ->add(this);
    hooks->OnMidiKey             ->add(this);
    hooks->OnMidiCC              ->add(this);
    hooks->OnMidiCCmod           ->add(this);
    hooks->OnMidiCCsustain       ->add(this);
    hooks->OnMidiCCchorus        ->add(this);
    hooks->OnMidiCClegato        ->add(this);
    hooks->OnMidiCCvolume        ->add(this);
    hooks->OnMidiInstrument      ->add(this);
    hooks->OnSerialMessage       ->add(this);

    // comment out if your plugin isn't an effect
    Fx->addEffect(this,"exampleEffect");
    fxActive = true; // enables the plugin's effect
    
    
    
    // LEAVE THIS, used to show the module has finished construction for debug
    console->sectionEnd("exampleModule initialised");
}

/* --------- All hooks that are needed for this module defined here --------- */

void exampleModule::onStart           (PARAM_onStart           ) {}
void exampleModule::onLoop            (PARAM_onLoop            ) {}
void exampleModule::onKeyMove         (PARAM_onKeyMove         ) {}
void exampleModule::onUserKeyToggle   (PARAM_onUserKeyToggle   ) {}
void exampleModule::onSystemKeyToggle (PARAM_onSystemKeyToggle ) {}
void exampleModule::onUserStopToggle  (PARAM_onUserStopToggle  ) {}
void exampleModule::onSystemStopToggle(PARAM_onSystemStopToggle) {}
void exampleModule::onPedalToggle     (PARAM_onPedalToggle     ) {}
void exampleModule::onControlChange   (PARAM_onControlChange   ) {}
void exampleModule::onMidiKey         (PARAM_onMidiKey         ) {}
void exampleModule::onMidiCC          (PARAM_onMidiCC          ) {}
void exampleModule::onMidiCCmod       (PARAM_onMidiCCmod       ) {}
void exampleModule::onMidiCCsustain   (PARAM_onMidiCCsustain   ) {}
void exampleModule::onMidiCCchorus    (PARAM_onMidiCCchorus    ) {}
void exampleModule::onMidiCClegato    (PARAM_onMidiCClegato    ) {}
void exampleModule::onMidiCCvolume    (PARAM_onMidiCCvolume    ) {}
void exampleModule::onMidiInstrument  (PARAM_onMidiInstrument  ) {}
void exampleModule::onSerialMessage   (PARAM_onSerialMessage   ) {}

// Runs when a key is pressed fxActive ==true
// fxData is a vector of tuples in the form
// {int manual, int key, int velocity, unsigned long delay}
// where the first element is the original keypress
// and the rest are the result of preceeding effects
fxData exampleModule::applyEffect(fxData previousEffect) {
    fxData result = previousEffect;
    console->println("running delay fx");
    // here is an example, which plays a note 'offset' 
    // keys above the note after 'delay' ms
    int delay = 500;
    int offset = -3;
    result.push_back(std::make_tuple(   // uses the first element, which is the key the user pressed
        std::get<0>(result[0]),         // the manual
        std::get<1>(result[0])-offset,  // the key (offset)
        std::get<2>(result[0]),         // the velocity
        delay                           // the delay in ms
    ));
    
    

    return result;
}

exampleModule * ExampleModule = nullptr; 


// uncomment to instantiate

