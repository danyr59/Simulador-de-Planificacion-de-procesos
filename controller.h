#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QThread>

class Controller : public QThread 
{
    Q_OBJECT

public:
    Controller(QObject *parent = nullptr);
    
    
    signals:
        void datosListos(const QString &datos);

    protected:
        void run() override{
            //ejecuccion de cada algoritmo
            //obtener metricas
            //exponer metricas
            for (size_t i = 0; i < 5; i++)
            {
                
                emit datosListos("dato " + QString::number(i));
                QThread::sleep(1);
                
            }
            

        }


    
    
};

#endif // CONTROLLER_H
