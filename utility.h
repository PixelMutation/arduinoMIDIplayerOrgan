// utility functions which may be useful elsewhere in the code

#ifndef UTILITY_H
#define UTILITY_H

#include "modules.h"


void printVector(vector<int> vector, bool displayZero = true);
void printVector(deque<double> vector, bool displayZero = true);
void printKeyStates(string option = "full");
void printStopStates(string option = "full");



#endif