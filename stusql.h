#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include<qsqldatabase.h>
class StuSql : public QObject//管理数据库的类
{
    Q_OBJECT
public:
    explicit StuSql(QObject *parent = nullptr);
    //初始化连接数据库的函数
    void init();
signals:

};

#endif // STUSQL_H
