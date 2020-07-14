
// stateManager.h includes the declarations of all modules in this code
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "modules.h"


class stateManager {
	const string itemsType; // whether the object is the keys or the stops
	const int polyphony; // stores the max number of notes that can be held at once
	const int numberOfItems; // the number of keys / stops in the object

	vector<int> itemBuffer; // a vector (list) of all keys or stops, with each item storing how many modules have requested that key or stop be active
	vector<int> activatedItems; // a vector (list) of all keys or stops that the system detects (via the sensors) have been activated
	vector<int> systemActivatedItems; // a vector of all the keys/stops activated by the system, including a tally of how long ago active keys were activated (to avoid exceeding any polyphony limits)
	vector<int> userActivatedItems; // a vector of all key/stops the user has activated themselves
	

	void polyphonyManager(int index, int dir);
	void agentManager(int index, string agent = "user");
public:
	deque<vector<unsigned long>> schedule; // a deque containing the schedule for when keys should be pressed if a delay is wanted
	//deque<deque<double>> schedule;
	//std::chrono::time_point<std::chrono::high_resolution_clock> progStartTime; // datatype found at https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
	unsigned long progStartTime;

	stateManager(string type, int size, int polyphony_);
	void requestSystemState(int itemNumber, int state);
	void requestDelayedSystemState(int delay, int itemNumber, int state);
	int getState(int itemNumber, string type = "all");
	vector<int> getStatesVector(string type, bool print = false, bool displayZero = true);
	void setSensorState(int itemNumber, int state);
	int size();

};

extern stateManager Keys;
extern stateManager Stops;



#endif
