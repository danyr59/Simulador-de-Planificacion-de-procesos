/**
 * @file SRTF.cpp
 * @brief Implementacion de la clase SRTF para el algoritmo Shortest Remaining Time First.
 *
 * Define las funciones miembro para la clase SRTF, que implementa
 * el algoritmo de planificacion de procesos basado en el tiempo restante mas corto.
 */

#include "SRTF.h"

/**
 * @brief Constructor por defecto de la clase SRTF.
 * Inicializa la clase base sin procesos.
 */
SRTF::SRTF() : Base() {}

/**
 * @brief Constructor de la clase SRTF con numero de procesos.
 * Inicializa la clase base con el numero de procesos especificado.
 * @param num_process Numero de procesos a inicializar.
 */

SRTF::SRTF(unsigned num_process) : Base(num_process) {}

/**
 * @brief Ejecuta el algoritmo de planificacion SRTF.
 * Asigna procesos a la CPU basandose en el tiempo de rafaga restante mas corto y maneja los procesos bloqueados.
 * @param tick Unidad de tiempo que representa un tick del procesador.
 * @param quantum No se utiliza en este algoritmo, pero se incluye para mantener la firma del metodo.
 */

void SRTF::execute(unsigned tick, unsigned quantum) {
    Cpu cpu(tick, quantum);
   // Comparador para la cola de prioridad, ordena los procesos por tiempo de rafaga restante
auto comp = [&](sProcess a, sProcess b) { return a->burst_time > b->burst_time; };
std::priority_queue<sProcess, std::vector<sProcess>, decltype(comp)> readyQueue(comp);

    // Bucle principal de ejecucion del algoritmo
    while (!is_done()) {
        // Colocar procesos en la cola de listos si son elegibles para ejecucion
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

            // Si el proceso ha completado su tiempo de E/S, se genera un nuevo punto de bloqueo y se añade a la cola de listos
            if (bloqued_process_queue.front()->io_burst_time == 0) {
                bloqued_process_queue.front()->generate_block_point();
                bloqued_process_queue.front()->status = STATES::READY;
                readyQueue.push(bloqued_process_queue.front());
                bloqued_process_queue.pop();
            }
        }

        // Preemptar el proceso actual si hay otro con menor tiempo de rafaga restante
        if((!readyQueue.empty() && !cpu.is_free()) && (cpu.getCurrentProcess()->burst_time > readyQueue.top()->burst_time))
        {
            readyQueue.push(cpu.interrupt());
        }

        // Asignar el proceso con el menor tiempo de rafaga restante a la CPU si esta libre
         if (cpu.is_free() && !readyQueue.empty()) {
            auto top_process = readyQueue.top();
            readyQueue.pop();
        }

        // Procesar el estado de la CPU y actualizar el estado de los procesos
        STATES state = cpu.processing();
        //enviar datos para estadisticas
        sendData(cpu.is_free(), cpu.num_ticks);

        if (state == STATES::BLOCKED) {
            bloqued_process_queue.push(cpu.interrupt());
        } else if (state == STATES::DONE) {
            if (is_done()) {
                sendData(cpu.is_free(), cpu.num_ticks,true);
                break;
            }
        }

    }
}
