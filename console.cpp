

#include "console.h"
#include "multiplexer.h"

Console::Console() {
    section("console",CORE_PREFIX);
	
	Serial.begin(SERIAL_BAUDRATE);
	//cycleGap = analogRead(22)/10;
	cycleGap = (((int)exp(analogRead(22)/100)));
	//cycleGap = 40;
	//hooks.OnLoop.add(this);
    sectionEnd("console initialised",CORE_PREFIX);
}

void Console::printByte(int8_t u) 
{ 
	
	std::bitset<8> byte(u);
	std::string byteStr = byte.to_string();
	char a[9] = {0};
	std::copy(byteStr.begin(), byteStr.end(), a);
	println(a); 
}
void Console::addPlotVar(int var) {
	#if PLOTTER == true 
		if (plotActive) {
			Serial.print(var);
			Serial.print(",");
		}
	#endif
}
void Console::addPlotVar(double var) {
	#if PLOTTER == true
		if (plotActive) {
			Serial.print(var);
			Serial.print(",");
		}
		
	#endif
}
void Console::plot() {
	
	#if PLOTTER == true
	
		plotCycles+=1;
		if (plotCycles > cycleGap) {
			plotCycles = 0;
			plotActive = true;
			
			Serial.println("");
			Serial.flush();
			
		} else {
			plotActive = false;
		}
		
		cycleGap = (((int)exp(analogRead(22)/100)));
	#endif
	
}




Console console;