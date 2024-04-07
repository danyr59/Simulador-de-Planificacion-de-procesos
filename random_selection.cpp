/**
 * @file random_selection.cpp
 * @brief Implementacion de la clase RandomSelection
 *
 * Define las funciones miembro para la clase RandomSelection, que implementa
 * el algoritmo de seleccion aleatoria de procesos para su ejecucion
 */
#include "random_selection.h"

/**
 * @brief Constructor de la clase RandomSelection.
 * Inicializa la clase base con el numero de procesos especificado.
 * @param num_process Numero de procesos a inicializar.
 */

RandomSelection::RandomSelection(int num_process) : Base(num_process) {
    // Inicializar procesos

}

/**
 * @brief Verifica si todos los procesos han terminado su ejecucion.
 * @return Verdadero si todos los procesos estan en el estado DONE, falso de lo contrario.
 */

bool RandomSelection::is_done() {
    for (auto p : process_list) {
        if (p->status != STATES::DONE)
            return false;
    }
    return true;
}

/**
 * @brief Ejecuta el algoritmo de seleccion aleatoria.
 * Asigna procesos de manera aleatoria a la CPU para su ejecucion y maneja los procesos bloqueados.
 * @param tick_p Unidad de tiempo que representa un tick del procesador.
 * @param quantum_p No se utiliza en este algoritmo, pero se incluye para mantener la firma del metodo.
 */

void RandomSelection::execute(unsigned tick_p, unsigned quantum_p = 0) {

    Cpu cpu(tick_p, quantum_p);

    std::vector<sProcess> ready_list;
    
    // Bucle principal de ejecucion del algoritmo
    while (!is_done()) {
     // Añadir procesos a la lista de listos segun su tiempo de llegada
        for (auto p : process_list)
        {
            if (p->status == STATES::DONE)
                continue;

            if (cpu.num_ticks == p->arrival_time)
            {
                p->status = STATES::READY;
                ready_list.push_back(p);

            }

        }

        // Actualizar el estado de E/S de los procesos bloqueados
        for(int i = 0 ; i < blocked_process_queue.size(); i++)
        {
            sProcess p = blocked_process_queue[i];

            p->io();
            if (p->io_burst_time == 0) {
                p->status = STATES::READY;
                ready_list.push_back(p);
                blocked_process_queue.erase(blocked_process_queue.begin()+i);
            }
        }

        // Seleccionar un proceso aleatorio de la lista de procesos listos y asignarlo a la CPU
        if (cpu.is_free() && !ready_list.empty()) {
            std::shuffle(ready_list.begin(), ready_list.end(), std::default_random_engine(generateRandomNum(0, ready_list.size() - 1)));
            auto selected_process = ready_list.front();
            ready_list.erase(ready_list.begin());
            cpu.assign_process(selected_process);
        }

        // Procesar la CPU y manejar los estados de los procesos
        STATES state = cpu.processing();
        if (state == STATES::BLOCKED) {
            auto interrupted_process = cpu.interrupt();
            blocked_process_queue.push_back(interrupted_process);
        }
        // Enviar datos para seguimiento y estadisticas
        sendData(cpu.is_free(), cpu.num_ticks);
    }
    sendData(cpu.is_free(), cpu.num_ticks, true);
}
