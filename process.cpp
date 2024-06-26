#include "process.h"

Process::Process(unsigned _pid, unsigned _arrival_time)
{
    this->burst_time = generateRandomNum(1, 30);
    this->io_burst_time = 0;
    this->priority = generateRandomNum(1, 40);
    this->pid = _pid;
    this->arrival_time = _arrival_time;
    generate_block_point();
}
Process::Process(unsigned _pid, unsigned _arrival_time, unsigned _burst_time)
{
    this->burst_time = _burst_time;
    this->priority = generateRandomNum(1, 40);
    this->io_burst_time = 0;
    this->pid = _pid;
    this->arrival_time = _arrival_time;
    generate_block_point();
}

Process::~Process()
{
}

void Process::io()
{
    if (status == STATES::BLOCKED && io_burst_time > 0)
        --io_burst_time;
}

void Process::generate_block_point()
{
    if(burst_time > 2)
    {
        
        int probability = generateRandomNum(0, 5);
        if (probability == 1)
        {
            //this->block_point = 4;
            this->block_point = generateRandomNum(1, burst_time-1);
            this->io_burst_time = generateRandomNum(1, 10);
        }

    }
    this->status = STATES::READY;
}