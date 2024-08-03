#ifndef CHANGEWIDGET_H
#define CHANGEWIDGET_H

#include <QMainWindow>
#include "ui_changewidget.h"
#include<qspinbox.h>
#include<QString>
#include<QMessageBox>
#include<QSqlQueryModel>
#include"managewidget.h"
#include<QDebug>
namespace Ui {
class ChangeWidget;
}

class ChangeWidget : public QMainWindow//添加和修改信息的窗口
{
    Q_OBJECT

public:
    explicit ChangeWidget(QWidget *parent = nullptr);
    ~ChangeWidget();
    //添加和修改信息的函数
   void change();

private slots:

   void on_pushButton_no_clicked();

   void on_pushButton_ok_clicked();

private:
    Ui::ChangeWidget *ui;
};

#endif // CHANGEWIDGET_H
