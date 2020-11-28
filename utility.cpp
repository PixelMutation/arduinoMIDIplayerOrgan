#include "utility.h"



void printvector(std::vector<int> vector, bool displayZero) {
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

void printvector(std::deque<double> vector, bool displayZero) {
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



		Serial.print(" ");
	}

}


// pauses everything until the user confirms to proceed to next step
void awaitConfirmation() {
    {
        delay(500);
    } while (digitalRead(CONFIRM_PIN)==LOW); // will include other options for confirmation (e.g. via an app)
}


