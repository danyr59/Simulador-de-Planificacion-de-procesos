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
    unsigned block_point;
    STATES status;

    Process(unsigned _pid, unsigned _arrival_time);
    Process(unsigned _pid, unsigned _arrival_time, unsigned _burst_time);
    ~Process();

    void io();
    void generate_block_point();

};

#endif