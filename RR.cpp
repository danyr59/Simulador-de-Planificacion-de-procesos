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

RR::RR(unsigned num_procesos) : Base(num_procesos)
{

     // ordenar procesos por tiempo de llegada
    std::sort(process_list.begin(), process_list.end(), [&](sProcess a, sProcess b)
              { return a->arrival_time < b->arrival_time; });
}

void RR::execute(unsigned tick_p, unsigned quantum_p = 0)
{

    //instancia de la cpu para iniciar operaciones
    Cpu cpu(tick_p, quantum_p);
    //bandera y contador que me permite identificar si debo expulsar un proceso de la cpu
    unsigned time = 0;
    bool add_process_interrup = false;

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


        //se expulsan procesos de la cpu debido a que su quantum en la cpu ha terminado
        if (add_process_interrup)
        {
            time = 0;
            process_queue.push(cpu.interrupt());
            add_process_interrup = false;
        }

         // si la cola de procesos bloqueantes no es vacia se realizan operaciones en la cola de procesos bloqueantes
        if (!bloqued_process_queue.empty())
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
            if (bloqued_process_queue.front()->io_burst_time == 0)
            {
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

        //este metodo es un metodo hererado de @Class Base
        //permite enviar toda los datos relevantes para hacer el refresco en pantalla en cada tick del procesador
        sendData(cpu.is_free(), cpu.num_ticks +1);

        //obtengo el proceso actual que esta siendo ejecutado
        //me permite saber el estado del proceso cuando es expulsado de la cpu
        //debido a que su quantum en el procesador acabo
        auto current = cpu.getCurrentProcess();


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
        }
        else if (state == STATES::DONE)
        {
            //si el proceso que se esta ejecutando en la CPU, termina exitosamente
            //verifico si hay mas procesos si no me salgo de la simulacion
            if (is_done())
            {
                this->sendData(cpu.is_free(), cpu.num_ticks, true);
                break;
            }

        }
        else if (state == STATES::EXECUTE)
        {
            //comprobacion ya que hay momentos en los que los procesos no han llegado a la cola de procesos listo
            //esto quiere decir que su tiempo de arribo es mayor que el instante de tick
            //entonces hay procesos que todavia faltan por ser procesados
            if (current == NULL || cpu.is_free())
                continue;

            //este paso disminuye el quantum e indica cuando un proceso debe ser expulsado de la cpu
            if (time == cpu.getQuantum() - 1)
            {
                add_process_interrup = true;
            }
            else
            {
                ++time;
            }
        }


    }

}
