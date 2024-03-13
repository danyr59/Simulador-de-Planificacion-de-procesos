#include "fcfs.h"

Fcfs::Fcfs(int num_process) : bloqued_process_queue()
{
    // aladur oircesiss
    process_list.push_back(std::make_shared<Process>(Process(1, 0, 3)));
    process_list.push_back(std::make_shared<Process>(Process(2, 1, 5)));
    process_list.push_back(std::make_shared<Process>(Process(4, 9, 5)));
    process_list.push_back(std::make_shared<Process>(Process(3, 4, 2)));
    process_list.push_back(std::make_shared<Process>(Process(5, 12, 5)));

    // ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(), [&](sProcess a, sProcess b)
              { return a->arrival_time < b->arrival_time; });

    // for(int i = 0; i < num_process; i++)
    // {
    //     this->process_queue.push(Process(i, i));
    // }
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
            p->io();

            if (p->status == STATES::DONE)
                continue;

            if (cpu.num_ticks == p->arrival_time)
            {
                process_queue.push(p);
                //break;
            }
        }

        if(!bloqued_process_queue.empty())
        {
            if(bloqued_process_queue.front()->io_burst_time == 0){
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

        
    }
}