// #include "mainwindow.h"
#include "process.h"
#include "fcfs.h"
#include "SJF.h"
#include "npps.h"
#include "ps.h"
#include "random_selection.h"
#include "RR.h"

//#include <QApplication>

int main(int argc, char *argv[])
{
    //std::cout << "hola";
    //Fcfs fcfs(8);
    //fcfs.execute();
    SJF sjf(3);
    sjf.execute();
    RandomSelection randomselection(7);
    randomselection.execute();
    NPPS npps(10);
    npps.execute();
    RR rr(3);
    rr.execute();
    PS ps(10);
    ps.execute();
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    return 0;//a.exec();
}
