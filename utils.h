#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <QThread>
#include <functional>
#include <unordered_map>
#include <algorithm>


/**
 * @brief Enumeración que define diferentes algoritmos de planificación de procesos.
 */
enum class ALGORITMO {
    NONE, /**< Indica que no se ha seleccionado ningún algoritmo. */
    FCFS, /**< Representa el algoritmo Primero en llegar primero en ejecutar (FCFS). */
    SJF, /**< Representa el algoritmo Primero el trabajo más corto (SJF). */
    SA, /**< Representa el algoritmo Selección aleatoria (SA). */
    PBEPNE, /**< Representa el algoritmo Planificación basada en prioridades (PBEPNE). */
    RR, /**< Representa el algoritmo Turno rotativo (RR). */
    SRTF, /**< Representa el algoritmo Primero el menor tiempo restante (SRTF). */
    PBEPE /**< Representa el algoritmo Planificación basada en prioridades (Expulsivo) (PBEPE). */
};

/**
 * @brief Enumeración que define los posibles estados de un proceso.
 */
enum class STATES
{
    READY, /**< Indica que el proceso está listo para ser ejecutado. */
    BLOCKED, /**< Indica que el proceso está bloqueado, esperando un evento de entrada/salida. */
    EXECUTE, /**< Indica que el proceso está siendo ejecutado. */
    DONE, /**< Indica que el proceso ha finalizado su ejecución. */
    NONE /**< Estado predeterminado o desconocido. */
};


/**
 * @brief Estructura para almacenar datos de un proceso.
 * para ser usado en las estadisticas finales
 */
struct data_process
{
    unsigned id;
    unsigned priority;
    unsigned burst_time;
};



/**
 * @brief Estructura para almacenar estadísticas finales del sistema.
 */
struct Final_stats
{
    unsigned total_tick; /**< Total de ticks de tiempo transcurridos. */
    unsigned total_occupied; /**< Total de tiempo en el que la CPU ha estado ocupada. */
    unsigned total_free; /**< Total de tiempo en el que la CPU ha estado libre. */
    std::unordered_map<unsigned,ushort> map_ready; /**< Mapa para contar cuántas veces un proceso ha estado listo. */
    std::unordered_map<unsigned,ushort> map_blocked; /**< Mapa para contar cuántas veces un proceso ha estado bloqueado. */
    std::unordered_map<unsigned,ushort> map_execution; /**< Mapa para contar cuántas veces un proceso ha estado en ejecución. */
};


/**
 * @brief Estructura para almacenar estadísticas del sistema en un momento específico.
 */
struct Stats
{
    data_process execution_process; /**< Proceso en ejecución en el momento específico. */
    std::vector<data_process> ready;  /**< Lista de procesos listos para ser ejecutados. */
    std::vector<data_process> blocked; /**< Lista de procesos bloqueados. */
    std::vector<data_process> done; /**< Lista de procesos que han finalizado su ejecución. */
    bool cpu_free; /**< Indica si la CPU está libre en el momento específico. */
    unsigned tick; /**< Tiempo actual del sistema en tick unidades. */
    Final_stats finals; /**< Estadísticas finales del sistema. */
    bool final; /**< Indica si es la última llamada a la función antes de finalizar la ejecución. */
};

typedef unsigned short int ushort;

/**
 * @brief Genera un número entero aleatorio en el rango especificado.
 *
 * @param min Valor mínimo del rango.
 * @param max Valor máximo del rango.
 * @return Número entero aleatorio generado.
 */
unsigned generateRandomNum(int min, int max);


/**
 * @brief Calcula el promedio de valores almacenados en un mapa no ordenado.
 *
 * @param map Mapa no ordenado que contiene los valores.
 * @return Promedio de los valores almacenados en el mapa.
 */
ushort generateAverage(const std::unordered_map<unsigned,ushort> &);


/**
 * @brief Duerme el hilo actual durante un período de tiempo especificado.
 *
 * @param time Tiempo en milisegundos durante el cual se debe dormir el hilo.
 */
void sleep(unsigned time);

#endif
