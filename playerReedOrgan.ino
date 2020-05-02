

#include "modules.h"



void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);

  //cout << testMux.muxRead(7,true,false) << "\n";
  //cout << testMux.muxRead(8,false,false) << "\n";
  //cout << testMux.muxRead(9,false,true) << "\n";
  cout << "1 2 3 4 5 6 7 8 Hall Reed Pot Hall2\n";
  int delay = 20;
  while (testMux.muxRead(9,false,true) != LOW) {
    //cout << 150 << " " << testMux.muxRead(8,true,false) <<  " " << 525 <<"\n";
    
    //cout << testMux.muxRead(7,true,false) << "\n";
    cout << "\n";
    for (int i = 0; i < 15; i++) {
      if (i == 8 || i == 11) {
        delay = testMux.muxRead(10,true,true)*10000;
      } else {
        delay = 200;
      }
      cout << testMux.muxRead(i,true,true,delay) << " ";
    }
    //cout << testMux.muxRead(7,true,true) << " " << testMux.muxRead(8,true,true) <<  " " << testMux.muxRead(9,true,true) <<  " " << testMux.muxRead(10,true,true) << testMux.muxRead(11,true,true)  << "\n";
  }
     
  
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
