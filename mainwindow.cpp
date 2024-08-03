#include "mainwindow.h"
#include "ui_mainwindow.h"
//为静态变量赋初值
ManageWidget* MainWindow::mw=NULL;
ChangeWidget* MainWindow::cw=NULL;
FindWidget* MainWindow::fw=NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //为窗口设置图标（图标是cuc校徽）
    setWindowIcon(QIcon(":/image/cuc.png"));
    //设置一个状态栏，默认在下部
    QStatusBar * statusbar=new QStatusBar;
    setStatusBar(statusbar);
    //为状态栏添加文字
    QLabel *label1=new QLabel("cuc数媒技某学生制作，仅供参考，大佬勿喷TVT",this);
    statusbar->addWidget(label1);
    //使用三个指针管理三个面板
    MainWindow::mw=new ManageWidget;
    MainWindow::cw=new ChangeWidget;
    MainWindow::fw=new FindWidget;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    //点击退出按钮时，程序退出
   exit(0);
}
//登录功能
void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text()=="cucadmin"&&ui->lineEdit_password->text()=="cucadmin")
    {
        QMessageBox::about(this,"提示","登陆成功");
        MainWindow::mw->show();
        //MainWindow::mw->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
    }
    else
    {
        QMessageBox::about(NULL,"提示","账号或者密码错误");
    }

}
