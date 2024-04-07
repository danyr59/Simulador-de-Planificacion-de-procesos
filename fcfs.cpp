#include "fcfs.h"

Fcfs::Fcfs(int num_process) : bloqued_process_queue(), Base(num_process)
{
}

void Fcfs::execute(unsigned tick_p, unsigned quantum_p = 0)
{
    //instancia de la cpu para iniciar operaciones
    Cpu cpu(tick_p, quantum_p);

    while (true)
    {

        //se añaden procesos a la cola de procesos listos para ser ejecutados
        //se añaden a medida que van llegando en funcion del tiempo (tick)
        for (auto p : process_list)
        {
            if (p->status == STATES::DONE)
                continue;


            // Si el tiempo actual del sistema es igual al tiempo de llegada del proceso, se añade a la cola.
            if (cpu.num_ticks == p->arrival_time)
            {
                p->status = STATES::READY;
                process_queue.push(p);
                
            }
        }

        // si la cola de procesos bloqueantes no es vacia se realizan operaciones en la cola de procesos bloqueantes
        if(!bloqued_process_queue.empty())
        {
            //se decrementa menos 1 unidades de tick a los procesos en la cola de procesos bloqueados
            for (auto p : process_list)
            {
                p->io();
            }

            //se saca de la cola de procesos bloqueados
            //se añade de nuevo a la cola de procesos listos
            //se cambia de estatus el proceso en cuestion
            //se genera un nuevo punto de bloqueo , ya que hay procesos que pueden ser bloqueados nuevamente
            //la generacion de un punto de bloqueo se hace de manera aleatoria
            //todo esto se realiza debido a que el tiempo de bloqueo de ese proceso se acabo
            if(bloqued_process_queue.front()->io_burst_time == 0){
                bloqued_process_queue.front()->generate_block_point();
                process_queue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        //si el CPU esta libre y hay procesos disponibles a ser ejecutados
        //se asigna un proceso a la cpu para mantenerla ocupada
        //se saca el proceso de la cola de listos ya que pasa a ser ejecutada
        if (cpu.is_free() && !process_queue.empty())
        {
            if (cpu.assign_process(process_queue.front()))
                process_queue.pop();
        }

        //aca se realizan las operaciones correspondientes de procesamiento de la cpu
        //aca se disminuye burns time de cada proceso en execucion , asi como otros procesamientos
        //ademas retorna el estado en tiempo real de la cpu
        //aqui la cpu se encarga de determinar el estado del proceso en ese instante de tick
        STATES state = cpu.processing();


        if (state == STATES::BLOCKED)
        {
            //si el proceso que se esta ejecutando en la CPU , hace una llamada bloqueante
            //se añade a la cola de procesos bloqueantes, lo cual hace una interrupcion a la CPU
            bloqued_process_queue.push(cpu.interrupt());
        }else if (state == STATES::DONE)
        {
            //si el proceso que se esta ejecutando en la CPU, termina exitosamente
            //verifico si hay mas procesos si no me salgo de la simulacion
            if (is_done())
            {
                this->sendData(cpu.is_free(), cpu.num_ticks, true);
                break;
            }
        }

        //este metodo es un metodo hererado de @Class Base
        //permite enviar toda los datos relevantes para hacer el refresco en pantalla en cada tick del procesador
        sendData(cpu.is_free(), cpu.num_ticks);
        
    }
}
