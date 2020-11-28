// utility functions which may be useful elsewhere in the code

#ifndef UTILITY_H
#define UTILITY_H

#include "global_includes.h"



void printVector(std::vector<int   > vector, bool displayZero = true);
void printVector(std::deque <double> vector, bool displayZero = true);

int thresholdCheck(int val, int threshold, int deadzone=POSITION_DEADZONE);

void awaitConfirmation();


#endif