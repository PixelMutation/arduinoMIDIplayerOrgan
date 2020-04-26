#include "utility.h"

void printVector(vector<int> vector, bool displayZero) {
	for (int element : vector) {

		if (element != 0) {
			//cout << " " << element;
		}
		else {
			if (displayZero) {
				//cout << " " << element;
			}
			else {
				//cout << "  ";
			}
		}
		


		//cout << " ";
	}

}

void printVector(deque<double> vector, bool displayZero) {
	for (double element : vector) {

		if (element != 0) {
			//cout << " " << element;
		}
		else {
			if (displayZero) {
				//cout << " " << element;
			}
			else {
				//cout << "  ";
			}
		}



		//cout << " ";
	}

}

