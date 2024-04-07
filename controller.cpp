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
        algorithm = std::make_unique<SJF>(this->quantity_process);

        break;
    case ALGORITMO::SA:
        algorithm = std::make_unique<RandomSelection>(this->quantity_process);

        break;
    case ALGORITMO::PBEPNE:
        algorithm = std::make_unique<NPPS>(this->quantity_process);

        break;
    case ALGORITMO::RR:
        algorithm = std::make_unique<RR>(this->quantity_process);

        break;
    case ALGORITMO::SRTF:
        algorithm = std::make_unique<SRTF>(this->quantity_process);
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
    //instanciar algoritmo
    std::unique_ptr<Base> base = instanceAlgotithm(this->algorithm);

    //vinculacion de la señal datosListos con el metodo sendData
    //hecho a través de una funcion lambda
    base->bind([this] (Stats data) {
        emit this->datosListos(data);
    });

    //ejecutar el algoritmo
    base->execute(this->tick, this->quantum);
    

}
