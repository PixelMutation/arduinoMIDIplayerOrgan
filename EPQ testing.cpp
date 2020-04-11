// EPQ testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;


void toggleItem(string type,int itemNumber,int state) { // UNFINISHED. This will take commands to move a stop or key and communicate with hardware.
    cout << "set " << type << " item number " << itemNumber << " to " << state << "\n";
}

class PositionManager { // this class handles positions of the keys and stops, with an instance created for the stops and for the keys
    string type; // whether the object is the keys or the stops
    int polyphony; // stores the max number of notes that can be held at once

    vector<int> itemBuffer; // a vector (list) of all keys or stops, with each item storing how many modules have requested that key or stop be active
    vector<int> activatedItems; // a vector (list) of all keys or stops that the system detects (via the sensors) have been activated
    vector<int> systemActivatedItems; // a vector of all the keys/stops activated by the system, including a tally of how long ago active keys were activated (to avoid exceeding any polyphony limits)
    vector<int> userActivatedItems; // a vector of all key/stops the user has activated themselves

    void polyphonyManager(int index,int dir) { // This tracks how long ago (in keypresses) the system pressed keys that are still active, and if polyphony is exceeded deactivates the 'oldest' key
        systemActivatedItems[index] = 0; //resets the tally for the current key to stop the loop adding to it
        if (type == "keys") { // polyphony only applies to keys, so ignore if the object is the stops
            
            for (int i = 0; i < systemActivatedItems.size(); i++ ) {
                if (systemActivatedItems[i] > 0) { // if the note is already active, add to the tally to show how recently it was activated
                    systemActivatedItems[i] += dir;
                }
                if (systemActivatedItems[i] > polyphony) { // if the tally exceeds the polyphony, that note gets deactivated
                    systemActivatedItems[i] = 0;
                    toggleItem(type, i, 0); // deactivates the note
                    itemBuffer[i] = 0; // clears the buffer for that item as it is forced off
                }
            }
            
        }
        if (dir == 1) { // if the system activates the item, it becomes the most recently activated. If the system deactivates the item, its state stays at 0
            systemActivatedItems[index] = 1;
        }
        

    }

public:
    PositionManager(string x, int size, int polyphony) { // initialises the object, taking the type (keys or stops) and size (number of keys/stops) wanted then filling out the vectors with 0s
        type = x;
        itemBuffer.assign(size, 0); // sets the length of the vectors to the number of items, sets all to 0
        activatedItems.assign(size, 0);
        systemActivatedItems.assign(size, 0);
        userActivatedItems.assign(size, 0);
    }

    void requestState(int itemNumber, int state) { // when something wants a key or stop on or off, it calls this
        int index = itemNumber - 1;
        if (state == 0) { // if request is to turn key off
            if (itemBuffer[index] > 0) {
                itemBuffer[index] -= 1;
                if (itemBuffer[index] == 0) { // if it is at 0, then the key or stop needs to be toggled off.
                    toggleItem(type, itemNumber, 0); // toggles key off
                    polyphonyManager(index, -1); // runs polyphony manager, reducing tallies by 1
                }
            }
            
        }
        else { // if request is to turn key on
            itemBuffer[index] += 1;
            if (itemBuffer[index] == 1) { // if it is at 1, then it must have been at 0 so the key or stop needs to be toggled on.
                toggleItem(type, itemNumber, 1); // toggles key on
                polyphonyManager(index, 1); // runs polyphony manager, increasing tallies by 1
            }
            
        }
        
    }

    int getState(int itemNumber, string agent = "all") { // returns if the key is toggled on or off, either overall, by the user, or by the system
        int index = itemNumber - 1;
        if (agent == "user") {
            return userActivatedItems[index]; // 0 if off, 1 if on
        }
        else if (agent == "system"){
            return systemActivatedItems[index]; // if 0, then off. otherwise returns how recently the item was activated
        } else {
            return activatedItems[index]; // 0 if off, 1 if on
        }

    }

    int getBufferValue(int itemNumber) { // returns the value in the buffer
        return itemBuffer[itemNumber - 1];
    }
};




int main() {
    cout << "Hello World!\n";
    PositionManager Keys("keys", 61, 5);
    PositionManager Stops("stops", 11, 11);
    int type, number, state;
    while (true) {
        cout << "Choose type: 1. Keys, 2. Stops\n";
        cin >> type;
        cout << "Choose item number (1-11 for stops, 1-61 for keys)\n";
        cin >> number;
        cout << "Choose state: 0/1\n";
        cin >> state;
        if (type == 1) {
            Keys.requestState(number, state);
            cout << "buffer value " << Keys.getBufferValue(number) << "\n";
            cout << "state " << Keys.getState(number) << "\n";
        }
        else {
            Stops.requestState(number, state);
            cout << "buffer value " << Stops.getBufferValue(number) << "\n";
            cout << "state " << Stops.getState(number) << "\n";
        }
        
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


