#include "dish.h"
#include "ui_dish.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
dish::dish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dish)
{
    ui->setupUi(this);
}

dish::~dish()
{
    delete ui;
}

void project::on_dish_clicked()
{
    dish*w=new dish;
    w->show();
    w->setWindowTitle("菜品");
    QSqlDatabase db=QSqlDatabase::database();
}

void dish::on_dish_show_clicked()
{
    ui->listWidget->clear();//清空上次查询内容
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    //利用combobox查询想要的菜品类型，默认全部菜品
    if(ui->category->currentText()=="素菜类"){
        query.exec("select dish_id,di_name,price from dish where category='素菜类'");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }
    }

    else if(ui->category->currentText()=="荤菜类"){
        query.exec("select dish_id,di_name,price from dish where category='荤菜类'");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }

    }
    else if(ui->category->currentText()=="汤类"){
        query.exec("select dish_id,di_name,price from dish where category='汤类'");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }

    }
    else if(ui->category->currentText()=="小吃类"){
        query.exec("select dish_id,di_name,price from dish where category='小吃类'");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }

    }
    else if(ui->category->currentText()=="饮品类"){
        query.exec("select dish_id,di_name,price from dish where category='饮品类'");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }

    }
    else if(ui->category->currentText()=="全部"){
        query.exec("select dish_id,di_name,price from dish");
        while (query.next())
        {
            QString dish_id= query.value("dish_id").toString();
            QString di_name= query.value("di_name").toString();
            QString price= query.value("price").toString();
            QString item=dish_id+" "+di_name+"  "+price;
            ui->listWidget->addItem(item);
        }

    }
    else {
        qDebug() << "查询失败:" << query.lastError().text();
    }
}


