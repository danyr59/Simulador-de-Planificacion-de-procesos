#ifndef __BASE__
#define __BASE__
#include "cpu.h"

class Base
{
public:
    //Controller *controller;
    int num_process;
    std::vector<sProcess> process_list;
    Stats stats;
    std::function<void(QString)> sendDataLambda;

    Base() : process_list(){};
    Base(int num_process) : process_list()
    {
        this->num_process = num_process;
        unsigned arraival_time = 0;
        //controller = nullptr;
        for (int i = 0; i < num_process; ++i)
        {
            process_list.push_back(std::make_shared<Process>(i, arraival_time));
            arraival_time = generateRandomNum(arraival_time, arraival_time + 5);
        }
    };

    void bind(std::function<void(QString)> f)
    {
       sendDataLambda = f;
    }
    // ejecucion de algoritmo
    virtual void execute(){};
    bool is_done()
    {
        for (auto p : process_list)
        {
            if (p->status != STATES::DONE)
                return false;
        }
        return true;
    };

    void sendData(bool cpu_free, unsigned tick)
    {
        for (auto p : process_list)
        {
            if (p->status == STATES::READY)
                stats.ready.push_back({p->pid, p->priority, p->burst_time});
            if (p->status == STATES::EXECUTE)
                stats.execution_process = {p->pid, p->priority, p->burst_time};
            if (p->status == STATES::BLOCKED)
                stats.blocked.push_back({p->pid, p->priority, p->burst_time});
        }
        stats.cpu_free = cpu_free;
        stats.tick = tick;

        std::cout << stats.tick << std::endl;
        std::cout << stats.cpu_free << std::endl;
        sendDataLambda("prueba tick:" + QString::number(stats.tick));
    }
};

#endif
