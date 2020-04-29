#include "scheduler.h"




void checkSchedule() {
    unsigned long durationFromStart = millis() - Keys.progStartTime;
    //auto currentTime = chrono::high_resolution_clock::now(); // using std::chrono answer from https://stackoverflow.com/questions/1735307/c-keeping-track-of-how-many-seconds-has-passed-since-start-of-program
    //using the code finding real time difference in double form at https://en.cppreference.com/w/cpp/chrono/c/clock 
    //double durationFromStart = std::chrono::duration<double, std::milli>(currentTime - Keys.progStartTime).count();

    if (! Keys.schedule.empty()) {
        //cout << "\nitem in schedule";
        for (int i = 0; i < (int)Keys.schedule.size(); i++) { // checks each element in the schedule
            //cout << "\nchecking item in schedule";
            if (Keys.schedule[0][0] <= durationFromStart) {// if the time since the start is equal to or greater than the scheduled time since start, press the scheduled key 
                //cout << "scheduled item activated\nscheduleFirstItem: ";
                //printVector(Keys.schedule[0]);
                cout << "\n";
                Keys.requestSystemState((int)(Keys.schedule[0][1]), (int)(Keys.schedule[0][2]));
                Keys.schedule.pop_front(); // deletes the element as it has been dealt with
                cout << "\nkeys pressed by user  : ";    Keys.getStatesVector("user", true, false);
                cout << "\nkeys pressed overall  : ";    Keys.getStatesVector("all", true, false);
                cout << "\nkeys pressed by system: ";    Keys.getStatesVector("system", true, false);
                cout << "\n";
            }

        }
    }
}
   
