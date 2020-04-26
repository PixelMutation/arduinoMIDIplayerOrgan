// stateManager.cpp contains the stateManager class definition. This class is used to store data about the positions of keys/stops and handle requests to move them.


#include "stateManager.h"


// constructor: initialises the object, taking the type ("keys" or "stops") and size (number of keys/stops) wanted then filling out the vectors with 0s
stateManager::stateManager(string type, int size, int polyphony_) { // 
    itemsType = type;
    numberOfItems = size;
    itemBuffer.assign(numberOfItems, 0);            // sets the length of the vectors to the number of items, sets all to 0
    activatedItems.assign(numberOfItems, 0);        //
    systemActivatedItems.assign(numberOfItems, 0);  //
    userActivatedItems.assign(numberOfItems, 0);    //
    polyphony = polyphony_;
    progStartTime = std::chrono::high_resolution_clock::now();
    //progStartTime = millis();
}

// request system state function - when something wants a key or stop on or off, it calls this
void stateManager::requestSystemState(int itemNumber, int state) {
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return; }
    int index = itemNumber - 1;
    if (state == 0) {                                   // if request is to turn key off
        if (itemBuffer[index] > 0) {                    // if it isn't already off
            itemBuffer[index] -= 1;
            if (itemBuffer[index] == 0) {               // if it is at 0, then the key or stop needs to be toggled off.
                toggleItem(itemsType, itemNumber, 0);   // toggles key off
                polyphonyManager(index, -1);            // runs polyphony manager, reducing tallies by 1
                agentManager(index, "system");          // runs agent manager
            }
        }

    }
    else {                                        // if request is to turn key on
        itemBuffer[index] += 1;
        if (itemBuffer[index] == 1) {               // if it is at 1, then it must have been at 0 so the key or stop needs to be toggled on.
            toggleItem(itemsType, itemNumber, 1);   // toggles key on
            polyphonyManager(index, 1);             // runs polyphony manager, increasing tallies by 1
            agentManager(index, "system");          // runs agent manager
        }

    }

}


// request system state function - when something wants a key or stop on or off after a specific delay, it calls this
void stateManager::requestDelayedSystemState(int delay, int itemNumber, int state) {
    
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return; }
    int index = itemNumber - 1;

    //unsigned long currentTime = millis();
    auto currentTime = chrono::high_resolution_clock::now(); // using std::chrono answer from https://stackoverflow.com/questions/1735307/c-keeping-track-of-how-many-seconds-has-passed-since-start-of-program
    //using the code finding real time difference in double form at https://en.cppreference.com/w/cpp/chrono/c/clock 
    //and using Jonathan Wakely's answer to convert int to millisecond duration data type https://stackoverflow.com/questions/31401560/c11-chrono-how-to-cast-unsigned-int-to-a-time-pointsystem-clock
    double delayDurationFromStart = std::chrono::duration<double, std::milli>(currentTime - progStartTime + chrono::milliseconds(delay)) .count();
    //unsigned long durationFromStart = currentTime - progStartTime;

    schedule.push_back({delayDurationFromStart, (double)itemNumber, (double)state });
    //schedule.push_back([delayDurationFromStart, (unsigned long)itemNumber, (unsigned long(state)])
    
}

//set sensor state function - called when sensors detect a key has been pressed or released
void stateManager::setSensorState(int itemNumber, int state) {
    int index = itemNumber - 1;
    //cout << "setting sensor state\n";
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return; }
    activatedItems[index] = state;
    agentManager(index);
    if (itemsType == "stops") {
        MIDI.stops_to_MIDI();
    }
}

// polyphony manager - tracks how long ago (in keypresses) the system pressed keys that are still active, and if polyphony is exceeded deactivates the 'oldest' key
void stateManager::polyphonyManager(int index, int dir) {

    systemActivatedItems[index] = 0; //resets the tally for the current key to stop the loop adding to it
    agentManager(index, "system");
    if (itemsType == "keys") { // polyphony only applies to keys, so ignore if the object is the stops

        for (int i = 0; i < (int)numberOfItems; i++) {
            if (systemActivatedItems[i] > 0) { // if the note is already active, change to the tally to show how recently it was activated
                systemActivatedItems[i] += dir;
                string direction;
                if (dir > 0) {direction = "increased"; }
                else {direction = "decreased"; }
                cout << direction << " item " << i + 1<< " age by 1\n";
                agentManager(i, "system");
            }
            if (systemActivatedItems[i] > polyphony) { // if the tally exceeds the polyphony, that note gets deactivated
                cout << "Polyphony exceeded, deactivated item " << i + 1 << "\n";
                systemActivatedItems[i] = 0;
                toggleItem(itemsType, i, 0);    // deactivates the note
                itemBuffer[i] = 0;              // clears the buffer for that item as it is forced off
                agentManager(i, "system");
            }
        }

    }
    if (dir == 1) { // if the system activates the item, it becomes the most recently activated. If the system deactivates the item, its state stays at 0
        systemActivatedItems[index] = 1;
        //cout << "item " << index + 1 << " age set to 1\n";
        agentManager(index, "system");
    }


}

// agent manager function - tracks whether a key has been physically pressed, and if this was done by the user
void stateManager::agentManager(int index, string agent) { 
    if (agent == "system" and systemActivatedItems[index] == 0) {
        if (userActivatedItems[index] == 0) {
            activatedItems[index] = 0;
        }
    }
    else {
        if (activatedItems[index] == 1 and systemActivatedItems[index] == 0) {
            userActivatedItems[index] = 1;
        }
        if (activatedItems[index] == 0 or systemActivatedItems[index] > 0) {
            userActivatedItems[index] = 0;
        }
        if (userActivatedItems[index] == 0 and systemActivatedItems[index] == 0) {
            activatedItems[index] = 0;
        }
        if (userActivatedItems[index] == 1 or systemActivatedItems[index] > 0) {
            activatedItems[index] = 1;
        }
    }
}
    
    
// retrieves state of an item (key/stop) of state type: "system" (the 'age' of an active item in keypresses since the system pressed it), "buffer" (how many processes currently want that item activated), "user" (if the user pressed it) or "all" (overall state of item)
int stateManager::getState(int itemNumber, string type) { // returns if the key is toggled on or off, either overall, by the user, or by the system
    if (itemNumber > numberOfItems or itemNumber < 1) { cout << "FAILED: item no. out of range!\n"; return NULL; }
    int index = itemNumber - 1;
    if (type == "user") {
        return userActivatedItems[index];   // 0 if off, 1 if on
    }
    else if (type == "system") {
        return systemActivatedItems[index]; // 0 if off, otherwise returns how recently the item was activated
    }
    else if (type == "buffer") {
        return itemBuffer[index];
    }
    else {
        return activatedItems[index];       // 0 if off, 1 if on
    }

}

// retrieves vector of states for keys/stops of state type: "system" (if the system pressed it), "buffer" (the 'age' of an active item in keypresses since activation), "user" (if the user pressed it) or "all" (overall state of item)
vector<int> stateManager::getStatesVector(string type, bool print, bool displayZero) {
    
    if (type == "user") {
        if (print) { printVector(userActivatedItems, displayZero); }
        return userActivatedItems;
    }
    else if (type == "system") {
        if (print) { printVector(systemActivatedItems, displayZero); }
        return systemActivatedItems;
    }
    else if (type == "buffer") {
        if (print) { printVector(itemBuffer, displayZero); }
        return itemBuffer;;
    }
    else {
        if (print) { printVector(activatedItems, displayZero); }
        return activatedItems;
    }
}
   
//returns number of items (keys/stops) in the class
int stateManager::size() {
    return numberOfItems;
}

// create instance of class for keys and stops
int polyphony = 3;

stateManager Keys("keys", 61, polyphony);
stateManager Stops("stops", 11, 11);







