#ifndef __PROCESS__
#define __PROCESS__
#include "utils.h"

class Process
{
private:

public:
    unsigned pid;
    unsigned burst_time;
    unsigned io_burst_time;
    unsigned priority;
    unsigned arrival_time;

    Process(unsigned _pid, unsigned _arrival_time);
    ~Process();

};

#endif