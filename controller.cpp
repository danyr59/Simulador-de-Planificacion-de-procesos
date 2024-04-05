#include "controller.h"

Controller::Controller(QObject *parent) : QThread(parent), quantity_process(0), tick(0), quantum(0)
{

}

void Controller::setTypeAlgorithm(ALGORITMO a){
    this->algorithm = a;
}
std::unique_ptr<Base> Controller::instanceAlgotithm(ALGORITMO a){
    std::unique_ptr<Base> algorithm;
    switch (a) {
    case ALGORITMO::FCFS:
        algorithm = std::make_unique<Fcfs>(this->quantity_process);

        break;
    case ALGORITMO::SJF:
        algorithm = std::make_unique<SJF>(4);

        break;
    case ALGORITMO::SA:
        algorithm = std::make_unique<Fcfs>(4);

        break;
    case ALGORITMO::PBEPNE:
        algorithm = std::make_unique<NPPS>(this->quantity_process);

        break;
    case ALGORITMO::RR:
        algorithm = std::make_unique<RR>(this->quantity_process);

        break;
    case ALGORITMO::SRTF:
        algorithm = std::make_unique<Fcfs>(4);
        break;
    case ALGORITMO::PBEPE:
        algorithm = std::make_unique<PS>(this->quantity_process);
        break;
    default:
        break;
    }
    return algorithm;
}

void Controller::run()
{
    std::unique_ptr<Base> base = instanceAlgotithm(this->algorithm);


    //ejecuccion de cada algoritmo
    //obtener metricas
    //exponer metricas
    //emit datosListos("dato");
    //Fcfs fcfs(4);
    base->bind([this] (Stats data) {
        emit this->datosListos(data);
    });
    base->execute(this->tick, this->quantum);
    

}
