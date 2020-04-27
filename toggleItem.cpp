// toggleItem.cpp contains the definition of the function used to communicate with hardware to physically move keys or stops

#include "toggleItem.h"

void toggleItem(string type, int itemNumber, int state) { // UNFINISHED. This will take commands to move a stop or key and communicate with hardware.
    int index = itemNumber - 1;
    cout << "set " << type << " item number " << itemNumber << " to " << state << "\n";
}
