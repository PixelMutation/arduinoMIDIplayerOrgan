

#include "modules.h"
#include "Arduino.h"

#if PLOT_SPEED == true
  elapsedMicros cycleLength;
  int cycle;
  double cycleDuration;
  double cycleFrequency;
#endif
//#include "Plotter.h"

//int a, b,c;

//Plotter p;
//int led = 13;




void setup() { 

  console.println("reached setup");

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);

  
  
  // Calls all module functions set to run on startup
  hooks.OnStart.call();   
}

void loop() {
  
  //console.addPlotVar((double)cycleLength);
  

  #if PLOT_SPEED == true
    cycle +=1;
    if (cycle >= 20) {
      cycleDuration = (double)cycleLength/20;
      cycleFrequency = (double)1/(cycleDuration*0.0001);
      #if PLOTTER == false
        Serial.print("cycleFreq(100Hz):"); Serial.println(cycleFrequency);
        Serial.flush();
      #endif
        
      cycleLength=0;
      cycle=0;
    }
    /*
    if (cycleDuration>1000) {
      Serial.print("cycleLength(100µs):"); Serial.print(cycleDuration/100);Serial.print(",");

    } else {
      Serial.print("cycleLength(µs):"); Serial.print(cycleDuration);Serial.print(",");

    }
    */
    #if PLOTTER == true

      Serial.print("cycleFreq(100Hz):"); Serial.print(cycleFrequency);Serial.print(",");
    #endif
  #endif
  
  digitalWrite(13,HIGH);
  //stateManager.keys.requestActuatorState(0,0,0);
  //KeyActuators.setState(0,0,0);
  //delay(analogRead(22));
  digitalWrite(13,LOW);
  //stateManager.keys.requestActuatorState(0,0,1);
  //KeyActuators.setState(0,0,1);
  
  double Delay=log(analogRead(21))*100;
  //console.addPlotVar(Delay);
  
  if (Delay>0) {
    delayMicroseconds(Delay);
  }
  
  
  // Calls all module functions set to run each loop
  hooks.OnLoop.call();
  
  console.plot();

  
}

