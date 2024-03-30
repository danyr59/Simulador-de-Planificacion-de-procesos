#ifndef __BASE__
#define __BASE__
#include "cpu.h"
#include "controller.h"

class Base
{
public:
    Controller *controller;
    int num_process;
    std::vector<sProcess> process_list;
    Stats stats;
    void (Controller::*_sendData)(QString);
    //std::function<void(QString)> sendDataLambda;

    Base() : process_list(){};
    Base(int num_process) : process_list()
    {
        this->num_process = num_process;
        unsigned arraival_time = 0;
        _sendData = nullptr;
        for (int i = 0; i < num_process; ++i)
        {
            process_list.push_back(std::make_shared<Process>(i, arraival_time));
            arraival_time = generateRandomNum(arraival_time, arraival_time + 5);
        }
    };

    void bind(Controller *con ,void (Controller::*_sendData)(QString))
    {
        this->_sendData = _sendData;
        this->controller = con;
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
        (controller->*_sendData)("prueba tick:" + QString::number(stats.tick));
    }
};

#endif