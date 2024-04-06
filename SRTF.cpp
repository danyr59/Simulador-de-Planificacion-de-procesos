#include "SRTF.h"

SRTF::SRTF() : Base() {}

SRTF::SRTF(unsigned num_process) : Base(num_process) {}

void SRTF::execute(unsigned tick, unsigned quantum) {
    Cpu cpu(tick, quantum);
   
auto comp = [&](sProcess a, sProcess b) { return a->burst_time > b->burst_time; };
std::priority_queue<sProcess, std::vector<sProcess>, decltype(comp)> readyQueue(comp);
int contador = 0;
    while (!is_done()) {
        // Colocar procesos en la cola de listos si son elegibles para ejecución
        for (auto process : process_list) {
            if (process->status == STATES::NONE && cpu.num_ticks == process->arrival_time) {
                process->status = STATES::READY;
                readyQueue.push(process);
            }
        }

        // Procesar los procesos bloqueados
        if (!bloqued_process_queue.empty()) {
            for (auto p : process_list) {
                p->io();
            }

            if (bloqued_process_queue.front()->io_burst_time == 0) {
                bloqued_process_queue.front()->generate_block_point();
                bloqued_process_queue.front()->status = STATES::READY;
                readyQueue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        // Asignar procesos a la CPU si está libre
         if (cpu.is_free() && !readyQueue.empty()) {
            auto top_process = readyQueue.top();
            readyQueue.pop();
            if (cpu.assign_process(top_process)) {
                contador = 0;
         //       std::cout << "Proceso asignado a la CPU: ID " << top_process->pid << ", Ráfaga de CPU " << top_process->burst_time << std::endl;
            }
        }

        // Procesar el estado de la CPU
        STATES state = cpu.processing();
        ++contador;
        sendData(cpu.is_free(), cpu.num_ticks);

        if(contador >= cpu.getQuantum())
        {
            readyQueue.push(cpu.interrupt());
        }

        if (state == STATES::BLOCKED) {
            bloqued_process_queue.push(cpu.interrupt());
           // std::cout << "Proceso bloqueado: ID " << cpu.interrupt()->pid << std::endl;
        } else if (state == STATES::DONE) {
            if (is_done()) {
                sendData(cpu.is_free(), cpu.num_ticks,true);
                break;
            }
        }

        // Enviar datos para seguimiento y estadísticas

    }
}
