#ifndef CONSOLE_H
#define CONSOLE_H

#include "global_includes.h"

#include "moduleManager.h"

//#include "elapsedMillis.h"

class Console  {
	int consoleIndent = 0;
	
	int plotCycles; // increments with each plot request
	int cycleGap=20;
	bool plotActive = false;
public:
	

	template<typename T>
	void print(T message) {
		#if DEBUG == true
			Serial.print(message);
			Serial.flush();
		#endif
	}
	void print(std::string message);
	template<typename T>
	void printPrefix(T prefix) {
		#if DEBUG == true
			Serial.print(prefix);
			for (int i = 0; i < consoleIndent; i++) {
				Serial.print(" | ");
			}	
		#endif
	}
	template<typename T>
	inline void println(T message) {
		#if DEBUG == true
			printPrefix(INFO_PREFIX);
			print(message);
			Serial.println("");
			Serial.flush();
		#endif
	}
	template<typename T>
	inline void println(T message, T prefix) {
		#if DEBUG == true
			printPrefix(prefix);
			print(message);
			Serial.println("");
			Serial.flush();
		#endif
	}
    template<typename T>
    inline void section(T name) {
		#if DEBUG == true
			println(name,PLUGIN_PREFIX);
			consoleIndent+=1;
		#endif
    }
	template<typename T>
    inline void section(T name, T prefix) {
		#if DEBUG == true
			println(name,prefix);
			consoleIndent+=1;
		#endif
    }
    template<typename T>
    inline void sectionEnd(T message){
		#if DEBUG == true
			consoleIndent-=1;
			println(message,PLUGIN_PREFIX);
		#endif
    }
	template<typename T>
    inline void sectionEnd(T message, T prefix){
		#if DEBUG == true
			consoleIndent-=1;
			println(message,prefix);
		#endif
    }
    void printByte(int8_t u);
	template<typename T>
	void printList(T & list, bool displayZero) {
		for (auto element : list) {

			if (element != 0) {
				print(" ");
				print(element);

			}
			else {
				if (displayZero) {
					print(" ");
					print(element);
				}
				else {
					print("  ");
				}
			}

			print(" ");
		}
	}
	template<typename T>
	inline void addPlotLabel(T label){
		#if PLOTTER == true 
			if (plotActive) {
				Serial.print(label);
				Serial.print(":");
			}
		#endif
	}
	void addPlotVar(int var);
	void addPlotVar(double var);
	void plot();
	
    Console();
};




extern Console * console;

#endif