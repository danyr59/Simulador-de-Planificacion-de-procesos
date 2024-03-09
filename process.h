#ifndef __PROCESS__
#define __PROCESS__

class Process
{
private:

public:
    unsigned pid;
    unsigned burst_time;
    unsigned io_burst_time;
    unsigned priority;

    Process(/* args */);
    ~Process();

};

#endif