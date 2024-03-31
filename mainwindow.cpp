#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new Controller(this);
    connect(controller, &Controller::datosListos, this, &MainWindow::actualizarUI);
    ui->data_widget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

void MainWindow::actualizarUI(const Stats &datos)
{
    ui->output_label->setText("numero de string:" + QString::number(datos.tick));
   

    QStandardItemModel *model = new QStandardItemModel(this);

   
    model->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                   << "Prioridad"
                                                   << "Burst time");

    int i = 0;
    for(auto p : datos.ready)
    {
        
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(p.id).arg(i)));
        items.append(new QStandardItem(QString::number(p.priority).arg(i + 1)));
        items.append(new QStandardItem(QString::number(p.burst_time).arg(i + 2)));
        model->appendRow(items);
        ++i;
    }

    ui->current_id->setText("ID: " + QString::number(datos.execution_process.id));
    ui->current_time->setText("Burst time: " + QString::number(datos.execution_process.burst_time));

    ui->table_ready->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    // verificar que antes de presionar el botom tener datos
    if (ui->algorithm_select->currentIndex() == 0)
    {
        this->Message("Debe seleccionar un algoritmo");
        return;
    }

    // de lo contrario mostrar mensaje

    std::cout << "algoritmo: " << ui->algorithm_select->currentIndex() << std::endl;
    std::cout << "numero de procesos: " << ui->process_number->value() << std::endl;
    std::cout << "numero de tick: " << ui->tick_number->value() << std::endl;
    ui->data_widget->show();
    controller->start();
}

void MainWindow::on_algorithm_select_currentIndexChanged(int index)
{
    alg = static_cast<ALGORITMO>(index);

    if (alg == ALGORITMO::FCFS || alg == ALGORITMO::SJF || alg == ALGORITMO::SA || alg == ALGORITMO::PBEPNE)
    {
        ui->label_4->hide();
        ui->quantum->hide();
    }
    else
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
