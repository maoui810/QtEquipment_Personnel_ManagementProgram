#include "mainwindow.h"
#include "userwindow.h"
#include <QApplication>
#include "addcamwindow.h"
#include "loginmainwindow.h"
#include "userloginmainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//LoginMainWindow b;
//b.show();
UserLoginMainWindow d;
//UserLoginMainWindow f;
d.show();
//f.show();




  // MainWindow w;
 // UserWindow u;


  // w.show();
 // u.show();


    return a.exec();
}
