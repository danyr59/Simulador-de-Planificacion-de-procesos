#include "RR.h"

RR::RR()
{
    process_list.push_back(std::make_shared<Process>(Process(1, 0, 3)));
    process_list.push_back(std::make_shared<Process>(Process(2, 1, 4)));
    process_list.push_back(std::make_shared<Process>(Process(3, 3, 6)));
    process_list.push_back(std::make_shared<Process>(Process(4, 5, 5)));
    process_list.push_back(std::make_shared<Process>(Process(5, 4, 3)));

    // ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(), [&](sProcess a, sProcess b)
              { return a->arrival_time < b->arrival_time; });
}

bool RR::is_done()
{
    for (auto p : process_list)
    {
        if (p->status != STATES::DONE)
            return false;
    }
    return true;
}

void RR::execute()
{

    Cpu cpu(2, 2);
    unsigned time = 0;
    bool add_process_interrup = false;


    while (true)
    {

        for (auto p : process_list)
        {
            if (p->status == STATES::DONE)
                continue;

            if (cpu.num_ticks == p->arrival_time)
            {
                process_queue.push(p);
                break;
            }

            // añadir a la cola cuando dismuya x cantidad de tick  definido por el quantum
        }

        if (add_process_interrup)
        {
            process_queue.push(cpu.interrupt());
            time = 0;
            
            add_process_interrup = false;
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
                process_queue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        if (cpu.is_free() && !process_queue.empty())
        {
            if (cpu.assign_process(process_queue.front()))
                process_queue.pop();
        }
        auto current = cpu.getCurrentProcess();
        STATES state = cpu.processing();

        if (state == STATES::BLOCKED)
        {
            bloqued_process_queue.push(cpu.interrupt());
        }
        else if (state == STATES::DONE)
        {
            if (is_done())
                break;
                //para metricas mostrar el current(variable local)
                //ya que el cpu en este momento no apunta a nada 
            

        }
        else if (state == STATES::EXECUTE)
        {
            if (time == cpu.getQuantum() - 1)
            {
                add_process_interrup = true;
            }
            else
            {
                ++time;
            }
        }

        std::cout << "h" << std::endl;
    }
}