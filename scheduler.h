#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "global_includes.h"
#include <elapsedMillis.h>
#include "moduleManager.h"


// any module which needs to schedule events inherits this
class schedule {
public:
    virtual void onSchedule(std::vector<int> params); // this function is run when the schedule is called
};

// this module checks the schedule each loop
class scheduleManager : public moduleTemplate{
    void checkSchedule();
    std::deque<schedule*> scheduleMethod;           // stores pointers to the methods for each scheduled event
    std::deque<unsigned long> scheduleTime;         // stores the time for each scheduled event
    std::deque<std::vector<int>> scheduleParameters; // stores the parameters given to the event's method
    elapsedMillis currentTime; // a constantly updated variable storing the current time https://www.pjrc.com/teensy/td_timing_elaspedMillis.html

public:
    scheduleManager();
    void addToSchedule(schedule *method, unsigned long delay, std::vector<int> params); // called to add to the schedule
    unsigned long CurrentTime();
    void onLoop();
};


extern scheduleManager * scheduler;

#endif
