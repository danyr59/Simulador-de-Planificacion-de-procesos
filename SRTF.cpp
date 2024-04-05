#include "SRTF.h"

SRTF::SRTF() : Base() {}

SRTF::SRTF(unsigned num_process) : Base(num_process) {}

void SRTF::execute(unsigned tick, unsigned quantum) {
    Cpu cpu(tick, quantum);
   
auto comp = [&](sProcess a, sProcess b) { return a->burst_time > b->burst_time; };
std::priority_queue<sProcess, std::vector<sProcess>, decltype(comp)> readyQueue(comp);

    while (!is_done()) {
        // Colocar procesos en la cola de listos si son elegibles para ejecución
        for (auto process : process_list) {
            if (process->status == STATES::READY) {
                if (cpu.num_ticks >= process->arrival_time && 
                    (!cpu.getCurrentProcess() || process->burst_time < cpu.getCurrentProcess()->burst_time)) {
                    if (!cpu.is_free()) {
                        auto interrupted_process = cpu.interrupt();
                        interrupted_process->status = STATES::READY;
                        readyQueue.push(interrupted_process);
                   //     std::cout << "Proceso interrumpido: ID " << interrupted_process->pid << std::endl;
                    }
                    readyQueue.push(process);
                 //   std::cout << "Proceso encolado: ID " << process->pid << ", Tiempo de llegada " << process->arrival_time << std::endl;
                }
            }
        }

        // Procesar los procesos bloqueados
        if (!bloqued_process_queue.empty()) {
            for (auto p : process_list) {
                p->io();
            }

            if (bloqued_process_queue.front()->io_burst_time == 0) {
                bloqued_process_queue.front()->generate_block_point();
                readyQueue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        // Asignar procesos a la CPU si está libre
         if (cpu.is_free() && !readyQueue.empty()) {
            auto top_process = readyQueue.top();
            readyQueue.pop();
            if (cpu.assign_process(top_process)) {
         //       std::cout << "Proceso asignado a la CPU: ID " << top_process->pid << ", Ráfaga de CPU " << top_process->burst_time << std::endl;
            }
        }

        // Procesar el estado de la CPU
        STATES state = cpu.processing();

        if (state == STATES::BLOCKED) {
            bloqued_process_queue.push(cpu.interrupt());
           // std::cout << "Proceso bloqueado: ID " << cpu.interrupt()->pid << std::endl;
        } else if (state == STATES::DONE) {
            if (is_done()) {
                break;
            }
        }

        // Enviar datos para seguimiento y estadísticas
        sendData(cpu.is_free(), cpu.num_ticks);
    }
}
