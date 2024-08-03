#include "mainwindow.h"
#include"stusql.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StuSql sql;
    //创建一个mainwindow，其他三个窗口也被创建
    MainWindow w;
    w.show();
    return a.exec();
}
