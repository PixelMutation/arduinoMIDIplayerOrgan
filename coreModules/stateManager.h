
// stateManager.h includes the declarations of all modules in this code
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "../modules.h"


class stateManager {
	string itemsType; // whether the object is the keys or the stops
	int polyphony; // stores the max number of notes that can be held at once
	int numberOfItems; // the number of keys / stops in the object

	vector<int> itemBuffer; // a vector (list) of all keys or stops, with each item storing how many modules have requested that key or stop be active
	vector<int> activatedItems; // a vector (list) of all keys or stops that the system detects (via the sensors) have been activated
	vector<int> systemActivatedItems; // a vector of all the keys/stops activated by the system, including a tally of how long ago active keys were activated (to avoid exceeding any polyphony limits)
	vector<int> userActivatedItems; // a vector of all key/stops the user has activated themselves

	void polyphonyManager(int index, int dir);
	void agentManager();
public:
	stateManager(string type, int size, int polyphony_);
	void requestSystemState(int itemNumber, int state);
	int getState(int itemNumber, string type = "all");
	vector<int> getStatesVector(string type = "all", bool print = false);
	void setSensorState(int itemNumber, int state);

};




#endif



