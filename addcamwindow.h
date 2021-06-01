#ifndef ADDCAMWINDOW_H
#define ADDCAMWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QCheckBox>
#include <QTableWidgetItem>


namespace Ui {
class AddcamWindow;
}

class AddcamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddcamWindow(QWidget *parent = nullptr);
    ~AddcamWindow();

private slots:


    void on_tableWidgetDisplayCameras_itemChanged(QTableWidgetItem *item);

private:
    Ui::AddcamWindow *ui;
    bool cameraDataLoaded;
    QSqlDatabase camdb;
    int currentId;
    bool showWidnow=false;

};

#endif // ADDCAMWINDOW_H
