#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>

#include <string>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QStandardItemModel>
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

private:
    Ui::MainWindow *ui;
    Controller *controller;

    //funtions
    void Message(QString);
};
#endif // MAINWINDOW_H
