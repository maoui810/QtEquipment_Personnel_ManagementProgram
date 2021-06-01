#include "addcamwindow.h"
#include "ui_addcamwindow.h"

AddcamWindow::AddcamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddcamWindow)
{
    ui->setupUi(this);


    cameraDataLoaded = false;
    ui->setupUi(this);

    camdb = QSqlDatabase::addDatabase("QSQLITE");
    camdb.setDatabaseName("F:/EQ.db");
    if (camdb.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT* FROM CameraData"))
        {
            while (query.next())
            {


                //ui->tableWidget->setColumnCount(4);
               // QStringList labels;
               // labels<<" "<<"ID"<<"Equipment Name"<<"Info"<<"Operator Assigned";
              //  ui->tableWidget->setHorizontalHeaderLabels(labels);

                qDebug() << query.value(0) << query.value(1)<<query.value(2);

                QString name =   query.value(0).toString();
                QString yearmade = query.value(1).toString();
                int check = query.value(2).toInt();



                ui->tableWidgetDisplayCameras->setRowCount(ui->tableWidgetDisplayCameras->rowCount() + 1);


                    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
                    QTableWidgetItem* yearItem = new QTableWidgetItem(yearmade);
                     QTableWidgetItem* checkItem = new QTableWidgetItem(check);

                    //connect(checkItem,changeEvent(),this,on_tableWidgetDisplayCameras_itemChanged(checkItem));
                        if(query.value(2).toInt()== 0)
                        {
                            checkItem->setCheckState(Qt::Unchecked);
                        }
                        else
                        {
                            checkItem->setCheckState(Qt::Checked);
                        }


                        ui->tableWidgetDisplayCameras->setItem(ui->tableWidgetDisplayCameras->rowCount() -1,0,nameItem);
                           ui->tableWidgetDisplayCameras->setItem(ui->tableWidgetDisplayCameras->rowCount() -1,1,yearItem);
                            ui->tableWidgetDisplayCameras->setItem(ui->tableWidgetDisplayCameras->rowCount() -1,2,checkItem);

            }
            cameraDataLoaded=true;
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

AddcamWindow::~AddcamWindow()
{

    delete ui;
}


















void AddcamWindow::on_tableWidgetDisplayCameras_itemChanged(QTableWidgetItem *item)
{
qDebug()<<"we are here";

    if(cameraDataLoaded){
    QSqlQuery Tquery;


    QString name = ui->tableWidgetDisplayCameras->item(item->row(), 0)->data(0).toString();

    QString YearMade = ui->tableWidgetDisplayCameras->item(item->row(), 1)->data(0).toString();
    int check = ui->tableWidgetDisplayCameras->item(item->row(), 2)->data(0).toInt();

    qDebug()<<name;
     qDebug()<<check;
    if(ui->tableWidgetDisplayCameras->item(item->row(),2)->checkState())
    {
        check=1;
    }


       if(Tquery.exec("UPDATE CameraData SET Name = '" + name + "', YearMade = '" + YearMade + "', check = '" + check + "' WHERE id = " + name))
                     {
                        QMessageBox::information(this,"Update Success","Data updated to database");
                     }
                     else
                     {
                         qDebug()<<Tquery.lastError().text();
                     }
}
    else
    {
     qDebug()<<"Didnt laod data";
    }


}
