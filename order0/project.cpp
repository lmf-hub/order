#include "project.h"
#include "ui_project.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmessagebox.h>
project::project(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::project)
{
    ui->setupUi(this);

}

void MainWindow::on_welcome_clicked()
{
    bool check=ui->password->text().isEmpty();
    QString code=ui->password->text();
    QString mycode="123456";
    if(!check){
        if(code==mycode){
            project*w=new project;
            w->show();
            w->setWindowTitle("操作菜单");
            QSqlDatabase db=QSqlDatabase::database();
            this->hide();//隐藏这个界面
        }
        else QMessageBox::information(this, "警告", "密码错误！");
    }
    else QMessageBox::information(this, "警告", "密码不能为空！");

}

project::~project()
{
    delete ui;
}
