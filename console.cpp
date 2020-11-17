

#include "console.h"


Console::Console() {
    section("console",CORE_PREFIX);
    
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

Console console;