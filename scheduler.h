#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "global_includes.h"
#include "stateManager.h"
#include "multiplexer.h"
#include "utility.h"


class scheduler : public moduleTemplate{
    void checkSchedule();

public:
    scheduler();
    void onLoop();
};


// using deque instead of vector as it can be modified from both ends http://www.cplusplus.com/reference/deque/deque/

extern scheduler Scheduler;

#endif
