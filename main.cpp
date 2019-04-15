#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
   // LoginForm l;
  //  l.show();
    return a.exec();
}
