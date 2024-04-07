#ifndef __SJF__
#define __SJF__
#include <queue>

#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "base.h"

/**
 * @brief Clase que implementa el algoritmo de planificación de procesos Shortest Job First (SJF) ó Primero el trabajo más corto.
 *
 * Esta clase implementa un planificador de procesos SJF, donde los procesos se ejecutan
 * en orden de su tiempo de burst time más corto.
 */

class SJF : public Base
{
public:

    /**
     * @brief Estructura de comparación para ordenar los procesos en la cola de prioridad.
     *
     * Esta estructura de comparación se utiliza para ordenar los procesos en la cola de prioridad
     * según su tiempo de ráfaga más corto. Si dos procesos tienen el mismo tiempo de burn time,
     * se prioriza el proceso con un tiempo de llegada menor.
     */
    struct Compare
    {
        /**
         * @brief Operador de comparación para ordenar procesos en la cola de prioridad.
         *
         * @param a Primer proceso a comparar.
         * @param b Segundo proceso a comparar.
         * @return bool
         */
        bool operator()(const sProcess &a, const sProcess &b)
        {
            auto b_ta = a->burst_time;
            auto b_tb = b->burst_time;
            if (b_ta == b_tb)
            {
                return a->arrival_time > b->arrival_time;
            }

            return b_ta > b_tb;
        }
    };

    /**
     * @brief Cola de prioridad para almacenar los procesos ordenados por tiempo de ráfaga.
     */
    std::priority_queue<sProcess, std::vector<sProcess>, Compare> process_queue;

    /**
     * @brief Cola para almacenar procesos bloqueados.
     */
    std::queue<sProcess> bloqued_process_queue;

    /**
     * @brief Constructor de la clase SJF.
     *
     * @param a Cantidad de Procesos a simular.
     */
    SJF(unsigned);

    SJF();
    /**
     * @brief Método para ejecutar el algoritmo Shortest Job First (SJF).
     *
     * @param tick_p Unidad de medida que representa cuantas unidades de tiempo va a representar un tick del procesador.
     * @param quantum_p Unidad de tiempo que toma el cpu en el procesador.
     *
     * Este método implementa la ejecución del algoritmo SJF.
     */
    void execute(unsigned, unsigned);


};

#endif
