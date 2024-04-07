#ifndef __FCFS__
#define __FCFS__
#include <queue>
#include <vector>
#include <algorithm>
#include "cpu.h"
#include "base.h"


/**
 * @brief Clase que implementa el algoritmo de planificación de procesos First-Come, First-Served (FCFS).
 *
 * Esta clase implementa un planificador de procesos FCFS, donde los procesos se ejecutan
 * en el orden en el que llegan, sin tener en cuenta sus tiempos de ráfaga.
 */
class Fcfs: public Base
{
    public:
    /**
     * @brief Cola de procesos listos para ser ejecutados.
     *
     * Esta cola almacena los procesos que están listos para ser ejecutados según el algoritmo FCFS.
     */
    std::queue<sProcess> process_queue;

    /**
     * @brief Cola de procesos bloqueados.
     *
     * Esta cola almacena los procesos que están bloqueados y esperan recursos o eventos externos.
     */
    std::queue<sProcess> bloqued_process_queue;

    /**
     * @brief Constructor de la clase Fcfs.
     *
     * Crea una instancia de la clase Fcfs con el número especificado de procesos.
     *
     * @param num_process Número de procesos para inicializar la cola de procesos listos.
     */
    Fcfs(int num_process);

    /**
     * @brief Método para ejecutar el algoritmo FCFS.
     *
     * Este método ejecuta el algoritmo FCFS, donde los procesos se ejecutan en el orden
     * en el que llegan, sin tener en cuenta sus tiempos de rafaga.
     *
     * @param tick_p Unidad de medida que representa cuantas unidades de tiempo va a representar un tick del procesador.
     * @param quantum_p Unidad de tiempo que toma el cpu en el procesador.
     */
    void execute(unsigned, unsigned);

};





#endif
