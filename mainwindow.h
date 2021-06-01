#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QCheckBox>
#include <QTableWidgetItem>
#include "addcamwindow.h"
#include <QTableView>
#include <QTabWidget>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:


    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_cameraData_clicked();

    void on_AddEQ_clicked();




    void on_Loaddata_clicked();



private:

    Ui::MainWindow *ui;
    bool hasInit;
    bool taskInit;
    QSqlDatabase db;
       int currentId;
    AddcamWindow* addCam;

};
#endif // MAINWINDOW_H
