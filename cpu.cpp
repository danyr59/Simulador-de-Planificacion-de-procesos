#include "cpu.h"

Cpu::Cpu(unsigned _tick, unsigned _quantum)
{
    this->tick = _tick; 
    this->quantum = _quantum;
    this->start_time = std::chrono::high_resolution_clock::now();
    this->num_ticks = 0;
    this->free = true;
    this->current = nullptr;
}

Cpu::~Cpu() 
{
}

bool Cpu::processing()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(this->tick));
    //procesamiento nulo
    if(free || current == nullptr)
        return false;

    --current->burst_time;
    ++num_ticks;
    //p.io_burst_time;
    if(current->burst_time == 0)
    {
        free = true;
        current->status = STATES::DONE;
        current = nullptr;
        return true;
    }

    return false;
}

bool Cpu::is_free()
{
    return free;
}

sProcess Cpu::interrupt()
{
    free = true;
    return current;
}

bool Cpu::assign_process(sProcess p)
{
    if(!free)
        return false;

    current = p;
    free = false;

    return true;
}