#include "scheduler.h"


scheduler::scheduler() {
    hook.OnLoop.push_back(this);
}

void scheduler::checkSchedule() {
    unsigned long durationFromStart = millis() - Keys.progStartTime;
    //auto currentTime = chrono::high_resolution_clock::now(); // using std::chrono answer from https://stackoverflow.com/questions/1735307/c-keeping-track-of-how-many-seconds-has-passed-since-start-of-program
    //using the code finding real time difference in double form at https://en.cppreference.com/w/cpp/chrono/c/clock 
    //double durationFromStart = std::chrono::duration<double, std::milli>(currentTime - Keys.progStartTime).count();

    if (! Keys.schedule.empty()) {
        //cout << "\nitem in schedule";

        for (int i = 0; i < (int)Keys.schedule.size(); i++) { // checks each element in the schedule
            //cout << "\nchecking item in schedule";
            //Serial.println("\nchecking item");
            if (Keys.schedule[0][0] <= durationFromStart) {// if the time since the start is equal to or greater than the scheduled time since start, press the scheduled key 
                //cout << "scheduled item activated\nscheduleFirstItem: ";
                //printstd::vector(Keys.schedule[0]);
                Keys.requestActuatorState((int)(Keys.schedule[0][1]), (int)(Keys.schedule[0][2]));
                Keys.schedule.pop_front(); // deletes the element as it has been dealt with
                printKeyStates("system");
            }

        }
    }
}
   
void scheduler::onLoop() {
    checkSchedule();
}

scheduler Scheduler;