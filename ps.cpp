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

sProcess PS::pop(ushort &cbtl)
{
    //comprobamos si esta vacia y
    //si ya se ha tomado los procesos permitidos
    if(!process_queue_h.empty() && took_h < priority_rate)
    { 
        //aumentamos el contador para marcar que se tomo un proceso de la cola
        ++took_h;
        sProcess p = process_queue_h.top();
        //asignamos el limite de ejecucion de alta prioridad
        cbtl = burst_time_limit_h;
        process_queue_h.pop();
        return p;
    }
    //comprobamos si esta vacia y
    //si ya se ha tomado los procesos permitidos
    if(!process_queue_m.empty() && took_m < priority_rate)
    {   
        //devolvemos a 0 el contador.
        //para que se vuelvan a tomar procesos de la cola de alta prioridad
        took_h = 0;
        ++took_m; 
        sProcess p = process_queue_m.top();
        //asignamos el limite de ejecucion de mediana prioridad
        cbtl = burst_time_limit_m;
        process_queue_m.pop();
        return p;
    }
    //devolvemos a 0 el contador.
    //para que se vuelvan a tomar procesos de las colas de alta y mediana prioridad 
    took_h = 0;
    took_m = 0;
    //comprobamos si esta vacia
    if(!process_queue_l.empty())
    {
        sProcess p = process_queue_l.top();
        //asignamos el limite de ejecucion de baja prioridad
        cbtl = burst_time_limit_l;
        process_queue_l.pop();
        return p;
    }else
        //hacemos un llamado recursivo para que se tomen procesos de las otras colas
        return pop(cbtl);
    
}

void PS::execute(unsigned tick_p, unsigned quantum_p = 0)
{
    //instancia del cpu
    Cpu cpu(tick_p, 0);
    //indice del proceso a insertar
    int p_index = 0;
    //limite del proseso en ejecucion
    ushort current_burst_time_limit = 0;

    while (true)
    {
        //tomamos un proceso y lo insertamos en la cola de listos basandose en el tiempo de llegada
        while (p_index < num_process && process_list[p_index]->status != STATES::DONE && process_list[p_index]->arrival_time == cpu.num_ticks)
        {
                 this->push(process_list[p_index]);
                ++p_index;
        }
        //comprobamos si la cola esta vacia
        if(!bloqued_process_queue.empty())
        {
            //simulamos I/O en los prosesos
            for (auto p : process_list)
            {
                p->io();
            }

            //sacamos de la cola de bloqueo al proceso que si esta listo
            if(bloqued_process_queue.front()->io_burst_time == 0){
                bloqued_process_queue.front()->generate_block_point();
                this->push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }
        
        //si el procesador esta libre se asigna un proceso
        if (cpu.is_free() && !this->empty())
        {
            cpu.assign_process(this->pop(current_burst_time_limit));
        }
        //enviamos los datos que seran mostrados en pantalla
        this->sendData(cpu.is_free(), cpu.num_ticks);

        STATES state = cpu.processing();

        //restamos al limite en cada ejecuion
        if(!cpu.is_free())
            --current_burst_time_limit;
        
        //sacamos el proceso del cpu si ya agoto el tiempo asignado
        if(current_burst_time_limit == 0 && state == STATES::EXECUTE) 
        {
            this->push(cpu.interrupt());
        }

        //si el proceso se bloqueo se libera del procesador
        if (state == STATES::BLOCKED)
        {
            bloqued_process_queue.push(cpu.interrupt());
        }else if (state == STATES::DONE)
        {
            // si el proceso termino. se comprueba si todo terminaron
            if (is_done())
            {
                //se envian la datos finales para mostrar la estadisticas
                this->sendData(cpu.is_free(), cpu.num_ticks, true);
                break;
            }

        }
    }
}
