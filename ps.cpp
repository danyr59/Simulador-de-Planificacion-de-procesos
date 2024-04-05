#include "ps.h"

PS::PS(int num_process): Base(num_process),
process_queue_h(PS::comparator),
process_queue_m(PS::comparator),
process_queue_l(PS::comparator),
bloqued_process_queue()
{
    priority_rate = 4;
    took_h = took_m = 0;
    hight_limit = 10;
    mid_limit = 30;   
    this->burst_time_limit_h = 10;
    this->burst_time_limit_m = 5;
    this->burst_time_limit_l = 3;
}

PS::PS(int num_process, ushort hight_limit, ushort mid_limit, ushort priority_rate,ushort burst_time_limit_h, ushort burst_time_limit_m, ushort burst_time_limit_l):
Base(num_process),
process_queue_h(PS::comparator),    
process_queue_m(PS::comparator),    
process_queue_l(PS::comparator),
bloqued_process_queue()
{
    took_h = took_m = 0;
    this->mid_limit = mid_limit;
    this->hight_limit = hight_limit;
    this->priority_rate = priority_rate;
    this->burst_time_limit_h = burst_time_limit_h;
    this->burst_time_limit_m = burst_time_limit_m;
    this->burst_time_limit_l = burst_time_limit_l;
}

bool PS::empty()
{
    return process_queue_h.empty() && process_queue_l.empty() && process_queue_m.empty();
}

void PS::push(sProcess p)
{
    if(p->priority < hight_limit)
        process_queue_h.push(p);
    else if(p->priority < mid_limit)
        process_queue_m.push(p);
    else
        process_queue_l.push(p);
}

/// @brief take a process of the queues corresponding to priority.
/// this assume at least one queue is not empty. check it with empty()
/// @return shared_pointer of process
sProcess PS::pop(ushort &cbtl)
{
    if(!process_queue_h.empty() && took_h < priority_rate)
    { 
        ++took_h;
        sProcess p = process_queue_h.top();
        cbtl = burst_time_limit_h;
        process_queue_h.pop();
        return p;
    }
    if(!process_queue_m.empty() && took_m < priority_rate)
    {
        took_h = 0;
        ++took_m; 
        sProcess p = process_queue_m.top();
        cbtl = burst_time_limit_m;
        process_queue_m.pop();
        return p;
    }
    took_h = 0;
    took_m = 0;
    if(!process_queue_l.empty())
    {
        sProcess p = process_queue_l.top();
        cbtl = burst_time_limit_l;
        process_queue_l.pop();
        return p;
    }else
        return pop(cbtl);
    
}

void PS::execute(unsigned tick_p, unsigned quantum_p = 0)
{
    Cpu cpu(tick_p, 0);
    int p_index = 0;
    ushort current_burst_time_limit = 0;

    while (true)
    {

        while (p_index < num_process && process_list[p_index]->status != STATES::DONE && process_list[p_index]->arrival_time == cpu.num_ticks)
        {
                 this->push(process_list[p_index]);
                ++p_index;
        }

        if(!bloqued_process_queue.empty())
        {
            for (auto p : process_list)
            {
                p->io();
            }

            if(bloqued_process_queue.front()->io_burst_time == 0){
                bloqued_process_queue.front()->generate_block_point();
                this->push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        if (cpu.is_free() && !this->empty())
        {
            cpu.assign_process(this->pop(current_burst_time_limit));
        }

        this->sendData(cpu.is_free(), cpu.num_ticks);

        STATES state = cpu.processing();

        if(!cpu.is_free())
            --current_burst_time_limit;

        if(current_burst_time_limit == 0 && state == STATES::EXECUTE) 
        {
            this->push(cpu.interrupt());
        }

        if (state == STATES::BLOCKED)
        {
            bloqued_process_queue.push(cpu.interrupt());
        }else if (state == STATES::DONE)
        {
            if (is_done())
            {
                this->sendData(cpu.is_free(), cpu.num_ticks, true);
                break;
            }

        }
    }
}
