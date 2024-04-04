#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QThread>
#include <functional>
#include <unordered_map>
#include <algorithm>



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

struct Final_stats
{
    unsigned total_tick;
    unsigned total_occupied;
    unsigned total_free;
    std::unordered_map<unsigned,ushort> map_ready;
    std::unordered_map<unsigned,ushort> map_blocked;
    std::unordered_map<unsigned,ushort> map_execution;
};


struct Stats
{
    data_process execution_process;
    std::vector<data_process> ready;
    std::vector<data_process> blocked;
    std::vector<data_process> done;
    bool cpu_free;
    unsigned tick;
    Final_stats finals;
    bool final;
};

typedef unsigned short int ushort;

unsigned generateRandomNum(int min, int max);

ushort generateAverage(const std::unordered_map<unsigned,ushort> &);

//sleep for time milliseconds
void sleep(unsigned time);

#endif
