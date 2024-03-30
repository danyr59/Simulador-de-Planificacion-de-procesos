#ifndef __SJF__
#define __SJF__
#include <queue>
// #include <vector>
#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "base.h"

class SJF : public Base
{
public:
    struct Compare
    {
        bool operator()(const sProcess &a, const sProcess &b)
        {
            auto b_ta = a->burst_time;
            auto b_tb = b->burst_time;
            if (b_ta == b_tb)
            {
                return a->arrival_time > b->arrival_time;
            }

            return b_ta > b_tb;
        }
    };
    // std::queue<sProcess> process_queue;
    std::priority_queue<sProcess, std::vector<sProcess>, Compare> process_queue;
    //std::vector<sProcess> process_list;

    std::queue<sProcess> bloqued_process_queue;
    SJF(unsigned);
    SJF();
    void execute();
   
    
};

#endif