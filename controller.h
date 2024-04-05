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
    void setTypeAlgorithm(ALGORITMO);
    unsigned quantity_process;
    unsigned tick;
    unsigned quantum;
    
    signals:
        void datosListos(const Stats &datos);

    protected:
        void run() override;

    private:
        ALGORITMO algorithm;

        std::unique_ptr<Base> instanceAlgotithm(ALGORITMO);

    
    
};

#endif // CONTROLLER_H
