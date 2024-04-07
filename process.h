#ifndef __PROCESS__
#define __PROCESS__
#include "utils.h"


/**
 * @brief Clase que representa un proceso en un sistema operativo.
 *
 * Esta clase representa un proceso en un sistema operativo, con atributos como
 * su identificador, tiempo de ráfaga(burns time), tiempo de ráfaga de E/S(io_burns_time), prioridad, etc.
 */
class Process
{
private:
public:

     /** Identificador único del proceso. */
    unsigned pid;

    /** Tiempo de ráfaga del proceso o burst time (tiempo de CPU). */
    unsigned burst_time;

    /** Tiempo de ráfaga de E/S o io burst time del proceso. */
    unsigned io_burst_time;

    /** Prioridad del proceso. */
    unsigned priority;

    /** Tiempo de llegada del proceso al sistema. */
    unsigned arrival_time;

    /** Punto de bloqueo del proceso (para E/S). */
    unsigned block_point;

    /** Estado actual del proceso. */
    STATES status;

    /**
     * @brief Constructor de la clase Process.
     *
     * Crea una instancia de la clase Process con un identificador único y tiempo de llegada especificados.
     *
     * @param _pid Identificador único del proceso.
     * @param _arrival_time Tiempo de llegada del proceso al sistema.
     */
    Process(unsigned _pid, unsigned _arrival_time);

    /**
     * @brief Constructor de la clase Process.
     *
     * Crea una instancia de la clase Process con un identificador único, tiempo de llegada y tiempo de ráfaga especificados.
     *
     * @param _pid Identificador único del proceso.
     * @param _arrival_time Tiempo de llegada del proceso al sistema.
     * @param _burst_time Tiempo de ráfaga del proceso (tiempo de CPU).
     */
    Process(unsigned _pid, unsigned _arrival_time, unsigned _burst_time);
    ~Process();


    /**
     * @brief Método para simular una operación de entrada/salida (E/S) del proceso.
     *
     * Este método simula una operación de E/S  y disminuye el tiempo de E/S.
     */
    void io();

    /**
     * @brief Método para generar un punto de bloqueo para el proceso (para E/S).
     *
     * Este método genera un punto de bloqueo aleatorio para simular una operación de E/S.
     * Si la duración de la ráfaga (burst_time) es mayor que 2, hay una probabilidad de generar un punto de bloqueo para el proceso.
     * Se genera un punto de bloqueo dentro del rango [1, burst_time - 1] y se genera un tiempo de ráfaga de entrada/salida (io_burst_time) dentro del rango [5, 20].
     */
    void generate_block_point();

};

#endif
