#include "npps.h"

NPPS::NPPS(int num_process): Base(num_process),
process_queue_h(NPPS::comparator),
process_queue_m(NPPS::comparator),
process_queue_l(NPPS::comparator),
bloqued_process_queue()
{
    priority_rate = 4;
    took_h = took_m = 0;
    hight_limit = 10;
    mid_limit = 30;    
}

NPPS::NPPS(int num_process, ushort hight_limit, ushort mid_limit, ushort priority_rate):
Base(num_process),
process_queue_h(NPPS::comparator),    
process_queue_m(NPPS::comparator),    
process_queue_l(NPPS::comparator),
bloqued_process_queue()
{
    took_h = took_m = 0;
    this->mid_limit = mid_limit;
    this->hight_limit = hight_limit;
    this->priority_rate = priority_rate;
}

bool NPPS::empty()
{
    return process_queue_h.empty() && process_queue_l.empty() && process_queue_m.empty();
}

void NPPS::push(sProcess p)
{
    p->status = STATES::READY;
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
sProcess NPPS::pop()
{
    if(!process_queue_h.empty() && took_h < priority_rate)
    { 
        ++took_h;
        sProcess p = process_queue_h.top();
        process_queue_h.pop();
        return p;
    }
    if(!process_queue_m.empty() && took_m < priority_rate)
    {
        took_h = 0;
        ++took_m; 
        sProcess p = process_queue_m.top();
        process_queue_m.pop();
        return p;
    }
    took_h = 0;
    took_m = 0;
    if(!process_queue_l.empty())
    {
        sProcess p = process_queue_l.top();
        process_queue_l.pop();
        return p;
    }else
        return pop();
    
}

void NPPS::execute(unsigned tick_p, unsigned quantum_p = 0)
{
    Cpu cpu(2, 0);
    int p_index = 0;

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
            cpu.assign_process(this->pop());
        }

        STATES state = cpu.processing();

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

        this->sendData(cpu.is_free(), cpu.num_ticks);
       
    }
}
