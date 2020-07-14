#include "utility.h"


void printVector(vector<int> vector, bool displayZero) {
	for (int element : vector) {

		if (element != 0) {
			Serial.print(" ");
			Serial.print(element);

		}
		else {
			if (displayZero) {
				Serial.print(" ");
				Serial.print(element);
			}
			else {
				Serial.print("  ");
			}
		}
		


		Serial.print(" ");
	}

}

void printVector(deque<double> vector, bool displayZero) {
	for (double element : vector) {

		if (element != 0) {
			Serial.print(" ");
			Serial.print(element);
		}
		else {
			if (displayZero) {
				Serial.print(" ");
				Serial.print(element);
			}
			else {
				Serial.print("  ");
			}
		}



		Serial.print(" ")
	}

}

void printKeyStates(string option) {
	if (option == "full") {
		
		Serial.print("\nkeys pressed by user  : ");    Keys.getStatesVector("user", true, false);
		Serial.print("\nkeys pressed overall  : ");    Keys.getStatesVector("all", true, false);
		Serial.print("\nkeys pressed by system: ");    Keys.getStatesVector("system", true, false);
	} else if (option == "buffer") {
		Serial.print("\nkey requests  buffer  : ");    Keys.getStatesVector("buffer", true, false);
	} else if (option =="overall") {
		Serial.print("\nkeys pressed overall  : ");    Keys.getStatesVector("all", true, false);
	} else if (option == "user") {
		Serial.print("\nkeys pressed by user  : ");    Keys.getStatesVector("user", true, false);
	} else if (option == "system") {
		Serial.print("\nkeys pressed by system: ");    Keys.getStatesVector("system", true, false);
	} else if (option == "header") {
		Serial.print("\n                        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 ");
	} 
}

void printStopStates(string option) {
	if (option == "full") {
		Serial.print("\n stops user state   : "); Stops.getStatesVector("user", true, true);
		Serial.print("\n stops overall state: "); Stops.getStatesVector("all", true, true);
		Serial.print("\n stops system state : "); Stops.getStatesVector("system", true, true);
	} else if (option =="overall") {
		Serial.print("\n stops overall state: "); Stops.getStatesVector("all", true, true);
	} else if (option == "user") {
		Serial.print("\n stops user state   : "); Stops.getStatesVector("user", true, true);
	} else if (option == "system") {
		Serial.print("\n stops system state : "); Stops.getStatesVector("system", true, true);
	} else if (option == "header") {
		Serial.print("\n                       01 02 03 04 05 06 07 08 09 10 11");
	}
}




