// utility functions which may be useful elsewhere in the code

#ifndef UTILITY_H
#define UTILITY_H

#include "configuration.h"
#include "console.h"
#include <algorithm>




template<typename T,typename T2>
int listFind(T & element,T2 & list) {
    auto pos = std::find(list.begin(),list.end(),element);
    if (pos != list.end()){
        return std::distance(list.begin(),pos);
    } else {
        return -1;
    }
}



int thresholdCheck(int val, int threshold, int deadzone=POSITION_DEADZONE);

void awaitConfirmation();


#endif