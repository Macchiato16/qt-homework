#include "managewidget.h"
#include "ui_managewidget.h"
#include<QSqlQueryModel>
#include"changewidget.h"
#include"findwidget.h"
#include"mainwindow.h"
ManageWidget::ManageWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageWidget)
{
    ui->setupUi(this);
    //设置窗口图标
    setWindowIcon(QIcon(":/image/cuc.png"));
    //设置状态栏
    QStatusBar * statusbar=new QStatusBar;
    setStatusBar(statusbar);
    //为状态栏添加文字
    QLabel *label1=new QLabel("cuc数媒技某学生制作，仅供参考，大佬勿喷TVT",this);
    statusbar->addWidget(label1);

    //首次初始化
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    //创建sql语句
    sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    model->setQuery(sql);
    //将获取到的model设置出来，就完成了表格的显示
    ui->tableView->setModel(model);
    //将search函数与输入框字符串变化的信号相连接，就可以进行实时模糊搜索
   connect(ui->lineEdit_name,SIGNAL(textChanged(QString)),this,SLOT(search()));
}
 void ManageWidget::tableupdate()
{
     //以后的更新每次都需要将之前的model释放掉
     //记录旧的model
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    //重新从数据库中获取表格
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    model->setQuery(sql);
    ui->tableView->setModel(model);
    //将旧的model删除
    delete oldmodel;
}
ManageWidget::~ManageWidget()
{
    delete ui;
}
 //点击添加修改按钮时调用的槽函数
void ManageWidget::on_pushButton_2_clicked()
{
   //让changwidget显示
   MainWindow::cw->show();
   //MainWindow::cw->setAttribute(Qt::WA_DeleteOnClose);
}
//点击精准查找按钮调用的槽函数
void ManageWidget::on_pushButton_5_clicked()
{
    //findwidget显示
   MainWindow::fw->show();
   //MainWindow::fw->setAttribute(Qt::WA_DeleteOnClose);
}


void ManageWidget::search()//将此函数与输入框字符串变化相连接，就可以实时模糊搜索
{
    //qDebug()<<"正在查找";
    //首先获取查找内容
    QString findname=ui->lineEdit_name->text();
    //如果为空，则直接刷新完整表格，不进行查找
    if(findname.isEmpty())
    {
        MainWindow::mw->tableupdate();
        return ;
    }
    //如果不为空，则进行模糊查找
    //同样需要记录旧的model
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student where name like '%"+findname+"%'";
    model->setQuery(sql);
    ui->tableView->setModel(model);
    //删除旧的model
    delete  oldmodel;
}

void ManageWidget::order()
{
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    //学号和绩点，升序和降序组合出四种情况，根据不同的情况定义要执行的sql语句
    //选择学号降序
    if(ui->comboBox->currentText()=="学号"&&ui->button_reverse->isChecked())
    {
        sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student order by stuid desc";
    }
    //选择学号升序
    else if(ui->comboBox->currentText()=="学号"&&!ui->button_reverse->isChecked())
    {
        sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student order by stuid";
    }
    //选择绩点降序
    else if(ui->comboBox->currentText()=="绩点"&&ui->button_reverse->isChecked())
    {
        sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student order by GPA desc";
    }
    //选择绩点升序
    else if(ui->comboBox->currentText()=="绩点"&&!ui->button_reverse->isChecked())
    {
        sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student order by GPA";
    }
    //执行sql语句后设置表格
    model->setQuery(sql);
    ui->tableView->setModel(model);
    delete  oldmodel;
}
void ManageWidget::on_pushButton_exit_clicked()
{
    //点击退出按钮，程序退出
   exit(0);
}
//点击开始排序按钮，调用排序函数
void ManageWidget::on_pushButton_startOrder_clicked()
{
    order();
}

void ManageWidget::on_pushButton_clearAll_clicked()
{
    //删除时，弹出两次消息窗口来确认，以防误删除
    if(QMessageBox::Yes==QMessageBox::question(this,"注意","是否删除所有数据"))
    {
        if(QMessageBox::Yes==QMessageBox::question(this,"注意","请再次确认是否删除所有数据"))
        {
            //将数据库全部清空，但保留表的结构
            QSqlQueryModel *model=new QSqlQueryModel;
            QString sql="delete from student";
            //qDebug()<<"表清空";
            model->setQuery(sql);
            delete model;
            MainWindow::mw->tableupdate();
        }
    }
}
