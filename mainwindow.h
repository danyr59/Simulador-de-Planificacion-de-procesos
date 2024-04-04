#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>

#include <string>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

#include "utils.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ALGORITMO alg;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void actualizarUI(const Stats &datos);

    void on_algorithm_select_currentIndexChanged(int index);

    void on_process_number_valueChanged(int arg1);

    void on_tick_number_valueChanged(int arg1);

    void on_quantum_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Controller *controller;
    QStandardItemModel *model_ready;
    QStandardItemModel *model_bloqued;
    QStandardItemModel *model_done;
    QBarSeries *barseries;
    QPieSeries *pieseries;
    QValueAxis *axisY;

    //funtions
    void Message(QString);
    void iniciar_modelos();
    void agregar_data(QStandardItemModel *, const std::vector<data_process> &);
    void resultados_finales(const Stats &);
    bool warnings();
};
#endif // MAINWINDOW_H
