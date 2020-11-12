#include "scheduler.h"


scheduleManager::scheduleManager() {
    progStartTime == millis();
    hook.OnLoop.push_back(this);
}

// checks the schedule and calls scheduled event methods 
void scheduleManager::checkSchedule() {
    unsigned long currentTime = millis() - progStartTime; // calculates current time
    if (! scheduleMethod.empty()){ 
        vector<int> events; // since the schedule is not in order, this stores which events have passed
        for (int i=0; i < (int)scheduleMethod.size(); i++) {            // for each event in the schedule
            if (scheduleTime[i] <= currentTime) {                       // if current time is equal to or past the event time
                scheduleMethod[i]->onSchedule(scheduleParameters[i]);   // call the event's method//
                events.push_back(i);
            } else {
                break; // if current time is less than the scheduled time, there is no point checking the rest
            }
        }
        for (int i=0; i < (int)events.size(); i ++) {   // erases all events that have been passed
            scheduleMethod    .erase(events[i]);
            scheduleTime      .erase(events[i]);
            scheduleParameters.erase(events[i]);
        }
    }
}

unsigned long scheduleManager::fetchStartTime() {
    return progStartTime;
}
// adds the event to the back of the schedule
void scheduleManager::addToSchedule(schedule *method, unsigned long time, std::vector<int> params) {
    scheduleMethod.push_back(method);       // 
    scheduleTime.push_back(time);           //
    scheduleParameters.push_back(params);   //
}

void scheduleManager::onLoop() {
    checkSchedule();
}

scheduleManager scheduler;