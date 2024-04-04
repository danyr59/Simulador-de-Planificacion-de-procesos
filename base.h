#ifndef __BASE__
#define __BASE__
#include "cpu.h"

class Base
{
public:
    int num_process;
    Final_stats fstats;
    std::vector<sProcess> process_list;
    std::function<void(Stats)> sendDataLambda;

    Base() : process_list(){};
    Base(int num_process) : process_list()
    {
        this->num_process = num_process;
        unsigned arraival_time = 0;
        fstats.total_free = 0;
        fstats.total_occupied = 0;
        fstats.total_free = 0;
        //controller = nullptr;
        for (int i = 0; i < num_process; ++i)
        {
            process_list.push_back(std::make_shared<Process>(i, arraival_time));
            arraival_time = generateRandomNum(arraival_time, arraival_time + 5);
        }
    };

    void bind(std::function<void(Stats)> f)
    {
       sendDataLambda = f;
    }
    // ejecucion de algoritmo
    virtual void execute(unsigned, unsigned){};
    bool is_done()
    {
        for (auto p : process_list)
        {
            if (p->status != STATES::DONE)
                return false;
        }
        return true;
    };

    void sendData(bool cpu_free, unsigned tick, bool final = false)
    {
        Stats stats;
        for (auto p : process_list)
        {
            if (p->status == STATES::READY)
            {
                stats.ready.push_back({p->pid, p->priority, p->burst_time});
                if(auto search = fstats.map_ready.find(p->pid); search != fstats.map_ready.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_ready.insert({p->pid, 0});
                }
            }
            if (p->status == STATES::EXECUTE)
            {
                stats.execution_process = {p->pid, p->priority, p->burst_time};
                if(auto search = fstats.map_execution.find(p->pid); search != fstats.map_execution.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_execution.insert({p->pid, 0});
                }
            }
            if (p->status == STATES::BLOCKED)
            {
                stats.blocked.push_back({p->pid, p->priority, p->burst_time});
                if(auto search = fstats.map_blocked.find(p->pid); search != fstats.map_blocked.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_blocked.insert({p->pid, 0});
                }
            }
            if(p->status == STATES::DONE){
                stats.done.push_back({p->pid, p->priority, p->burst_time});
            }
        }
        stats.cpu_free = cpu_free;
        stats.tick = tick;

        std::cout << stats.tick << std::endl;
        std::cout << stats.cpu_free << std::endl;

        for(auto p : stats.ready)
        {
            std::cout << "{" << p.id << "," << p.burst_time << "}" << std::endl;
        }
        std::cout << "========================" << std::endl;

        if(!final)
        {
            ++fstats.total_tick;

            if(cpu_free)
                ++fstats.total_free;
            else
                ++fstats.total_occupied;
        }
        stats.final = final;
        if(final)
            stats.finals = this->fstats;
        sendDataLambda(stats);
    }
};

#endif
