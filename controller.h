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
        void run() override;


    
    
};

#endif // CONTROLLER_H
