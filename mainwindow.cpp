#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    contador = 0;
    label = this->findChild<QLabel*>("label");
    button = this->findChild<QPushButton*>("pushButton");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete button;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "button precionado" << std::endl;
    this->close();
}

