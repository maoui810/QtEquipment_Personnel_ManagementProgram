#ifndef USERWINDOW_H
#define USERWINDOW_H

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

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private slots:


    void on_pushButton_2_clicked();

private:
    Ui::UserWindow *ui;
    bool UserTaskUpdated;
     QSqlDatabase userdb;
};

#endif // USERWINDOW_H
