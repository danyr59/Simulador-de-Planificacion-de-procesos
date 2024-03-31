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
    model_bloqued = nullptr;
    model_ready = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

void MainWindow::iniciar_modelos()
{
    if(model_ready == nullptr)
    {
        model_ready = new QStandardItemModel(this);
        ui->table_ready->setModel(model_ready);
    }
    if(model_bloqued == nullptr)
    {
        model_bloqued = new QStandardItemModel(this);

        ui->table_bloqued->setModel(model_bloqued);
    }

    model_bloqued->clear();
    model_ready->clear();
    model_bloqued->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                           << "Prioridad"
                                                           << "Burst time");
    model_ready->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                         << "Prioridad"
                                                         << "Burst time");
}

void MainWindow::agregar_data(QStandardItemModel *model, const std::vector<data_process> &datos)
{
    int i = 0;
    for(auto p : datos)
    {

        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(p.id).arg(i)));
        items.append(new QStandardItem(QString::number(p.priority).arg(i + 1)));
        items.append(new QStandardItem(QString::number(p.burst_time).arg(i + 2)));
        model->appendRow(items);
        ++i;
    }

}

void MainWindow::actualizarUI(const Stats &datos)
{
    ui->output_label->setText("numero de string:" + QString::number(datos.tick));


    iniciar_modelos();

    agregar_data(this->model_ready, datos.ready);
    agregar_data(this->model_bloqued, datos.blocked);

    if(datos.cpu_free)
    {
        ui->current_id->setText("ID: NONE" );
        ui->current_time->setText("Burst time: ");
    }else

    {
        ui->current_id->setText("ID: " + QString::number(datos.execution_process.id));
        ui->current_time->setText("Burst time: " + QString::number(datos.execution_process.burst_time));
    }
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
