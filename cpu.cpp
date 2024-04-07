#include "cpu.h"

Cpu::Cpu(unsigned _tick, unsigned _quantum)
{
    this->tick = _tick; 
    this->quantum = _quantum;
    this->start_time = std::chrono::high_resolution_clock::now();
    this->num_ticks = 0;
    this->free = true;
    this->current = nullptr;
}

Cpu::~Cpu() 
{
}

STATES Cpu::processing()
{
    // Pausa la ejecución por el tiempo de un tick
    QThread::msleep(this->tick);

    // Incrementa el contador de ticks de la CPU
    ++num_ticks;

    // Si la CPU está libre o no hay un proceso actual, se considera que la CPU está en estado de ejecución
    if(free || current == nullptr)
        return STATES::EXECUTE;

    // Reduce el tiempo de burst time del proceso actual en ejecución
    --current->burst_time;

    // Verifica si el proceso actual ha terminado su ejecución
    if(current->burst_time == 0)
    {
       // Marca la CPU como libre y el proceso actual como completado
        free = true;
        current->status = STATES::DONE;
        current = nullptr;
        return STATES::DONE;
    }

     // Verifica si el proceso actual ha alcanzado su punto de bloqueo
    if(current->burst_time == current->block_point)
    {
         // Marca el proceso actual como bloqueado y devuelve el estado de bloqueo
        current->status = STATES::BLOCKED;
        return STATES::BLOCKED;
    }
    
    // Si no se cumplen las condiciones anteriores, el proceso sigue ejecutándose
    return STATES::EXECUTE;
}

bool Cpu::is_free()
{
    return free;
}

sProcess Cpu::interrupt()
{
     // Marca la CPU como libre
    free = true;

    // Si el proceso estaba en estado de ejecución, lo cambia a estado listo
    if(current->status ==  STATES::EXECUTE)
        current->status = STATES::READY;

     // Retorna el proceso que fue interrumpido
    return current;
}

bool Cpu::assign_process(sProcess p)
{
    // Verifica si la CPU está libre
    if(!free)
        return false;

    // Asigna el proceso especificado y lo marca como en estado de ejecución
    current = p;
    current->status = STATES::EXECUTE;
    free = false;

    return true;
}
