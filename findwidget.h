#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QMainWindow>

namespace Ui {
class FindWidget;
}

class FindWidget : public QMainWindow//查找和删除信息的窗口
{
    Q_OBJECT

public:
    explicit FindWidget(QWidget *parent = nullptr);
    ~FindWidget();
    //查找信息的函数
    void find();
    //删除信息的函数
    void deletenStu();
private slots:
    void on_pushButton_2_clicked();

    void on_button_find_clicked();

    void on_button_delete_clicked();

private:
    Ui::FindWidget *ui;
};

#endif // FINDWIDGET_H
