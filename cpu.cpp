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

STATES Cpu::processing()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(this->tick));
    QThread::msleep(this->tick);
    //procesamiento nulo
    ++num_ticks;
    if(free || current == nullptr)
        return STATES::EXECUTE;

    --current->burst_time;

    //p.io_burst_time;
    if(current->burst_time == 0)
    {
        free = true;
        current->status = STATES::DONE;
        current = nullptr;
        return STATES::DONE;
    }

    ///ocurre evento bloqueante
    if(current->burst_time == current->block_point)
    {
        current->status = STATES::BLOCKED;
        return STATES::BLOCKED;
    }
    

    return STATES::EXECUTE;
}

bool Cpu::is_free()
{
    return free;
}

sProcess Cpu::interrupt()
{
    free = true;
    if(current->status ==  STATES::EXECUTE)
        current->status = STATES::READY;
    return current;
}

bool Cpu::assign_process(sProcess p)
{
    if(!free)
        return false;

    current = p;
    current->status = STATES::EXECUTE;
    free = false;

    return true;
}