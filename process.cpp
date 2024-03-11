#include "process.h"

Process::Process(unsigned _pid, unsigned _arrival_time)
{
    this->burst_time = generateRandomNum(1, 1000);
    this->io_burst_time = generateRandomNum(1000,10000);
    this->priority = generateRandomNum(1, 40);
    this->pid = _pid;
    this->arrival_time = _arrival_time;
    this->status = STATES::READY;

}
Process::Process(unsigned _pid, unsigned _arrival_time, unsigned _burst_time)
{
    this->burst_time = _burst_time;
    this->io_burst_time = generateRandomNum(1000,10000);
    this->priority = generateRandomNum(1, 40);
    this->pid = _pid;
    this->arrival_time = _arrival_time;
    this->status = STATES::READY;

}

Process::~Process()
{
    
}


