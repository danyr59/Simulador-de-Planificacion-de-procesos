#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QThread>
#include <functional>



enum class ALGORITMO {
    NONE,
    FCFS,
    SJF,
    SA,
    PBEPNE,
    RR,
    SRTF,
    PBEPE
};


enum class STATES
{
    READY,
    BLOCKED,
    EXECUTE,
    DONE,
    NONE
};

struct data_process
{
    unsigned id;
    unsigned priority;
    unsigned burst_time;
};


struct Stats
{
    data_process execution_process;
    std::vector<data_process> ready;
    std::vector<data_process> blocked;
    std::vector<data_process> done;
    bool cpu_free;
    unsigned tick;
    /* data */
};


typedef unsigned short int ushort;

unsigned generateRandomNum(int min, int max);

//sleep for time milliseconds
void sleep(unsigned time);

#endif
