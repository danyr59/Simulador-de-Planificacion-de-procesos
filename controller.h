#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QThread>
#include "fcfs.h"
#include "SJF.h"
#include "random_selection.h"
#include "npps.h"
#include "ps.h"
#include "RR.h"
#include "utils.h"
#include "SRTF.h"
class Controller : public QThread 
{
    Q_OBJECT

public:
    Controller(QObject *parent = nullptr);
    /**
     * @brief asigna la variable algorithm
     *
     * @param algorithm
     */
    void setTypeAlgorithm(ALGORITMO);

    //cantidad de procesos a simular
    unsigned quantity_process;
    //tick del procesador en milisegundos
    unsigned tick;
    //quantum del algorithmo
    unsigned quantum;
    
    signals:
        /**
         * @brief señal emitida al estar listos los datos
         *
         * @param datos a motrar en pantalla
         */
        void datosListos(const Stats &datos);

    protected:
        /**
         * @brief ejecutar el algoritmo seleccionado
        */
        void run() override;

    private:
        //algoritmo seleccionado
        ALGORITMO algorithm;
        /**
         * @brief crea una instancia del algoritmo con los parametros guardados.
         *
         * @param tipo de algoritmo a instanciar
         * 
         * @return instancia del algoritmo
         */
        std::unique_ptr<Base> instanceAlgotithm(ALGORITMO);

    
    
};

#endif // CONTROLLER_H
