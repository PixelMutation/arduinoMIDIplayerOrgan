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
// returns whether a value is above or below a threshold, taking into account a deadzone
int thresholdCheck(int val, int threshold, int deadzone) {
    if (val < threshold-deadzone/2) {
        return -1;
    } else if ((val > threshold+deadzone/2)) {
        return 1;
    } else {
        return 0;
    }
}

// pauses everything until the user confirms to proceed to next step
void awaitConfirmation() {
    {
        delay(500);
    } while (digitalRead(CONFIRM_PIN)==LOW); // will include other options for confirmation (e.g. via an app)
}


