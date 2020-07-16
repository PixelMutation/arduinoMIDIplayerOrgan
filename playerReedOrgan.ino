

#include "modules.h"



int led = 13;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(A8, INPUT); 
  

  
  adc->adc0->setAveraging(16);
  adc->adc0->setResolution(16);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

  adc->adc0->startContinuous(A8);

  adc->adc1->setAveraging(16);
  adc->adc1->setResolution(16);
  adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
  adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);


  Serial1.begin(9600);
  Serial.begin(9600);
  

  pinMode(led, OUTPUT);
  Serial.println("1 2 3 4 5 6 7 8 Hall Reed Pot Hall2\n");
  int Delay = 0;
  while (/*testMux.muxRead(9,false,true) != LOW*/true) {
    digitalWrite(led, HIGH);
    Serial.print("\n");
    /*
    for (int i = 0; i < 15; i++) {

      //Delay = testMux.muxRead(10,true,true);

      Serial.print(testMux.muxRead(i,true,true,Delay));
      Serial.print(" ");
      
    }
    */
    Serial.print(testMux.muxRead(8,true,true,Delay));
    Serial.print(" ");
    Serial.print(testMux.muxRead(11,true,true,Delay));
    Serial.print(" ");
    Serial.print(255);
    Serial.print(" ");
    Serial.print(0);
    digitalWrite(led, LOW);

  }
  
  /*
  int x =0;
  while (x < 10) {
    x++;
    Serial.println("\n TEST");
    delay(1000);
    if (testMux.muxRead(0,false,true) == HIGH) {
      Serial.println("\n x");
    }
    Serial.println("\n y");
  }
  */
  
  /*
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
  */

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
