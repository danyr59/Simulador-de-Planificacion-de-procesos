#ifndef __FCFS__
#define __FCFS__
#include <queue>
#include <vector>
#include <algorithm>
#include "process.h"
#include "cpu.h"


class Fcfs 
{
    public:
    std::queue<sProcess> process_queue;
    std::vector<sProcess> process_list;


    Fcfs(int num_process);

    //funcion para sacar metricas

    //ejecucion de algoritmo
    void execute(); 
    bool is_done();
};





#endif