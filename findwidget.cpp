#include "findwidget.h"
#include "ui_findwidget.h"
#include<QSqlQueryModel>
#include<QMessageBox>
#include"mainwindow.h"
FindWidget::FindWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/cuc.png"));
//在findwidget里也有一个tableview，在打开时也初始化一下
    //首次初始化
    QSqlQueryModel *model=new QSqlQueryModel;
    QString sql;
    //创建sql语句
    sql="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    model->setQuery(sql);
    ui->tableView->setModel(model);
}

FindWidget::~FindWidget()
{
    delete ui;
}

void FindWidget::on_pushButton_2_clicked()
{
    //点击退出按钮则把窗口隐藏
    hide();
}
//精准查找所用的函数
void FindWidget::find()
{

    //先获取输入框信息
QString name=ui->lineEdit_name->text();
QString id=ui->lineEdit_id->text();
//姓名和id都不为空时
if(!name.isEmpty()&&!id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where name='%1' and stuid='%2'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(name).arg(id));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(NULL,"失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则进行查找并显示
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql2="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student where name='%1' and stuid='%2'";
    QSqlQueryModel *model2=new QSqlQueryModel;
    model2->setQuery(sql2.arg(name).arg(id));
    ui->tableView->setModel(model2);
    delete oldmodel;

}
//姓名不为空，id为空时
else if(!name.isEmpty()&&id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where name='%1'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(name));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(NULL,"失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则进行查找并显示
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql2="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student where name='%1'";
    QSqlQueryModel *model2=new QSqlQueryModel;
    model2->setQuery(sql2.arg(name));
    ui->tableView->setModel(model2);
    delete oldmodel;
}
//姓名为空，id不为空时
else if(name.isEmpty()&&!id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where stuid='%1'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(id));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(NULL,"失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则进行查找并显示
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql2="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student where stuid='%1'";
    QSqlQueryModel *model2=new QSqlQueryModel;
    model2->setQuery(sql2.arg(id));
    ui->tableView->setModel(model2);
    delete oldmodel;
}
//最后一种情况，什么信息都没有填写，直接打回去
else
{
    QMessageBox::about(NULL,"注意","请至少填写一个信息");
}

}
//查找并删除用到的函数
void FindWidget::deletenStu()
{
   //以下内容由find函数拷贝并修改
  //先获取信息
QString name=ui->lineEdit_name->text();
QString id=ui->lineEdit_id->text();
//姓名和id都不为空时
if(!name.isEmpty()&&!id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where name='%1' and stuid='%2'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(name).arg(id));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(NULL,"删除失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则先确认是否进行删除
    //如果用户选择了No，则直接返回
    if(QMessageBox::No==QMessageBox::question(this,"注意","是否确认删除"))
    {
        return ;
    }
    //选择Yes的话，直接删除
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString sql2="delete from student where name='%1' and stuid='%2'";
    model2->setQuery(sql2.arg(name).arg(id));
    delete model2;
    //删除成功后重新初始化表格
    MainWindow::mw->tableupdate();
    QMessageBox::about(NULL,"提示","删除成功");
    //查找窗口的表格重新刷新
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql3="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    QSqlQueryModel *model3=new QSqlQueryModel;
    model3->setQuery(sql3);
    ui->tableView->setModel(model3);
    delete oldmodel;
  // qDebug()<<1;


}
//姓名不为空，id为空时
else if(!name.isEmpty()&&id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where name='%1'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(name));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(NULL,"失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则先确认是否进行删除
    //如果用户选择了No，则直接返回
    if(QMessageBox::No==QMessageBox::question(this,"注意","是否确认删除"))
    {
        return ;
    }
    //选择Yes的话，直接删除
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString sql2="delete from student where name='%1'";
    model2->setQuery(sql2.arg(name));
    delete model2;
    //删除成功后重新初始化表格
    MainWindow::mw->tableupdate();
    QMessageBox::about(NULL,"提示","删除成功");
    //查找窗口的表格重新刷新
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql3="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    QSqlQueryModel *model3=new QSqlQueryModel;
    model3->setQuery(sql3);
    ui->tableView->setModel(model3);
    delete oldmodel;
    //qDebug()<<2;
}
//姓名为空，id不为空时
else if(name.isEmpty()&&!id.isEmpty())
{
    //先根据信息查找该学生
    QString sql1;
    sql1="select count (*) from student where stuid='%1'";
    QSqlQueryModel *model1=new QSqlQueryModel;
    model1->setQuery(sql1.arg(id));
    QModelIndex index1=model1->index(0,0);
    if(index1.data()==0)
    {
        //找不到提示一下后返回
        QMessageBox::about(this,"失败","系统中找不到该学生");
         delete model1;
        return;
    }
     delete model1;
    //如果找到了，则先确认是否进行删除
    //如果用户选择了No，则直接返回
    if(QMessageBox::No==QMessageBox::question(this,"注意","是否确认删除"))
    {
        return ;
    }
    //选择Yes的话，直接删除
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString sql2="delete from student where stuid='%1'";
    model2->setQuery(sql2.arg(id));
    delete model2;
    //删除成功后重新初始化表格
    MainWindow::mw->tableupdate();
    QMessageBox::about(this,"提示","删除成功");
    //查找窗口的表格重新刷新
    QItemSelectionModel *oldmodel=ui->tableView->selectionModel();
    QString sql3="select name as 姓名,stuid as 学号,age as 年龄,gender as 性别,Stuclass as 班级, GPA as 绩点,phone as 电话 from student";
    QSqlQueryModel *model3=new QSqlQueryModel;
    model3->setQuery(sql3);
    ui->tableView->setModel(model3);
    delete oldmodel;
    //qDebug()<<3;
}
//最后一种情况，什么信息都没有填写，直接打回去
else
{
    QMessageBox::about(NULL,"注意","请至少填写一个信息");
}
}

void FindWidget::on_button_find_clicked()
{
    //点击查找按钮，则执行查找函数
    find();
}

void FindWidget::on_button_delete_clicked()
{
    //点击删除按钮，则执行删除函数
    deletenStu();
}
