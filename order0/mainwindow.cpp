#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    QSqlQuery query(db);
    db= QSqlDatabase::addDatabase("QODBC");           //建立数据库连接
        db.setHostName("127.0.0.1");     // 主机名
        db.setPort(3306);               // 端口
        db.setDatabaseName("order");   // 数据库名
        db.setUserName("root");         // 用户名
        db.setPassword("123456");     // 密码
    if (!db.open())
       {
           qDebug()<<"database open failed!";
       }
       else
       {
           qDebug()<<"database open success!";
   }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}




