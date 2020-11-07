
// stateManager.h includes the declarations of all modules in this code
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "global_includes.h"
#include "utility.h"
#include "midiManager.h"
#include "toggleItem.h"


class stateManager {
	std::string itemsType; // whether the object is the keys or the stops
	int polyphony; // stores the max number of notes that can be held at once
	int numberOfItems; // the number of keys / stops in the object
	int set; // the manual of keys or division of stops
	std::vector<int> itemBuffer; // a vector (list) of all keys or stops, with each item storing how many modules have requested that key or stop be active
	std::vector<int> activatedItems; // a vector (list) of all keys or stops that the system detects (via the sensors) have been activated
	std::vector<int> systemActivatedItems; // a vector of all the keys/stops activated by the system, including a tally of how long ago active keys were activated (to avoid exceeding any polyphony limits)
	std::vector<int> userActivatedItems; // a vector of all key/stops the user has activated themselves
	std::vector<int> velocity; // the velocity of the keypress

	void polyphonyManager(int index, int dir);
	void agentManager(int index, std::string agent = "user");
public:
	std::deque<std::vector<unsigned long>> schedule; // a deque containing the schedule for when keys should be pressed if a delay is wanted
	//deque<deque<double>> schedule;
	//std::chrono::time_point<std::chrono::high_resolution_clock> progStartTime; // datatype found at https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
	unsigned long progStartTime;

	stateManager(std::string type, int size, int polyphony_, int _set);
	void requestActuatorState(int itemNumber, int state);
	void requestActuatorState(int itemNumber, int state, int delay);
	int getState(int itemNumber, std::string type = "all");
	std::vector<int> getStatesVector(std::string type, bool print = false, bool displayZero = true);
	void setSensorState(int itemNumber, int state);
	int size();

};

void printKeyStates(std::string option = "full");
void printStopStates(std::string option = "full");

extern stateManager Keys;
extern stateManager Stops;



#endif
