#include "loginmainwindow.h"
#include "ui_loginmainwindow.h"


LoginMainWindow::LoginMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginMainWindow)
{
    ui->setupUi(this);

    logindb = QSqlDatabase::addDatabase("QSQLITE");
    logindb.setDatabaseName("F:/checkUser.db");



            if (logindb.open())
            {
                qDebug() << "Connected!";
            }
            else
            {
                qDebug() << "Failed to connect.";
            }


}

LoginMainWindow::~LoginMainWindow()
{
    delete ui;
}

void LoginMainWindow::on_loginButton_clicked()
{

    QString username = ui->username->text();
        QString password = ui->password->text();

        qDebug() << username << password;


        QSqlQuery qTask("SELECT* FROM Users",logindb);
        qDebug()<<qTask.lastError().text();
        qTask.first();
        if(qTask.exec())
        {

qDebug() << qTask.value(0) << qTask.value(1) << qTask.value(2);
            while (qTask.next()){




                QString task =   qTask.value(0).toString();
               QString OperatorA = qTask.value(1).toString();
              QString timeS = qTask.value(2).toString();




              if(task==username &OperatorA==password &timeS=="1")
              {




                    QMessageBox::information(this, "Login success.", "Your The Boss!");

                    adminLogin=true;

                    openMain = new MainWindow(this);
                    openMain->show();
                    QMessageBox::information(this, "Login success.", "Welcome Operator");


                    break;
            }
            else if(task==username &OperatorA==password &timeS=="0")
            {

                  QMessageBox::information(this, "Login success.", "Welcome Operator");

                  userLogin=true;

                  openUser = new UserWindow(this);
                  openUser->show();
                break;
            }
               else
              {
                  QMessageBox::information(this, "Login failed.", "Login failed. Please try again...");

              }
                }


                }
        qTask.finish();
}
