

#include "console.h"


Console::Console() {
    section("console",CORE_PREFIX);
    
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
		Serial.print(var);
		Serial.print(",");
	#endif
}
void Console::addPlotVar(double var) {
	#if PLOTTER == true
		Serial.print(var);
		Serial.print(",");
	#endif
}
void Console::plot() {
	#if PLOTTER == true
		Serial.println("");
		Serial.flush();
	#endif
}




Console console;