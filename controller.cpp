#include "controller.h"

Controller::Controller(QObject *parent) : QThread(parent)
{

}

void Controller::run()
{
    //ejecuccion de cada algoritmo
    //obtener metricas
    //exponer metricas
    //emit datosListos("dato");
    Fcfs fcfs(4);
    fcfs.bind(this,&Controller::sendData);
    fcfs.execute();
    

}

void Controller::sendData(QString data)
{
    emit datosListos(data);
}
