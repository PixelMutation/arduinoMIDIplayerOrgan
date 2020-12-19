#include "scheduler.h"

#include "console.h"
//#include "I2Cactuators.h"

scheduleManager::scheduleManager() {
    console->section("scheduleManager",CORE_PREFIX);
    hooks->OnLoop->add(this);
    /*
    while (true) {
        //digitalWrite(13,HIGH);
        KeyActuators.setState(0,0,0);
        delay(analogRead(22));
        //digitalWrite(13,LOW);
        KeyActuators.setState(0,0,1);
        delay(analogRead(21));
    }
    */
    
    
    console->sectionEnd("scheduleManager initialised",CORE_PREFIX);
}




// checks the schedule and calls scheduled event methods 
void scheduleManager::checkSchedule() {
    if (! scheduleMethod.empty()){ 
        std::vector<int> events; // since the schedule is not in order, this stores which events have passed
        for (int i=0; i < (int)scheduleMethod.size(); i++) {            // for each event in the schedule
            if (scheduleTime[i] <= currentTime) {                       // if current time is equal to or past the event time
                scheduleMethod[i]->onSchedule(scheduleParameters[i]);   // call the event's method//
                events.push_back(i);
            } else {
                break; // if current time is less than the scheduled time, there is no point checking the rest
            }
        }
        for (int i=0; i < (int)events.size(); i ++) {   // erases all events that have been passed
            scheduleMethod     .erase(scheduleMethod    .begin() + events[i]);
            scheduleTime       .erase(scheduleTime      .begin() + events[i]);
            scheduleParameters .erase(scheduleParameters.begin() + events[i]);
        }
    }
}

unsigned long scheduleManager::CurrentTime(){
    return currentTime;
}
// adds the event to the back of the schedule
void scheduleManager::addToSchedule(schedule *method, unsigned long delay, std::vector<int> params) {
    scheduleMethod.push_back(method);       // 
    scheduleTime.push_back(delay+currentTime);           //
    scheduleParameters.push_back(params);   //
}

void scheduleManager::onLoop() {
    checkSchedule();
}

scheduleManager * scheduler = nullptr;