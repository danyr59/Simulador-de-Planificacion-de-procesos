#ifndef __CPU__
#define __CPU__
#include <memory>
#include "process.h"
using sProcess = std::shared_ptr<Process>;


/**
 * @brief Clase que representa una Unidad Central de Procesamiento (CPU).
 */
class Cpu
{
private:
    unsigned tick; /**< Tiempo actual de la CPU (en unidades de tiempo)- Define cuantos unidades de tiempo representa un tick */
    unsigned quantum; /**< Duración del quantum de la CPU (en tick unidades). */
    std::chrono::_V2::system_clock::time_point start_time; /**< Momento de inicio del procesamiento actual. */
    bool free; /**< Indica si la CPU está libre para asignar un proceso. */
    sProcess current; /**< Proceso actualmente en ejecución en la CPU. */
    
public:
    unsigned num_ticks; /**< Contador de ticks de la CPU. */

    /**
     * @brief Constructor de la clase Cpu.
     *
     * @param _tick Unidad de medida que representa el tiempo de un tick de la CPU.
     * @param _quantum Duración del quantum de la CPU.
     */
    Cpu(unsigned _tick, unsigned _quantum);
    ~Cpu();

    /**
     * @brief Procesa el siguiente ciclo de ejecución en la CPU.
     *
     * @return Estado del proceso después de ejecutar el ciclo.
     */
    STATES processing();

    /**
     * @brief Verifica si la CPU está libre para asignar un proceso.
     *
     * @return true si la CPU está libre, false en caso contrario.
     */
    bool is_free();

    /**
     * @brief Interrumpe el proceso actualmente en ejecución en la CPU.
     *
     * @return Proceso que fue expulsado.
     */
    sProcess interrupt();

    /**
     * @brief Asigna un proceso para ser ejecutado en la CPU.
     *
     * @param p Proceso a asignar.
     * @return true si se pudo asignar el proceso correctamente, false en caso contrario.
     */
    bool assign_process(sProcess p);

    /**
     * @brief Obtiene la duración del quantum de la CPU.
     *
     * @return Duración del quantum de la CPU.
     */
    unsigned getQuantum() const{
        return this->quantum;
    }

    /**
     * @brief Obtiene el proceso actualmente en ejecución en la CPU.
     *
     * @return Proceso actualmente en ejecución en la CPU.
     */
    sProcess getCurrentProcess() const {
        return this->current;
    }
    


};

#endif
