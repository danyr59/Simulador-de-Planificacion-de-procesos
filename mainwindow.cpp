#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new Controller(this);
    connect(controller, &Controller::datosListos, this,  &MainWindow::actualizarUI);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

void MainWindow::actualizarUI(const QString &datos)
{
    ui->output_label->setText(datos);
}

void MainWindow::on_pushButton_clicked()
{
    //verificar que antes de presionar el botom tener datos
    if(ui->algorithm_select->currentIndex() == 0)
    {
        this->Message("Debe seleccionar un algoritmo");
        return;
    }



    //de lo contrario mostrar mensaje

    std::cout << "algoritmo: " << ui->algorithm_select->currentIndex() << std::endl;
    std::cout << "numero de procesos: " << ui->process_number->value() << std::endl;
    std::cout << "numero de tick: " << ui->tick_number->value() << std::endl;
    controller->start();
}


void MainWindow::on_algorithm_select_currentIndexChanged(int index)
{
    alg = static_cast<ALGORITMO>(index);

    if(alg == ALGORITMO::FCFS || alg == ALGORITMO::SJF || alg == ALGORITMO::SA || alg == ALGORITMO::PBEPNE)
    {
        ui->label_4->hide();
        ui->quantum->hide();
    }else
    {
        ui->label_4->show();
        ui->quantum->show();
    }
    
    std::cout << index << std::endl;
}


void MainWindow::Message(QString text)
{
    QMessageBox messageBox(this);
    messageBox.critical(0, "Error", "Ha ocurrido un error");
    messageBox.setText(text);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();
}
