

#include "modules.h"



void setup() {
  // put your setup code here, to run once:
  
  Serial1.begin(9600);
  Serial.begin(9600);
  
  /*
  cout << "1 2 3 4 5 6 7 8 Hall Reed Pot Hall2\n";
  int delay = 20;
  while (testMux.muxRead(9,false,true) != LOW) {
    cout << "\n";
    for (int i = 0; i < 15; i++) {

      delay = testMux.muxRead(10,true,true);

      cout << testMux.muxRead(i,true,true,delay) << " ";
    }
  }
  */
  
     
  #ifdef SCALES_H
    //cout << "y";    
    if (testMux.muxRead(0,false,true) == HIGH) {
      scaleManager.scale = "harmonic minor";
    } else {
      scaleManager.scale = "major";
    }
    if (testMux.muxRead(1,false,true) == HIGH) {
      scaleManager.chordType = "seventh";
    } else {
      scaleManager.chordType = "triad";
    }
    if (testMux.muxRead(2,false,true) == HIGH) {
      scaleManager.delay = 0;
    } else {
      scaleManager.delay = 20;
    }
    scaleManager.updatePatterns();
  #endif
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
