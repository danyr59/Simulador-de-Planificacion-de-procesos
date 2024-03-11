#include "fcfs.h"

Fcfs::Fcfs(int num_process)
{
    //aladur oircesiss
    process_list.push_back(Process(1, 0, 3));
    process_list.push_back(Process(2, 1, 5));
    process_list.push_back(Process(4, 9, 5));
    process_list.push_back(Process(3, 4, 2));
    process_list.push_back(Process(5, 12, 5));

    //ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(),[&](Process a,Process b){
        return a.arrival_time < b.arrival_time;
    });
    
    // for(int i = 0; i < num_process; i++)
    // {
    //     this->process_queue.push(Process(i, i));
    // }
}

bool Fcfs::is_done()
{
    for(auto p : process_list)
    {
        if(p.status != STATES::READY)
            return false;
    }
    return true;
}

void Fcfs::execute()
{   

    Cpu _cpu(2, 0); 


    while (true ) {
        for(auto p : process_list)
        {
            if(p.status == STATES::DONE)
                continue;

            if(_cpu.num_ticks == p.arrival_time){
                process_queue.push(p);
                break;
            }
        }

        //Process ´pro.pop();
        
        
        //dormir la execucion un tick;
        //_cpu.processing();

       
    }


}