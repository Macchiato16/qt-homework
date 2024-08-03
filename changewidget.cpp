#include "changewidget.h"
#include"mainwindow.h"
ChangeWidget::ChangeWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/cuc.png"));
    ui->groupBox->setStyleSheet("QGroupBox{border:none}");
    ui->groupBox_2->setStyleSheet("QGroupBox{border:none}");
    //设置id和phone的输入只能为整数
    ui->lineEdit_id->setValidator(new QIntValidator( NULL));
    ui->lineEdit_phone->setValidator(new QIntValidator( NULL));

}
void ChangeWidget::change()
{
//点击的是添加按钮
    if(ui->button_add->isChecked())
    {
        //把数据全部获取到
        QString id=ui->lineEdit_id->text();
        QString name=ui->lineEdit_name->text();
        QString stuclass=ui->lineEdit_class->text();
        QString phone=ui->lineEdit_phone->text();
        int age=ui->spinBox_age->value();
        double gpa=ui->doubleSpinBox_gpa->value();
        QString gender;
        //根据点击的按钮来确认性别信息
        if(ui->radioButton_male->isChecked())
        {
            gender="男";

        }
        else
        {
            gender="女";
        }

        //添加学生时，必须保证每个信息不为空
        //没有默认信息的地方如果有一个为空，则直接打回去
        if(id.isEmpty()||name.isEmpty()||stuclass.isEmpty()||phone.isEmpty())
        {

            QMessageBox::about(NULL,"注意","请把信息补充完整");
        }
        //信息完整时
        else
        {
            //添加时，首先检测表中是否存在学号相同的学生（姓名可以相同，学号不能相同）
            QString sql1;
            sql1="select count (*) from student where stuid='%1'";
            QSqlQueryModel *model1=new QSqlQueryModel;
            model1->setQuery(sql1.arg(id));
            QModelIndex index1=model1->index(0,0);
            //找到有相同学号的学生后，提醒不能添加
            if(index1.data()!=0)
            {
                QMessageBox::about(NULL,"添加失败","系统中已有学号相同的学生");
                return;
            }
            //没找到就开始添加
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="insert into student values ('%1','%2',%3,'%4','%5',%6,'%7')";
            model->setQuery(sql.arg(name).arg(id).arg(age).arg(gender).arg(stuclass).arg(gpa).arg(phone));
            //重新刷新信息
            MainWindow::mw->tableupdate();

            QMessageBox::about(NULL,"提示","系统信息添加成功");
        }
    }
    //点击的是修改按钮
    else
    {
        //由于姓名可能重复，只能根据学号修改信息，包括姓名也是可以修改的（可能有人改名）
        //同样检测是否存在
        QString id=ui->lineEdit_id->text();
        QString sql1;
        sql1="select count (*) from student where stuid='%1'";
        QSqlQueryModel *model1=new QSqlQueryModel;
        model1->setQuery(sql1.arg(id));
        QModelIndex index1=model1->index(0,0);
        //如果找不到该学号的学生，就提示一下并返回
        if(index1.data()==0)
        {
            QMessageBox::about(NULL,"修改失败","系统中找不到该学号的学生");
            return;
        }
        //如果找到了，获取剩余数据，由于修改可以不修改所有值，所以只对输入的内容修改，年龄，绩点，性别等默认有输入值，年龄，绩点为默认值0时认为不修改
        QString name=ui->lineEdit_name->text();
        QString stuclass=ui->lineEdit_class->text();
        QString phone=ui->lineEdit_phone->text();
        int age=ui->spinBox_age->value();
        double gpa=ui->doubleSpinBox_gpa->value();
        QString gender;
        if(ui->radioButton_male->isChecked())
        {
            gender="男";

        }
        else
        {
            gender="女";
        }
        //开始修改
        //只有信息不为空时才修改
        if(!name.isEmpty())
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set name='%1' where stuid='%2'";
            model->setQuery(sql.arg(name).arg(id));
            delete model;
            qDebug()<<1;
        }
        if(age!=0)
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set age=%1 where stuid='%2'";
            model->setQuery(sql.arg(age).arg(id));
             delete model;
           qDebug()<<2;
        }
        if(true)//为了整齐>_<
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set gender='%1' where stuid='%2'";
            model->setQuery(sql.arg(gender).arg(id));
            delete model;
            qDebug()<<3;
        }
        if(!stuclass.isEmpty())
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set Stuclass='%1' where stuid='%2'";
            model->setQuery(sql.arg(stuclass).arg(id));
            delete model;
            qDebug()<<4;
        }
        if(gpa!=0)
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set GPA=%1 where stuid='%2'";
            model->setQuery(sql.arg(gpa).arg(id));
            delete model;
            qDebug()<<5;
        }
        if(!phone.isEmpty())
        {
            QString sql;
            QSqlQueryModel *model=new QSqlQueryModel;
            sql="update student set phone='%1' where stuid='%2'";
            model->setQuery(sql.arg(phone).arg(id));
            delete model;
           qDebug()<<6;
        }
        //重新刷新信息
        MainWindow::mw->tableupdate();
        QMessageBox::about(NULL,"提示","系统信息修改成功");
    }
}
ChangeWidget::~ChangeWidget()
{
    delete ui;
}



void ChangeWidget::on_pushButton_no_clicked()
{
    //点击退出按钮就隐藏
    hide();
}

void ChangeWidget::on_pushButton_ok_clicked()
{
    //点击确认按钮就进行修改
   this->change();
}
