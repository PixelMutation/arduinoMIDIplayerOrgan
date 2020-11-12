#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "global_includes.h"

// any module which needs to schedule events inherits this
class schedule {
public:
    virtual void onSchedule(std::vector<int> params); // this function is run when the schedule is called
};

// this module checks the schedule each loop
class scheduleManager : public moduleTemplate{
    unsigned long progStartTime;
    void checkSchedule();
    std::deque<schedule*> scheduleMethod;           // stores pointers to the methods for each scheduled event
    std::deque<unsigned long> scheduleTime;         // stores the time for each scheduled event
    std::deque<std::vector<int>> scheduleParameters; // stores the parameters given to the event's method
public:
    scheduleManager();
    unsigned long fetchStartTime();
    void addToSchedule(schedule *method, unsigned long time, std::vector<int> params); // called to add to the schedule
    void onLoop();
};


// using deque instead of vector as it can be modified from both ends http://www.cplusplus.com/reference/deque/deque/

extern scheduleManager scheduler;

#endif
