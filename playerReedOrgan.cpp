

#include "modules.h"
#include "Arduino.h"
#include "Plotter.h"

int a, b,c;

Plotter p;
int led = 13;

void setup() {
  



  // put your setup code here, to run once:

  p.Begin();
  p.AddTimeGraph("Hall effect sensors",1000, "LB", a, "hall", b, "UB", c);

  Serial1.begin(9600);
  Serial.begin(9600);
  

  pinMode(led, OUTPUT);
  //Serial.println("1 2 3 4 5 6 7 8 Hall Reed Pot Hall2\n");
  

  while (/*testMux.muxRead(9,false,true) != LOW*/true) {

    digitalWrite(led, HIGH);
    //Serial.print("\n");

    a= 150;
    b= testMux.muxRead(8,true,true);
    c= 210;

    p.Plot();

    delayMicroseconds(1000); 
  }

  // Calls all module functions set to run on startup
  for (auto module : moduleCall.OnStart) {
    module->onStart();
  }       
}

void loop() {
  
  // put your main code here, to run repeatedly:
  checkSchedule();
  Controls.checkPins();

  // Calls all module functions set to run each loop
  for (auto module : moduleCall.OnLoop) {
    module->onLoop();
  }

  
}

