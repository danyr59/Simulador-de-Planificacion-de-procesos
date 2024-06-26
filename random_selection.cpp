#include "random_selection.h"

RandomSelection::RandomSelection(int num_process) {
    // Inicializar procesos
    process_list.push_back(std::make_shared<Process>(Process(1, 0, 5)));
    process_list.push_back(std::make_shared<Process>(Process(2, 2, 3)));
    process_list.push_back(std::make_shared<Process>(Process(3, 4, 4)));
    process_list.push_back(std::make_shared<Process>(Process(4, 6, 2)));

}

bool RandomSelection::is_done() {
    for (auto p : process_list) {
        if (p->status != STATES::DONE)
            return false;
    }
    return true;
}

void RandomSelection::execute() {

    Cpu cpu(2, 0);

    while (!is_done()) {
        // Actualizar el estado de E/S de los procesos bloqueados
        for (auto& p : blocked_process_queue) {
            p->io();
            if (p->io_burst_time == 0) {
                p->status = STATES::READY;
                process_list.push_back(p);
               // std::cout << "Proceso " << p->pid << " desbloqueado y movido a la cola de procesos listos." << std::endl;
            }
        }

        // Eliminar procesos bloqueados que estén listos para ser desbloqueados
        for (auto it = blocked_process_queue.begin(); it != blocked_process_queue.end(); ) {
            if ((*it)->status == STATES::READY) {
                it = blocked_process_queue.erase(it);
            } else {
                ++it;
            }
        }

        // Seleccionar un proceso aleatorio de la lista de procesos listos y asignarlo a la CPU
        if (cpu.is_free() && !process_list.empty()) {
            std::shuffle(process_list.begin(), process_list.end(), std::default_random_engine(generateRandomNum(0, process_list.size() - 1)));
            auto selected_process = process_list.front();
            process_list.erase(process_list.begin());
            if (cpu.assign_process(selected_process)) {
                //std::cout << "Proceso " << selected_process->pid << " asignado a la CPU." << std::endl;
            }
        }

        // Procesar la CPU
        STATES state = cpu.processing();
        if (state == STATES::BLOCKED) {
            auto interrupted_process = cpu.interrupt();
            blocked_process_queue.push_back(interrupted_process);
            //std::cout << "Proceso " << interrupted_process->pid << " interrumpido y movido a la cola de procesos bloqueados." << std::endl;
        }

        //std::cout << "Simulando paso del tiempo..." << std::endl;
        std::cout << 5 << std::endl;
    }
}
