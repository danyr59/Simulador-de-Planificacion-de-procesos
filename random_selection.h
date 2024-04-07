/**
 * @file random_selection.h
 * @brief Clase que implementa el algoritmo de planificacion de procesos de Seleccion Aleatoria
 *
 * Esta clase hereda de la clase Base y sobrescribe el metodo execute para implementar
 * la seleccion aleatoria de procesos para su ejecucion
 */

#ifndef __RANDOM_SELECTION__
#define __RANDOM_SELECTION__
#include <vector>
#include <queue>
#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "utils.h"
#include "base.h"

/**
 * @class RandomSelection
 * @brief Implementa el algoritmo de planificacion de procesos de Seleccion Aleatoria.
 *
 * En este algoritmo, los procesos son seleccionados de manera aleatoria de la lista de procesos listos
 * para su ejecucion, sin seguir un criterio especifico como prioridad o tiempo de rafaga.
 */

class RandomSelection : public Base {
private:
    std::vector<sProcess> blocked_process_queue; ///< Cola de procesos bloqueados esperando por recursos o eventos externos
    std::queue<sProcess> process_queue; ///< Cola de procesos listos para ser ejecutados.

public:
    /**
     * @brief Constructor de la clase RandomSelection.
     * @param num_process Numero de procesos para inicializar la cola de procesos listos
     */
    RandomSelection(int num_process);
    /**
     * @brief Metodo para ejecutar el algoritmo de Seleccion Aleatoria
     * @param tick_p Unidad de tiempo que representa un tick del procesador
     * @param quantum_p No se utiliza en este algoritmo, pero se incluye para mantener la firma del metodo
     */
    void execute(unsigned , unsigned ) override;
    /**
     * @brief Verifica si todos los procesos han sido completados
     * @return true si todos los procesos están en el estado DONE, false en caso contrario
     */
    bool is_done();
};

#endif
