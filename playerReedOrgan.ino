

#include "modules.h"



void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Serial.begin(9600);
  


  #ifdef TEST_INTERFACE_H
    testInterface();
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.MIDIrecieve();
  checkSchedule();
}
