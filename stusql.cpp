#include "stusql.h"
#include<QDebug>
#include<QMessageBox>
#include<QCoreApplication>
#include<QApplication>
StuSql::StuSql(QObject *parent) : QObject(parent)
{
  //查找驱动
if(QSqlDatabase::drivers().isEmpty())
{
    QMessageBox::warning(NULL,tr("警告"),tr("驱动找不到"));

}
else
{
     this->init();
}
}
void StuSql::init()
{
    //先获取exe文件的父级路径，加上"/data.db"就是我们所设置的sql数据库的绝对路径，在程序打包后，用户不需要考虑路径就可以正常连接数据库
   QString path=  QCoreApplication::applicationDirPath()+"/data.db";
  // qDebug()<<path;
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    //根据路径连接数据库
    db.setDatabaseName(path);
    if(db.open())
    {
        qDebug()<<"open success";

    }
    else
    {
        qDebug()<<"open failed";

    }
}
