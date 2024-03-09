#ifndef __PROCESS__
#define __PROCESS__

class Process
{
private:
    unsigned pid;
    unsigned burst_time;
public:
    Process(/* args */);
    ~Process();
};

#endif