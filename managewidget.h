#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QMainWindow>

namespace Ui {
class ManageWidget;
}

class ManageWidget : public QMainWindow//管理窗口
{
    Q_OBJECT

public:

    explicit ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();
    //更新tableview中表的函数
   void tableupdate();
   //排序所用的函数
   void order();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_exit_clicked();

    void search();

    void on_pushButton_startOrder_clicked();

    void on_pushButton_clearAll_clicked();

private:
    Ui::ManageWidget *ui;
};

#endif // MANAGEWIDGET_H
