#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QThread>
#include "fcfs.h"

class Controller : public QThread 
{
    Q_OBJECT

public:
    Controller(QObject *parent = nullptr);
    void sendData(QString);
    
    
    signals:
        void datosListos(const QString &datos);

    protected:
        void run() override;

    private:

    
    
};

#endif // CONTROLLER_H
