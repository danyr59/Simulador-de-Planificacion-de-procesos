#ifndef __BASE__
#define __BASE__
#include "cpu.h"

/**
 * @brief Clase base para la implementación de algoritmos de planificación de procesos.
 *
 * Esta clase proporciona una base común para la implementación de diferentes algoritmos de planificación
 * de procesos. Contiene una serie de métodos y miembros de datos compartidos por los algoritmos específicos.
 */
class Base
{
public:
    /** Número total de procesos. */
    int num_process;

    /** Estructura para almacenar estadísticas finales. */
    Final_stats fstats;

    /** Lista de procesos. */
    std::vector<sProcess> process_list;

     /** Función lambda para enviar datos de estadísticas. */
    std::function<void(Stats)> sendDataLambda;

    /**
     * @brief Constructor predeterminado de la clase Base.
     * @deprecated
     * Crea una instancia de la clase Base sin procesos.
     */
    Base() : process_list(){};


    /**
     * @brief Constructor de la clase Base con un número específico de procesos.
     *
     * Crea una instancia de la clase Base con el número especificado de procesos.
     * Los procesos se inicializan con tiempos de llegada aleatorios y estados iniciales.
     *
     * @param num_process Número total de procesos a crear.
     */
    Base(int num_process) : process_list()
    {
        this->num_process = num_process;
        unsigned arraival_time = 0;
        fstats.total_free = 0;
        fstats.total_occupied = 0;
        fstats.total_free = 0;
        //controller = nullptr;
        for (int i = 0; i < num_process; ++i)
        {
            process_list.push_back(std::make_shared<Process>(i, arraival_time));
            arraival_time = generateRandomNum(arraival_time, arraival_time + 5);
        }
    };


    /**
     * @brief Método para vincular una función lambda para enviar datos de estadísticas.
     * Esta funcion me permite estar conectado por medio de Señales y slots con QT para refresco
     * y visualizacion de datos por pantalla en tiempo real
     *
     * @param f Función lambda que recibe un objeto Stats como parámetro.
     */
    void bind(std::function<void(Stats)> f)
    {
       sendDataLambda = f;
    }


    /**
     * @brief Método virtual para ejecutar un algoritmo de planificación de procesos.
     *
     * Este método debe ser implementado por las clases derivadas para ejecutar
     * el algoritmo específico de planificación de procesos.
     *
     * @param tick_p Unidad de medida que representa cuantas unidades de tiempo va a representar un tick del procesador.
     * @param quantum_p Unidad de tiempo que toma el cpu en el procesador.
     */
    virtual void execute(unsigned, unsigned){};


    /**
     * @brief Verifica si todos los procesos han finalizado.
     *
     * @return true si todos los procesos han finalizado; false en caso contrario.
     */
    bool is_done()
    {
        for (auto p : process_list)
        {
            if (p->status != STATES::DONE)
                return false;
        }
        return true;
    };


    /**
     * @brief Método para enviar datos de estadísticas.
     *
     * Este método recopila estadísticas de los procesos y envía los datos utilizando la función lambda vinculada.
     *
     * @param cpu_free Indica si la CPU está libre en el momento actual.
     * @param tick Tiempo actual del sistema (en unidades de tiempo).
     * @param final Indica si es la última llamada a la función antes de finalizar la ejecución.
     */
    void sendData(bool cpu_free, unsigned tick, bool final = false)
    {
        Stats stats;
        for (auto p : process_list)
        {
            if (p->status == STATES::READY)
            {
                stats.ready.push_back({p->pid, p->priority, p->burst_time});
                if(auto search = fstats.map_ready.find(p->pid); search != fstats.map_ready.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_ready.insert({p->pid, 0});
                }
            }
            if (p->status == STATES::EXECUTE)
            {
                stats.execution_process = {p->pid, p->priority, p->burst_time};
                if(auto search = fstats.map_execution.find(p->pid); search != fstats.map_execution.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_execution.insert({p->pid, 0});
                }
            }
            if (p->status == STATES::BLOCKED)
            {
                stats.blocked.push_back({p->pid, p->priority, p->burst_time});
                if(auto search = fstats.map_blocked.find(p->pid); search != fstats.map_blocked.end())
                {
                    ++search->second;
                }else
                {
                    fstats.map_blocked.insert({p->pid, 0});
                }
            }
            if(p->status == STATES::DONE){
                stats.done.push_back({p->pid, p->priority, p->burst_time});
            }
        }
        stats.cpu_free = cpu_free;
        stats.tick = tick;

        std::cout << stats.tick << std::endl;
        std::cout << stats.cpu_free << std::endl;

        for(auto p : stats.ready)
        {
            std::cout << "{" << p.id << "," << p.burst_time << "}" << std::endl;
        }
        std::cout << "========================" << std::endl;

        if(!final)
        {
            ++fstats.total_tick;

            if(cpu_free)
                ++fstats.total_free;
            else
                ++fstats.total_occupied;
        }
        stats.final = final;
        if(final)
            stats.finals = this->fstats;
        sendDataLambda(stats);
    }
};

#endif
