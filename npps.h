#ifndef __NPPS__
#define __NPPS__
#include <queue>
#include <vector>
#include <algorithm>
#include "base.h"
#include "process.h"
#include "cpu.h"
//Non Preemptive Priority Scheduling

class NPPS: public Base
{
    private:
    ushort priority_rate;
    //proccess took of hight priority queue
    ushort took_h;
    //proccess took of mid priority queue
    ushort took_m;
    //limit for hight priority queue 
    ushort hight_limit;
    //limit for mid priority queue 
    ushort mid_limit;

    public:
    //hight priority queue
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_h;
    //mid priority queue
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_m;
    //low priority queue
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_l;

    std::queue<sProcess> bloqued_process_queue; 

    NPPS(int num_process);
    NPPS(int num_process, ushort hight_limit, ushort mid_limit, ushort priority_rate);
    
    void push(sProcess p);
    sProcess pop();
    void execute();
    bool empty();
    //funcion para sacar metricas

    //comparator
    static bool comparator(sProcess a, sProcess b)
    {
        return a->priority > b->priority;
    }
};





#endif