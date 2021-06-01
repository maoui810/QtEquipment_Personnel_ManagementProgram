#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    UserTaskUpdated = false;


    userdb = QSqlDatabase::addDatabase("QSQLITE");
    userdb.setDatabaseName("filename");

    if (userdb.open())
    {
        QSqlQuery query;
        QSqlQuery queryAdd;
    qDebug()<<"Opened";
          query.prepare("SELECT ID,Task,OA,timestamp FROM Tasks INNER JOIN operators ON Tasks.OA = operators.NameA");
         qDebug() << query.lastError().text();
           query.first();
        if (query.exec("SELECT ID,Task,OA,timestamp FROM Tasks INNER JOIN operators ON Tasks.OA = operators.NameA"))
        {
             qDebug()<<"1";

            while (query.next())
            {

                qDebug() << query.value(0) << query.value(1) << query.value(2) <<query.value(3);


                QString id =   query.value(0).toString();
                QString name = query.value(1).toString();
                QString info = query.value(2).toString();

                 QString assigned = query.value(3).toString();
                // int sel= query.value(3).toInt();
                    qDebug()<<"2";
                 qDebug() << "INSERT INTO Opp (TaskA,NameA,Time) VALUES ('" + name + ",'" + info + "','" + assigned + "')";

                 QSqlQuery query;
                 if (queryAdd.exec("INSERT INTO Opp (TaskA,NameA,Time) VALUES ('" + name + ",'" + info + "','" + assigned + "')"))
                 {


                     qDebug() << "Insert success.";
                 }
                 else
                 {
                     qDebug() << query.lastError().text();
                 }




                ui->tableWidgetOp->setRowCount(ui->tableWidgetOp->rowCount() + 1);

                    QTableWidgetItem* idItem = new QTableWidgetItem(id);
                    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
                    QTableWidgetItem* infoItem = new QTableWidgetItem(info);

                     QTableWidgetItem* assItem= new QTableWidgetItem(assigned);


                        ui->tableWidgetOp->setItem(ui->tableWidgetOp->rowCount() -1,0,idItem);
                        ui->tableWidgetOp->setItem(ui->tableWidgetOp->rowCount() -1,1,nameItem);
                        ui->tableWidgetOp->setItem(ui->tableWidgetOp->rowCount() -1,2,infoItem);
                        ui->tableWidgetOp->setItem(ui->tableWidgetOp->rowCount() -1,3,assItem);

            }

            UserTaskUpdated=true;
        }
        else
        {
            qDebug() << query.lastError().text();
        }


    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }

}

UserWindow::~UserWindow()
{
    delete ui;
}




void UserWindow::on_pushButton_2_clicked()
{

    QSqlQuery aTask(userdb);



ui->tableWidgetOp_2->setRowCount(0);

// ui->tableWidget_2->setColumnHidden(0, true);
aTask.first();
   if(aTask.exec("SELECT ID,Name,Info,OperatorA FROM stock INNER JOIN operators ON stock.OperatorA = operators.NameA"))
   {



       while (aTask.next()){


           qDebug() << aTask.value(0) << aTask.value(1) << aTask.value(2)<<aTask.value(3);

           QString ID =   aTask.value(0).toString();
          QString NameOfEQ = aTask.value(1).toString();
         QString Info = aTask.value(2).toString();
         QString OPName = aTask.value(3).toString();


           ui->tableWidgetOp_2->setRowCount(ui->tableWidgetOp_2->rowCount() + 1);

               QTableWidgetItem* idItem = new QTableWidgetItem(ID);
               QTableWidgetItem* EQNameItem = new QTableWidgetItem(NameOfEQ);

                QTableWidgetItem* InfoItem= new QTableWidgetItem(Info);
                QTableWidgetItem* OPNameSItem= new QTableWidgetItem(OPName);

                   ui->tableWidgetOp_2->setItem(ui->tableWidgetOp_2->rowCount() -1,0,idItem);
                   ui->tableWidgetOp_2->setItem(ui->tableWidgetOp_2->rowCount() -1,1,EQNameItem);
                   ui->tableWidgetOp_2->setItem(ui->tableWidgetOp_2->rowCount() -1,2,InfoItem);
                       ui->tableWidgetOp_2->setItem(ui->tableWidgetOp_2->rowCount() -1,3,OPNameSItem);



       }


   }
   else
   {
        qDebug() << aTask.lastError().text();
   }


}
