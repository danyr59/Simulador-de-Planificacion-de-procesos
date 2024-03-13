#include "process.h"

Process::Process(unsigned _pid, unsigned _arrival_time)
{
    this->burst_time = generateRandomNum(1, 10);
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
    int probability = generateRandomNum(0, 5);
    if (probability == 1)
    {
        this->block_point = generateRandomNum(0, burst_time);
        this->io_burst_time = generateRandomNum(0, 10);
    }
    this->status = STATES::READY;
}