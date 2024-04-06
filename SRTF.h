//#ifndef SRTF_H
/*#define SRTF_H

#include "process.h"
#include "cpu.h"
#include <queue>
#include <memory>
#include "base.h"
#include <algorithm>

class SRTF: public Base {

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
   // void addProcess(sProcess p);
    void execute(unsigned ,unsigned ) override;

private:
   // std::priority_queue<std::shared_ptr<Process>, std::vector<std::shared_ptr<Process>>, Compare> readyQueue;
    std::priority_queue<sProcess, std::vector<sProcess>, Compare> readyQueue;    
   // std::queue<std::shared_ptr<Process>> blockedProcessQueue;
    std::queue<sProcess> blockedProcessQueue;

};

#endif // SRTF_H
*/
#ifndef __SRTF__
#define __SRTF__

#include "base.h"
#include "process.h"
#include <queue>

class SRTF : public Base {
public:
    SRTF();
    SRTF(unsigned num_process);
    void execute(unsigned tick, unsigned quantum = 0) override;
    std::queue<sProcess> bloqued_process_queue;

};

#endif // SRTF_H
