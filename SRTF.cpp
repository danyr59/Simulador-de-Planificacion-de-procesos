#include "SRTF.h"

SRTF::SRTF(int num_process) {
    addProcess(std::make_shared<Process>(Process(1, 0, 8)));
    addProcess(std::make_shared<Process>(Process(2, 1, 4)));
    addProcess(std::make_shared<Process>(Process(3, 2, 6)));
    addProcess(std::make_shared<Process>(Process(4, 3, 3)));
    addProcess(std::make_shared<Process>(Process(5, 4, 5)));
    addProcess(std::make_shared<Process>(Process(6, 5, 2)));
    addProcess(std::make_shared<Process>(Process(7, 6, 7)));
}

void SRTF::addProcess(std::shared_ptr<Process> p) {
    readyQueue.push(p);
}

void SRTF::execute() {
    std::shared_ptr<Process> runningProcess = nullptr;
    unsigned int currentTime = 0;

    while (!readyQueue.empty() || runningProcess) {
        // Si no hay proceso en ejecución o el proceso en la cola tiene un burst time menor
        if (!runningProcess || (readyQueue.top()->burst_time < runningProcess->burst_time)) {
            // Si hay un proceso en ejecución, lo encolamos como bloqueado
            if (runningProcess) {
                blockedProcessQueue.push(runningProcess);
            }
            // Sacamos el próximo proceso de la cola
            runningProcess = readyQueue.top();
            readyQueue.pop();
        }

        // Simulamos la ejecución de una unidad de tiempo
        currentTime++;

        // Reducimos el burst time del proceso en ejecución
        runningProcess->burst_time--;

        // Si el burst time es 0, el proceso ha terminado
        if (runningProcess->burst_time == 0) {
          //  std::cout << "Proceso " << runningProcess->pid << " completado en el tiempo " << currentTime << std::endl;
            runningProcess.reset(); // Liberamos el proceso en ejecución
        }

        // Procesamos la cola de procesos bloqueados
        while (!blockedProcessQueue.empty() && blockedProcessQueue.front()->arrival_time <= currentTime) {
            readyQueue.push(blockedProcessQueue.front());
            blockedProcessQueue.pop();
        }
    }
}
