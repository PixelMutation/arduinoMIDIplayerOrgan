#include "moduleManager.h"

void moduleTemplate::onStart() {

}
void moduleTemplate::onLoop() {}

void moduleTemplate::onKeyMove         (int key, int newPos, int oldPos) {}
void moduleTemplate::onUserKeyToggle   (int manual, int key, int velocity, bool state, int pos) {}
void moduleTemplate::onSystemKeyToggle (int manual, int key, int velocity, bool state) {}

void moduleTemplate::onUserStopToggle  (int stop, bool state) {}
void moduleTemplate::onSystemStopToggle(int stop , bool state) {}

void moduleTemplate::onPedalToggle     (int pedal, bool state) {}

void moduleTemplate::onControlChange   (int panel, int number, int state) {}

void moduleTemplate::onMidiKey         (int manual, int key  , int velocity) {}
void moduleTemplate::onMidiCC          (int data1 , int data2) {}
void moduleTemplate::onMidiCCmod       (int data) {}
void moduleTemplate::onMidiCCsustain   (int data) {}
void moduleTemplate::onMidiCCchorus    (int data) {}
void moduleTemplate::onMidiCClegato    (int data) {}
void moduleTemplate::onMidiCCvolume    (int data) {}
void moduleTemplate::onMidiInstrument  (int instrument) {}

void moduleTemplate::onSerialMessage   (std::string module, std::string setting, int data) {}


void Hooks::start() {
    for (auto module : OnStart) {
		module->onStart();
	}
}
void Hooks::loop() {
    for (auto module : OnLoop) {
        module->onLoop();
    }
}

void Hooks::keyMove(int key, int newPos, int oldPos) {
    for (auto module : OnKeyMove) {
        module->onKeyMove(key,newPos,oldPos);
    }
}
void Hooks::userKeyToggle(int manual, int key, int velocity, bool state, int pos) {
    for (auto module : OnUserKeyToggle) {
        module->onUserKeyToggle(manual,key,velocity,state,pos);
    }
}
void Hooks::systemKeyToggle(int manual, int key, int velocity, bool state) {
    for (auto module : OnSystemKeyToggle) {
        module->onSystemKeyToggle(manual,key,velocity,state);
    }
}

void Hooks::userStopToggle(int stop, bool state) {
    for (auto module : OnUserStopToggle) {
        module->onUserStopToggle(stop,state);
    }
}
void Hooks::systemStopToggle(int stop, bool state) {
    for (auto module : OnSystemStopToggle) {
        module->onSystemStopToggle(stop,state);
    }
}

void Hooks::pedalToggle(int pedal, bool state) {
    for (auto module : OnPedalToggle) {
        module->onPedalToggle(pedal,state);
    }
}

void Hooks::controlChange(int panel, int number, int state) {
    for (auto module : OnControlChange) {
        module->onControlChange(panel,number,state);
    }
}

void Hooks::midiKey(int manual, int key, int velocity) {
    for (auto module : OnMidiKey) {
        module->onMidiKey(manual,key,velocity);
    }
}
void Hooks::midiCC(int data1, int data2) {
    for (auto module : OnMidiCC) {
        module->onMidiCC(data1,data2);
    }
}
void Hooks::midiCCmod(int data) {
    for (auto module : OnMidiCCmod) {
        module->onMidiCCmod(data);
    }
}
void Hooks::midiCCsustain(int data) {
    for (auto module : OnMidiCCsustain) {
        module->onMidiCCsustain(data);
    }
}
void Hooks::midiCCchorus(int data) {
    for (auto module : OnMidiCCchorus) {
        module->onMidiCCchorus(data);
    }
}
void Hooks::midiCClegato(int data) {
    for (auto module : OnMidiCClegato) {
        module->onMidiCClegato(data);
    }
}
void Hooks::midiCCvolume(int data) {
    for (auto module : OnMidiCCvolume) {
        module->onMidiCCvolume(data);
    }
}
void Hooks::midiInstrument(int instrument) {
    for (auto module : OnMidiInstrument) {
        module->onMidiInstrument(instrument);
    }
}

void Hooks::serialMessage(std::string target, std::string setting, int data) {
    for (auto module : OnSerialMessage) {
        module->onSerialMessage(target,setting,data);
    }
}





Hooks hook;


