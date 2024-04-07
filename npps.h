#ifndef __NPPS__
#define __NPPS__
#include <queue>
#include <vector>
#include <algorithm>
#include "base.h"
#include "process.h"
#include "cpu.h"
//Non Preemptive Priority Scheduling

class NPPS: public Base
{
    private:
    //relacion de toma entre las colas
    ushort priority_rate;
    //contador para la cola de alta prioridad
    ushort took_h;
    //contador para la cola de mediana prioridad
    ushort took_m;

    //limite para asignar a la cola de alta prioridad
    ushort hight_limit;
    //limite para asignar a la cola de mediana prioridad
    ushort mid_limit;

    public:
    //cola de alta prioridad
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_h;
    //cola de mediana prioridad
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_m;
    //cola de baja prioridad
    std::priority_queue<sProcess, std::vector<sProcess>, std::function<bool(sProcess,sProcess)>> process_queue_l;

    //cola de procesos bloqueados
    std::queue<sProcess> bloqued_process_queue; 

    NPPS(int num_process);
    NPPS(int num_process, ushort hight_limit, ushort mid_limit, ushort priority_rate);
    

    /**
     * @brief Inserta un proceso a las colas segun su prioridad 
     * si la prioridad es menor al limite alto se inserta en alta prioridad.
     * si es menor al limite medio se insera en mediana priodidad.
     * si no se inserta en baja prioridad
     *
     * @param p proceso a insertar
     */
    void push(sProcess p);
    /**
     * @brief Toma un proceso de la cola que le toca.
     * Se asume que las colas no estan vacias
     *
     * @return proceso tomado
     */
    sProcess pop();

    //ejecucion del algoritmo
    void execute(unsigned, unsigned);

    /**
     * @brief comprueba si todas las colas estan vacias
     * 
     * @return true si todas las colas estan vacias
     */
    bool empty();

    /**
     * @brief Compara los procesos basandose en la prioridad.
     *
     * @param a proceso a
     * @param b proceso b
     * @return true si el proceso a es mayor al b
     */
    static bool comparator(sProcess a, sProcess b)
    {
        return a->priority > b->priority;
    }
};





#endif
