#include "userloginmainwindow.h"
#include "ui_userloginmainwindow.h"

UserLoginMainWindow::UserLoginMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserLoginMainWindow)
{
    ui->setupUi(this);

    ulogindb = QSqlDatabase::addDatabase("QSQLITE");
    ulogindb.setDatabaseName("F:/OnlyUsers.db");



            if (ulogindb.open())
            {
                qDebug() << "Connected!";
            }
            else
            {
                qDebug() << "Failed to connect.";
            }

}

UserLoginMainWindow::~UserLoginMainWindow()
{
    ulogindb.close();
    delete ui;

}

void UserLoginMainWindow::on_loginButton_clicked()
{
    QString username = ui->username->text();
        QString password = ui->password->text();

        qDebug() << username << password;


        if (ulogindb.open())
        {
            qDebug() << "Connected!";
        }
        else
        {
            qDebug() << "Failed to connect.";
        }

        QSqlQuery qTask(ulogindb);
 qTask.first();
        if(qTask.exec("SELECT* FROM backups"))
        {

           // qTask.exec("SELECT ,timestamp,  datetime('now')");
            while (qTask.next()){


                qDebug() << qTask.value(0) << qTask.value(1) << qTask.value(2);

                QString task =   qTask.value(0).toString();
               QString OperatorA = qTask.value(1).toString();
              QString timeS = qTask.value(2).toString();




              if(task==username &OperatorA==password &timeS=="1")
              {




                    QMessageBox::information(this, "Login success.", "Your The Boss!");


                    uopenMain = new MainWindow(this);
                    uopenMain->show();

                    userLogin=true;

                    QMessageBox::information(this, "Login success.", "Welcome Operator");

                    userLogin=true;

                    uopenUser = new UserWindow(this);
                   uopenUser->show();


                    break;
            }
            else if(task==username &OperatorA==password &timeS=="0")
            {

                  QMessageBox::information(this, "Login success.", "Welcome Operator");

                  userLogin=true;

                  uopenUser = new UserWindow(this);
                 uopenUser->show();

                break;
            }
               else
              {
                  QMessageBox::information(this, "Login failed.", "Login failed. Please try again...");

              }
                }


                }

}
