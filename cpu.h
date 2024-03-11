#ifndef __CPU__
#define __CPU__
#include "process.h"

class Cpu
{
private:
    unsigned tick;
    unsigned quantum;
    std::chrono::_V2::system_clock::time_point start_time;
    
public:
    unsigned num_ticks;
    Cpu(unsigned _tick, unsigned _quantum);

    bool processing(Process p );
    
    
    ~Cpu();
    


};

#endif