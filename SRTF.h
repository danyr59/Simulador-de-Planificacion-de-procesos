/**
 * @file SRTF.h
 * @brief Clase que implementa el algoritmo de planificacion de procesos Shortest Remaining Time First (SRTF).
 *
 * Esta clase hereda de la clase Base y sobrescribe el metodo execute para implementar
 * la planificacion de procesos basada en el tiempo restante mas corto.
 */
#ifndef __SRTF__
#define __SRTF__

#include "base.h"
#include "process.h"
#include <queue>

/**
 * @class SRTF
 * @brief Implementa el algoritmo de planificacion de procesos Shortest Remaining Time First (SRTF).
 *
 * En este algoritmo, los procesos son seleccionados para ejecucion basandose en el tiempo de rafaga restante mas corto.
 * Si un proceso con un tiempo de rafaga mas corto llega mientras otro proceso esta en ejecucion, el proceso actual
 * sera interrumpido y el nuevo proceso tomara su lugar.
 */

class SRTF : public Base {
public:
    /**
     * @brief Constructor por defecto de la clase SRTF.
     */
    SRTF();
    /**
     * @brief Constructor de la clase SRTF con numero de procesos.
     * @param num_process Numero de procesos para inicializar la cola de procesos listos.
     */
    SRTF(unsigned num_process);
    /**
     * @brief Metodo para ejecutar el algoritmo SRTF.
     * @param tick Unidad de tiempo que representa un tick del procesador.
     * @param quantum No se utiliza en este algoritmo, pero se incluye para mantener la firma del metodo.
     */
    void execute(unsigned tick, unsigned quantum = 0) override;

     /**
     * @brief Cola de procesos bloqueados esperando por recursos o eventos externos.
     */
    std::queue<sProcess> bloqued_process_queue;

};

#endif // SRTF_H
