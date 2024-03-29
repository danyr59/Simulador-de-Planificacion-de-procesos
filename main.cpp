#include "mainwindow.h"
#include "process.h"
#include "fcfs.h"
#include "SJF.h"
#include "npps.h"
#include "ps.h"
#include "random_selection.h"
#include "RR.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
