

#include "modules.h"
#include "Arduino.h"
//#include "Plotter.h"

//int a, b,c;

//Plotter p;
//int led = 13;




void setup() { 

  console.println("reached setup");

  pinMode(13,OUTPUT);

  
  
  
  // Calls all module functions set to run on startup
  hook.start();   
}

void loop() {
  
  digitalWrite(13,HIGH);
  KeyActuators.setState(0,0,0);
  delay(analogRead(22));
  digitalWrite(13,LOW);
  KeyActuators.setState(0,0,1);
  delay(analogRead(21));
  // Calls all module functions set to run each loop
  hook.loop();

  
}

