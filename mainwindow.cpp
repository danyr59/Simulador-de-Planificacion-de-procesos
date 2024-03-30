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
    controller = new Controller(this);
    connect(controller, &Controller::datosListos, this,  &MainWindow::actualizarUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarUI(const QString &datos)
{
    ui->label->setText(datos);
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "button precionado" << std::endl;
    controller->start();
}

