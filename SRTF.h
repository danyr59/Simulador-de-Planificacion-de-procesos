#ifndef SRTF_H
#define SRTF_H

#include "process.h"
#include "cpu.h"
#include <queue>
#include <memory>

class SRTF {

private:
    struct Compare
    {
        bool operator()(const sProcess &a, const sProcess &b)
        {
            return a->burst_time > b->burst_time;
        }
    };

public:
    SRTF(int num_process);
    void addProcess(std::shared_ptr<Process> p);
    void execute();

private:
    std::priority_queue<std::shared_ptr<Process>, std::vector<std::shared_ptr<Process>>, Compare> readyQueue;
    std::queue<std::shared_ptr<Process>> blockedProcessQueue;
};

#endif // SRTF_H