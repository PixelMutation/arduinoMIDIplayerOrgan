// utility functions which may be useful elsewhere in the code

#ifndef UTILITY_H
#define UTILITY_H

#include "global_includes.h"



void printVector(std::vector<int> vector, bool displayZero = true);
void printVector(std::deque<double> vector, bool displayZero = true);


void awaitConfirmation();


#endif