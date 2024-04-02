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
    model_done = nullptr;
   // showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
    delete model_bloqued;
    delete model_ready;
    delete model_done;
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

    if(model_done == nullptr){
        model_done = new QStandardItemModel(this);
        ui->table_done->setModel(model_done);
    }


    model_bloqued->clear();
    model_ready->clear();
    model_done->clear();
    model_bloqued->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                           << "Prioridad"
                                                           << "Burst time");
    model_ready->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                         << "Prioridad"
                                                         << "Burst time");
    model_done->setHorizontalHeaderLabels(QStringList() << "Proceso"
                                                         << "Prioridad"
                                                         << "Burst time");

    ui->table_ready->setColumnWidth(0, 100);
    ui->table_ready->setColumnWidth(1, 140);
    ui->table_ready->setColumnWidth(2, 140);
    ui->table_ready->verticalHeader()->setVisible(false);
    ui->table_bloqued->setColumnWidth(0, 100);
    ui->table_bloqued->setColumnWidth(1, 140);
    ui->table_bloqued->setColumnWidth(2, 140);
    ui->table_bloqued->verticalHeader()->setVisible(false);
    ui->table_done->setColumnWidth(0, 100);
    ui->table_done->setColumnWidth(1, 140);
    ui->table_done->setColumnWidth(2, 140);
    ui->table_done->verticalHeader()->setVisible(false);
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
    ui->output_label->setText("Tick del Procesador: " + QString::number(datos.tick));


    iniciar_modelos();

    agregar_data(this->model_ready, datos.ready);
    agregar_data(this->model_bloqued, datos.blocked);
    agregar_data(this->model_done, datos.done);

    if(datos.cpu_free)
    {
        ui->current_id->setText("ID: NONE" );
        ui->current_time->setText("Burst time: ");
        ui->current_time_2->setText("Priority: ");
    }else

    {
        ui->current_id->setText("ID: " + QString::number(datos.execution_process.id));
        ui->current_time->setText("Burst time: " + QString::number(datos.execution_process.burst_time));
        ui->current_time_2->setText("Priority: " + QString::number(datos.execution_process.priority));
    }

    this->resultados_finales(datos);
}

bool MainWindow::warnings(){
    // verificar que antes de presionar el botom tener datos
    if (ui->algorithm_select->currentIndex() == 0)
    {
        this->Message("Debe seleccionar un algoritmo");
        return true;
    }

    if(controller->quantity_process == 0){
        this->Message("Debe seleccionar la cantidad de procesos");
        return true;
    }

    if(controller->tick == 0){
        this->Message("Debe seleccionar cuantos segundos deber durar un tick");
        return true;
    }
    if (alg == ALGORITMO::RR || alg == ALGORITMO::SRTF ||  alg == ALGORITMO::PBEPE)
    {
        if(controller->quantum == 0){
            this->Message("Debe seleccionar cuantas unidades de tick va a durar cada proceso en la CPU");
            return true;
        }
    }
    return false;
}

void MainWindow::on_pushButton_clicked()
{


    if(warnings())
        return;

    std::cout << "algoritmo: " << ui->algorithm_select->currentIndex() << std::endl;
    std::cout << "numero de procesos: " << ui->process_number->value() << std::endl;
    std::cout << "numero de tick: " << ui->tick_number->value() << std::endl;

    ui->data_widget->show();
    controller->setTypeAlgorithm(alg);
    controller->start();
}
std::string AlgoritmoToString(ALGORITMO a) {
    std::string selected;
    switch(a) {
    case ALGORITMO::NONE:
        selected = "NONE";
        break;
    case ALGORITMO::FCFS:
        selected = "FCFS";
        break;
    case ALGORITMO::SJF:
        selected = "SJF";
        break;
    case ALGORITMO::SA:
        selected = "SA";
        break;
    case ALGORITMO::PBEPNE:
        selected = "PBEPNE";
        break;
    case ALGORITMO::RR:
        selected = "RR";
        break;
    case ALGORITMO::SRTF:
        selected = "SRTF";
        break;
    case ALGORITMO::PBEPE:
        selected = "PBEPE";
        break;
    default:
        selected = "Desconocido";
        break;
    }
    return selected;
}

void MainWindow::on_algorithm_select_currentIndexChanged(int index)
{
    alg = static_cast<ALGORITMO>(index);

    std::cout << "Nombre del valor del enum: " << AlgoritmoToString(alg) << std::endl;

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

void MainWindow::on_process_number_valueChanged(int arg1)
{
    this->controller->quantity_process = arg1;
}


void MainWindow::on_tick_number_valueChanged(int arg1)
{
    this->controller->tick = arg1;
}


void MainWindow::on_quantum_valueChanged(int arg1)
{
    this->controller->quantum = arg1;
}


void MainWindow::resultados_finales(const Stats &stats)
{
    if(!stats.final)
        return;

    ui->table_bloqued->setVisible(false);
    ui->table_ready->setVisible(false);

    std::cout << "Finales total free " << stats.finals.total_free << std::endl;
    std::cout << "Finales total bloqued " << stats.finals.total_occupied << std::endl;
    std::cout << "Finales total " << stats.finals.total_tick << std::endl;
}
