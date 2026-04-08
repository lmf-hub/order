#include "orders.h"
#include "ui_orders.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
orders::orders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orders)
{
    ui->setupUi(this);
}

orders::~orders()
{
    delete ui;
}

void project::on_orders_clicked()
{
    orders*w=new orders;
    w->show();
    w->setWindowTitle("订单");
    QSqlDatabase db=QSqlDatabase::database();
}

void orders::on_orders_show_clicked()
{
    ui->listWidget->clear();//清空上次查询内容
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    //利用combobox查询想要的菜品类型，默认全部菜品
    if(ui->status->currentText()=="已支付"){
        query.exec("select order_id,table_id,customer_id,total_price,"
                   "discount_rate,actual_price from orders where or_status='已支付'");
        while (query.next())
        {
            QString order_id,table_id,customer_id,total_price,discount_rate,actual_price;
            order_id= query.value("order_id").toString();
            table_id= query.value("table_id").toString();
            customer_id= query.value("customer_id").toString();
            total_price= query.value("total_price").toString();
            discount_rate= query.value("discount_rate").toString();
            actual_price= query.value("actual_price").toString();
            QString item=order_id+"号订单 "+table_id+"号桌"+customer_id+"号客人，总价"+total_price
                    +"，折扣："+discount_rate+"，实际总价："+actual_price;
            ui->listWidget->addItem(item);
        }
    }
    else if(ui->status->currentText()=="未支付"){
        query.exec("select order_id,table_id,customer_id,total_price,"
                   "discount_rate,actual_price from orders where or_status='未支付'");
        while (query.next())
        {
            QString order_id,table_id,customer_id,total_price,discount_rate,actual_price;
            order_id= query.value("order_id").toString();
            table_id= query.value("table_id").toString();
            customer_id= query.value("customer_id").toString();
            total_price= query.value("total_price").toString();
            discount_rate= query.value("discount_rate").toString();
            actual_price= query.value("actual_price").toString();
            QString item=order_id+"号订单 "+table_id+"号桌"+customer_id+"号客人，总价"+total_price
                    +"，折扣："+discount_rate+"，实际总价："+actual_price;
            ui->listWidget->addItem(item);
        }
    }
    else if(ui->status->currentText()=="全部"){
            query.exec("select order_id,table_id,customer_id,total_price,"
                       "discount_rate,actual_price from orders ");
            while (query.next())
            {
                QString order_id,table_id,customer_id,total_price,discount_rate,actual_price;
                order_id= query.value("order_id").toString();
                table_id= query.value("table_id").toString();
                customer_id= query.value("customer_id").toString();
                total_price= query.value("total_price").toString();
                discount_rate= query.value("discount_rate").toString();
                actual_price= query.value("actual_price").toString();
                QString item=order_id+"号订单 "+table_id+"号桌"+customer_id+"号客人，总价"+total_price
                        +"，折扣："+discount_rate+"，实际总价："+actual_price;
                ui->listWidget->addItem(item);
            }
        }
}




