

#include "modules.h"



void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  cout << "setup complete\n";


  #ifdef TEST_INTERFACE_H
    testInterface();
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  checkSchedule();
  Controls.checkPins();
}

void serialEvent() {
  MIDI.MIDIrecieve();
}