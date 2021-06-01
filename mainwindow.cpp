#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcamwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    hasInit = false;
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("F:/EQ.db");

    if (db.open())
    {
        QSqlQuery query;


        if (query.exec("SELECT* FROM stock"))
        {
            while (query.next())
            {


                //ui->tableWidget->setColumnCount(4);
               // QStringList labels;
               // labels<<" "<<"ID"<<"Equipment Name"<<"Info"<<"Operator Assigned";
              //  ui->tableWidget->setHorizontalHeaderLabels(labels);

                qDebug() << query.value(0) << query.value(1) << query.value(2) <<query.value(3);


                QString id =   query.value(0).toString();
                QString name = query.value(1).toString();
                QString info = query.value(2).toString();

                 QString assigned = query.value(3).toString();
                // int sel= query.value(3).toInt();


                ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

                    QTableWidgetItem* idItem = new QTableWidgetItem(id);
                    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
                    QTableWidgetItem* infoItem = new QTableWidgetItem(info);

                     QTableWidgetItem* assItem= new QTableWidgetItem(assigned);


                        ui->tableWidget->setItem(ui->tableWidget->rowCount() -1,0,idItem);
                        ui->tableWidget->setItem(ui->tableWidget->rowCount() -1,1,nameItem);
                        ui->tableWidget->setItem(ui->tableWidget->rowCount() -1,2,infoItem);
                        ui->tableWidget->setItem(ui->tableWidget->rowCount() -1,3,assItem);

            }
            hasInit=true;
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

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{

    if(hasInit)
    {
         QString id = ui->tableWidget->item(item->row(), 0)->data(0).toString();

         QString name = ui->tableWidget->item(item->row(), 1)->data(0).toString();
         QString info = ui->tableWidget->item(item->row(), 2)->data(0).toString();
         QString assigned = ui->tableWidget->item(item->row(), 3)->data(0).toString();



             qDebug()<<id<<name<<info<<assigned;

             QSqlQuery query;

             if(query.exec("UPDATE stock SET Name = '" + name + "', Info = '" + info + "', OperatorA = '" + assigned + "' WHERE id = " + id))
             {
                QMessageBox::information(this,"Update Success","Data updated to database");
             }
             else
             {
                 qDebug()<<query.lastError().text();
             }





    }
    else
    {
     qDebug()<<"Didnt laod data";
    }



}

void MainWindow::on_cameraData_clicked()
{


    addCam = new AddcamWindow(this);
    addCam->show();


}



void MainWindow::on_AddEQ_clicked()
{

    if(taskInit){

        QString name= ui->task->text();
        QString info=ui->OP->text();
        //QString op=ui->time->text();
        QDateTime time=QDateTime::currentDateTime();
        QString s=time.toString();
        qDebug()<<"Entering time check: ";
        qDebug()<<s;
        qDebug() << "INSERT INTO Tasks (Task,OA,timestamp) VALUES ('" + name + ",'" + info + "','" + s + "')";

         QSqlQuery query;
         if (query.exec("INSERT INTO Tasks (Task,OA,timestamp) VALUES ('" + name + "','" + info + "','" + s + "')"))
         {


             qDebug() << "Insert success.";
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






void MainWindow::on_Loaddata_clicked()
{

     QSqlQuery qTask(db);
     QSqlQuery qOper(db);


ui->tableWidget_2->setRowCount(0);

 // ui->tableWidget_2->setColumnHidden(0, true);
    if(qTask.exec("SELECT Task,OA,timestamp FROM Tasks"))
    {
        qOper.exec("SELECT Name,FROM operators");

  //  qTask.prepare("SELECT source, datetime(timestamp");
       // qTask.exec("SELECT ,timestamp,  datetime('now')");
        while (qTask.next()){


            qDebug() << qTask.value(0) << qTask.value(1) << qTask.value(2);
        QString avaOP =   qOper.value(0).toString();

            QString task =   qTask.value(0).toString();
           QString OperatorA = qTask.value(1).toString();
          QString timeS = qTask.value(2).toString();

            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount() + 1);

                QTableWidgetItem* taskItem = new QTableWidgetItem(task);

                 QTableWidgetItem* OperatorAItem= new QTableWidgetItem(OperatorA);
                 QTableWidgetItem* timeSItem= new QTableWidgetItem(timeS);

                    ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() -1,1,taskItem);
                    ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() -1,2,OperatorAItem);
                    ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() -1,3,timeSItem);
                    if(avaOP==OperatorA)
                    {
                        qOper.exec("INSERT INTO Opp (Task,Name,Time) VALUES ('" + task + "','" + OperatorA + "','" + timeS + "')");
                    }


        }
        taskInit=true;

    }
    else
    {
         qDebug() << qTask.lastError().text();
    }

}

