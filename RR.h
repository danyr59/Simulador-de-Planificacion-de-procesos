#ifndef __RR__
#define __RR__

#include <queue>
#include <vector>
#include <algorithm>
#include "process.h"
#include "cpu.h"
#include "base.h"

/**
 * @brief Clase que implementa el algoritmo de planificación de procesos Round Robin.
 *
 * Esta clase implementa un planificador de procesos Round Robin, donde los procesos se ejecutan
 * en un ciclo circular y cada proceso se ejecuta durante un quantum de tiempo antes de pasar
 * al siguiente proceso en la cola.
 */
class RR : public Base
{
public:
    /**
     * @brief Constructor predeterminado de la clase RR.
     * @deprecated Este metodo solo se usa para casos de testing
     *
     * Crea una instancia de la clase RR con un caso base para probar RR
     */
    RR();

    /**
     * @brief Constructor de la clase RR con un numero de procesos especificado.
     *
     * Crea una instancia de la clase RR con un numero de procesos especificado.
     *
     * @param num_procesosCantidad de Procesos a simular.
     */
    RR(unsigned );

    /**
     * @brief Cola de procesos listos para ser ejecutados.
     *
     * Esta cola almacena los procesos que están listos para ser ejecutados según el algoritmo RR.
     */
    std::queue<sProcess> process_queue;

    /**
     * @brief Cola de procesos bloqueados.
     *
     * Esta cola almacena los procesos que están bloqueados.
     */
    std::queue<sProcess> bloqued_process_queue;


    /**
     * @brief Método para ejecutar el algoritmo Round Robin.
     *
     * Este método ejecuta el algoritmo Round Robin, donde cada proceso se ejecuta durante un quantum de tiempo
     * antes de pasar al siguiente proceso en la cola. Los procesos se ejecutan en un ciclo circular.
     *
     * @param tick_p Unidad de medida que representa cuantas unidades de tiempo va a representar un tick del procesador.
     * @param quantum_p Unidad de tiempo que toma el cpu en el procesador.
     */
    void execute(unsigned, unsigned);

};

#endif
