#ifndef LOGINMAINWINDOW_H
#define LOGINMAINWINDOW_H

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
class LoginMainWindow;
}

class LoginMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginMainWindow(QWidget *parent = nullptr);
    ~LoginMainWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginMainWindow *ui;
    bool adminLogin=false;
    bool userLogin=false;
    QSqlDatabase logindb;
    MainWindow* openMain;
    UserWindow* openUser;

};

#endif // LOGINMAINWINDOW_H
