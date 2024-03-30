#include "fcfs.h"

Fcfs::Fcfs(int num_process) : bloqued_process_queue(), Base(num_process)
{
}

bool Fcfs::is_done()
{
    for (auto p : process_list)
    {
        if (p->status != STATES::DONE)
            return false;
    }
    return true;
}

void Fcfs::execute()
{

    Cpu cpu(2, 0);

    while (true)
    {

        for (auto p : process_list)
        {
            if (p->status == STATES::DONE)
                continue;

            if (cpu.num_ticks == p->arrival_time)
            {
                p->status = STATES::READY;
                process_queue.push(p);
                
            }
        }

        if(!bloqued_process_queue.empty())
        {
            for (auto p : process_list)
            {
                p->io();
            }

            if(bloqued_process_queue.front()->io_burst_time == 0){
                bloqued_process_queue.front()->generate_block_point();
                process_queue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        if (cpu.is_free() && !process_queue.empty())
        {
            if (cpu.assign_process(process_queue.front()))
                process_queue.pop();
        }

        STATES state = cpu.processing();


        if (state == STATES::BLOCKED)
        {
            bloqued_process_queue.push(cpu.interrupt());
        }else if (state == STATES::DONE)
        {
            if (is_done())
                break;
        }

        sendData(cpu.is_free(), cpu.num_ticks);
        
    }
}