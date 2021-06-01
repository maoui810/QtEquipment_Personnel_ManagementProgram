#ifndef USERLOGINMAINWINDOW_H
#define USERLOGINMAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QCheckBox>
#include <QTableWidgetItem>

#include "mainwindow.h"
#include "userwindow.h"

namespace Ui {
class UserLoginMainWindow;
}

class UserLoginMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserLoginMainWindow(QWidget *parent = 0);
    ~UserLoginMainWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::UserLoginMainWindow *ui;

    bool userLogin=false;
    QSqlDatabase ulogindb;
    MainWindow* uopenMain;
    UserWindow* uopenUser;

};

#endif // USERLOGINMAINWINDOW_H
