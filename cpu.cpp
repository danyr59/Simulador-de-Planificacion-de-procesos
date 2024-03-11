#include "cpu.h"

Cpu::Cpu(unsigned _tick, unsigned _quantum)
{
    this->tick = _tick; 
    this->quantum = _quantum;
    this->start_time = std::chrono::high_resolution_clock::now();
    this->num_ticks = 0;
}

Cpu::~Cpu() 
{
}

bool Cpu::processing(Process p)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(this->tick));
    --p.burst_time;
    ++num_ticks;
    //p.io_burst_time;
    return p.burst_time == 0;
        
}

