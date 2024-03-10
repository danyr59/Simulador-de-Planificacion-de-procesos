#ifndef __FCFS__
#define __FCFS__
#include <queue>
#include "process.h"


class Fcfs 
{
    public:
    std::queue<Process> process_queue;


    Fcfs(int num_process);
    //funcion para sacar metricas

    //ejecucion de algoritmo
    void execute(); 
};





#endif