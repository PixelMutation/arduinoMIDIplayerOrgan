
#include "modules.h"




void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.MIDIrecieve();
  checkSchedule();
}
