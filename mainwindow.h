#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"managewidget.h"
#include"changewidget.h"
#include"findwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow//登录窗口，也是qt中的主窗口
{
    Q_OBJECT

public:
     //使用三个指针管理三个面板
    static ManageWidget *mw;
    static ChangeWidget *cw;
    static FindWidget *fw;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
