#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qthread.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    contador = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "button precionado" << std::endl;

    for (size_t i = 0; i < 5; i++)
    {
        /* code */
        ui->label->setText("paso " + QString::number(i));
         QThread::sleep(1);
    }
    
    this->close();
    
}

