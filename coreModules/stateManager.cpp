// stateManager.cpp contains the stateManager class definition. This class is used to store data about the positions of keys/stops and handle requests to move them.


#include "stateManager.h"


// contructor 
stateManager::stateManager(string type, int size, int polyphony_) { // initialises the object, taking the type (keys or stops) and size (number of keys/stops) wanted then filling out the vectors with 0s
    itemsType = type;
    numberOfItems = size;
    itemBuffer.assign(numberOfItems, 0); // sets the length of the vectors to the number of items, sets all to 0
    activatedItems.assign(numberOfItems, 0);
    systemActivatedItems.assign(numberOfItems, 0);
    userActivatedItems.assign(numberOfItems, 0);
    polyphony = polyphony_;
}

// request system state function // when something wants a key or stop on or off, it calls this
void stateManager::requestSystemState(int itemNumber, int state) { 
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return; }
    int index = itemNumber - 1;
    if (state == 0) { // if request is to turn key off
        if (itemBuffer[index] > 0) {
            itemBuffer[index] -= 1;
            if (itemBuffer[index] == 0) { // if it is at 0, then the key or stop needs to be toggled off.
                toggleItem(itemsType, itemNumber, 0); // toggles key off
                polyphonyManager(index, -1); // runs polyphony manager, reducing tallies by 1
            }
        }

    }
    else { // if request is to turn key on
        itemBuffer[index] += 1;
        if (itemBuffer[index] == 1) { // if it is at 1, then it must have been at 0 so the key or stop needs to be toggled on.
            toggleItem(itemsType, itemNumber, 1); // toggles key on
            polyphonyManager(index, 1); // runs polyphony manager, increasing tallies by 1
        }

    }

}

//set sensor state function
void stateManager::setSensorState(int itemNumber, int state) {
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return; }
    activatedItems[itemNumber - 1] = state;
    agentManager();
}

// polyphony manager function
void stateManager::polyphonyManager(int index, int dir) { // This tracks how long ago (in keypresses) the system pressed keys that are still active, and if polyphony is exceeded deactivates the 'oldest' key
    systemActivatedItems[index] = 0; //resets the tally for the current key to stop the loop adding to it
    if (itemsType == "keys") { // polyphony only applies to keys, so ignore if the object is the stops

        for (int i = 0; i < (int)numberOfItems; i++) {
            if (systemActivatedItems[i] > 0) { // if the note is already active, add to the tally to show how recently it was activated
                systemActivatedItems[i] += dir;
                string direction;
                if (dir > 0) {direction = "increased"; }
                else {direction = "decreased"; }
                cout << direction << " item " << i + 1<< " age by 1\n";
            }
            if (systemActivatedItems[i] > polyphony) { // if the tally exceeds the polyphony, that note gets deactivated
                cout << "Polyphony exceeded, deactivated item " << i + 1 << "\n";
                systemActivatedItems[i] = 0;
                toggleItem(itemsType, i, 0); // deactivates the note
                itemBuffer[i] = 0; // clears the buffer for that item as it is forced off
            }
        }

    }
    if (dir == 1) { // if the system activates the item, it becomes the most recently activated. If the system deactivates the item, its state stays at 0
        systemActivatedItems[index] = 1;
        cout << "item " << index + 1 << " age set to 1\n";
    }


}

// agent manager function
void stateManager::agentManager() { // This tracks whether a key has been physically pressed, and if this was done by the user
    for (int i = 0; i < numberOfItems; i++) {
        if (activatedItems[i] == 1 and systemActivatedItems[i] == 0) {
            userActivatedItems[i] = 1;
        }
        else if (activatedItems[i] == 0 or systemActivatedItems[i] != 0) {
            userActivatedItems[i] = 0;
        }
    }
}
    
// functions to retrieve states
int stateManager::getState(int itemNumber, string type) { // returns if the key is toggled on or off, either overall, by the user, or by the system
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return NULL; }
    int index = itemNumber - 1;
    if (type == "user") {
        return userActivatedItems[index]; // 0 if off, 1 if on
    }
    else if (type == "system") {
        return systemActivatedItems[index]; // if 0, then off. otherwise returns how recently the item was activated
    }
    else if (type == "buffer") {
        return itemBuffer[index];
    }
    else {
        return activatedItems[index]; // 0 if off, 1 if on
    }

}


vector<int> stateManager::getStatesVector(string type, bool print) {
    
    if (type == "user") {
        if (print) { printVector(userActivatedItems); }
        return userActivatedItems;
    }
    else if (type == "system") {
        if (print) { printVector(systemActivatedItems); }
        return systemActivatedItems;
    }
    else if (type == "buffer") {
        if (print) { printVector(itemBuffer); }
        return itemBuffer;;
    }
    else {
        if (print) { printVector(activatedItems); }
        return activatedItems;
    }
}
    

    




