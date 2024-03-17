#ifndef __BASE__
#define __BASE__
#include "cpu.h"

class Base
{
    public:
    int num_process;
    std::vector<sProcess> process_list;

    Base(): process_list(){};
    Base(int num_process): process_list(){
        this->num_process = num_process;
        unsigned arraival_time = 0;
        for(int i = 0; i < num_process; ++i)
        {
            process_list.push_back(std::make_shared<Process>(i, arraival_time));
            arraival_time = generateRandomNum(arraival_time, arraival_time + 5);
        }
    };
    //ejecucion de algoritmo
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
};

#endif