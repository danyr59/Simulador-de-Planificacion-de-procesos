#include "controller.h"

Controller::Controller(QObject *parent) : QThread(parent)
{

}

void Controller::run()
{
    //ejecuccion de cada algoritmo
    //obtener metricas
    //exponer metricas
    emit datosListos("dato");
}
