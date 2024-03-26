#ifndef __CPU__
#define __CPU__
#include <memory>
#include "process.h"
using sProcess = std::shared_ptr<Process>;


class Cpu
{
private:
    unsigned tick;
    unsigned quantum;
    std::chrono::_V2::system_clock::time_point start_time;
    bool free;
    sProcess current;
    
public:
    unsigned num_ticks;

    Cpu(unsigned _tick, unsigned _quantum);
    ~Cpu();

    //funciones
    STATES processing();
    bool is_free();
    sProcess interrupt();
    bool assign_process(sProcess p);
    unsigned getQuantum() const{
        return this->quantum;
    }
    sProcess getCurrentProcess() const {
        return this->current;
    }
    


};

#endif