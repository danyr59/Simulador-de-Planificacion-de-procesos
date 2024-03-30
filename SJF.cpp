#include "SJF.h"

SJF::SJF(unsigned a) : Base(a)
{

    // ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(), [&](sProcess a, sProcess b)
              { return a->arrival_time < b->arrival_time; });
}
SJF::SJF()
{
    process_list.push_back(std::make_shared<Process>(Process(1, 0, 8)));
    process_list.push_back(std::make_shared<Process>(Process(5, 4, 4)));
    process_list.push_back(std::make_shared<Process>(Process(3, 2, 4)));
    process_list.push_back(std::make_shared<Process>(Process(4, 6, 2)));

    // ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(), [&](sProcess a, sProcess b)
              { return a->arrival_time < b->arrival_time; });
}

void SJF::execute()
{
    Cpu cpu(2, 0);

    /*
     */
    while (true)
    {
        for (sProcess process : process_list)
        {
            if (process->status == STATES::DONE)
                continue;

            if (cpu.num_ticks == process->arrival_time)
            {
                process_queue.push(process);
                break;
            }
        }

        if (!bloqued_process_queue.empty())
        {
            for (auto p : process_list)
            {
                p->io();
            }

            if (bloqued_process_queue.front()->io_burst_time == 0)
            {
                bloqued_process_queue.front()->generate_block_point();
                auto dropped_out = bloqued_process_queue.front();
                dropped_out->arrival_time = cpu.num_ticks;
                process_queue.push(dropped_out);
                bloqued_process_queue.pop();
            }
        }

        if (cpu.is_free() && !process_queue.empty())
        {
            if (cpu.assign_process(process_queue.top()))
                process_queue.pop();
        }

        STATES state = cpu.processing();

        if (state == STATES::BLOCKED)
        {
            bloqued_process_queue.push(cpu.interrupt());
        }
        else if (state == STATES::DONE)
        {
            if (is_done())
                break;
        }
        
    }
    
}
