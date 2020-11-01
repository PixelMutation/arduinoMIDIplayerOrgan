#include "moduleManager.h"

void moduleTemplate::onStart() {

}
void moduleTemplate::onLoop() {}

void moduleTemplate::onKeyMove(int key, int newPos, int oldPos) {}
void moduleTemplate::onUserKeyToggle(int manual, int key, int velocity, bool state, int pos) {}
void moduleTemplate::onSystemKeyToggle(int manual, int key, int velocity, bool state) {}

void moduleTemplate::onUserStopToggle(int stop, bool state) {}
void moduleTemplate::onSystemStopToggle(int stop, bool state) {}

void moduleTemplate::onPedalToggle(int pedal, bool state) {}

void moduleTemplate::onControlChange(int panel, int number, int state) {}

void moduleTemplate::onMidiKey(int manual, int key, int velocity) {}
void moduleTemplate::onMidiCC(int data1, int data2) {}
void moduleTemplate::onMidiCCmod(int data) {}
void moduleTemplate::onMidiCCsustain(int data) {}
void moduleTemplate::onMidiCCchorus(int data) {}
void moduleTemplate::onMidiCClegato(int data) {}
void moduleTemplate::onMidiCCvolume(int data) {}
void moduleTemplate::onMidiInstrument(int instrument) {}

void moduleTemplate::onSerialMessage(string module, string setting, int data) {}


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
        module->onUserKeyToggle();
    }
}
void Hooks::systemKeyToggle(int manual, int key, int velocity, bool state) {
    for (auto module : OnSystemKeyToggle) {
        module->onSystemKeyToggle();
    }
}

void Hooks::userStopToggle(int stop, bool state) {
    for (auto module : OnUserStopToggle) {
        module->onUserStopToggle();
    }
}
void Hooks::systemStopToggle(int stop, bool state) {
    for (auto module : OnSystemStopToggle) {
        module->onSystemStopToggle();
    }
}

void Hooks::pedalToggle(int pedal, bool state) {
    for (auto module : OnPedalToggle) {
        module->onPedalToggle();
    }
}

void Hooks::controlChange(int panel, int number, int state) {
    for (auto module : OnControlChange) {
        module->onControlChange();
    }
}

void Hooks::midiKey(int manual, int key, int velocity) {
    for (auto module : OnMidiKey) {
        module->onMidiKey();
    }
}
void Hooks::midiCC(int data1, int data2) {
    for (auto module : OnMidiCC) {
        module->onMidiCC();
    }
}
void Hooks::midiCCmod(int data) {
    for (auto module : OnMidiCCmod) {
        module->onMidiCCmod();
    }
}
void Hooks::midiCCsustain(int data) {
    for (auto module : OnMidiCCsustain) {
        module->onMidiCCsustain();
    }
}
void Hooks::midiCCchorus(int data) {
    for (auto module : OnMidiCCchorus) {
        module->onMidiCCchorus();
    }
}
void Hooks::midiCClegato(int data) {
    for (auto module : OnMidiCClegato) {
        module->onMidiCClegato();
    }
}
void Hooks::midiCCvolume(int data) {
    for (auto module : OnMidiCCvolume) {
        module->onMidiCCvolume();
    }
}
void Hooks::midiInstrument(int instrument) {
    for (auto module : OnMidiInstrument) {
        module->onMidiInstrument();
    }
}

void Hooks::serialMessage(std::string module, std::string setting, int data) {
    for (auto module : OnSerialMessage) {
        module->onSerialMessage();
    }
}





Hooks hook;


