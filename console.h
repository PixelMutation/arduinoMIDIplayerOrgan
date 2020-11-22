#ifndef CONSOLE_H
#define CONSOLE_H

#include "global_includes.h"
#include <bitset>
//#include "elapsedMillis.h"

class Console  {
	int consoleIndent = 0;
	

public:
	

	template<typename T>
	void print(T message) {
		delay(SERIAL_DELAY);
		Serial.begin(SERIAL_BAUDRATE);
		if (DEBUG) {
			Serial.print(message);
		}
		delay(SERIAL_DELAY);
		Serial.print("");
		delay(SERIAL_DELAY);
		Serial.flush();
	}
	template<typename T>
	void println(T message) {
		#if DEBUG == true
			Serial.begin(SERIAL_BAUDRATE);
			delay(SERIAL_DELAY);
			Serial.print(INFO_PREFIX);
			delay(SERIAL_DELAY);
			for (int i = 0; i < consoleIndent; i++) {
				delay(SERIAL_DELAY);
				Serial.print(" | ");
                delay(SERIAL_DELAY);
			}	
			
			delay(SERIAL_DELAY);
			Serial.println(message);
			delay(SERIAL_DELAY);
			Serial.print("");
			delay(SERIAL_DELAY);
			Serial.flush();
		#endif
	}
	template<typename T>
	void println(T message, T prefix) {
		#if DEBUG == true
			Serial.begin(SERIAL_BAUDRATE);
			delay(SERIAL_DELAY);
			Serial.print(prefix);
			delay(SERIAL_DELAY);
			for (int i = 0; i < consoleIndent; i++) {
				delay(SERIAL_DELAY);
				Serial.print(" | ");
                delay(SERIAL_DELAY);
			}
	
			delay(SERIAL_DELAY);
			Serial.println(message);
			delay(SERIAL_DELAY);
			Serial.print("");
			delay(SERIAL_DELAY);
			Serial.flush();
		#endif
	}
    template<typename T>
    void section(T name) {
        println(name,PLUGIN_PREFIX);
        consoleIndent+=1;
    }
	template<typename T>
    void section(T name, T prefix) {
        println(name,prefix);
        consoleIndent+=1;
    }
    template<typename T>
    void sectionEnd(T message){
        consoleIndent-=1;
        println(message,PLUGIN_PREFIX);
    }
	template<typename T>
    void sectionEnd(T message, T prefix){
        consoleIndent-=1;
        println(message,prefix);
    }
    void printByte(int8_t u);
	void addPlotVar(int var);
	void addPlotVar(double var);
	void plot();
	
    Console();
};




extern Console console;

#endif