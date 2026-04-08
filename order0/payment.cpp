#include "payment.h"
#include "ui_payment.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
payment::payment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
}

payment::~payment()
{
    delete ui;
}

void project::on_payment_clicked()
{
    payment*w=new payment;
    w->show();
    w->setWindowTitle("结账");
    QSqlDatabase db=QSqlDatabase::database();
}

//确认订单内容
void payment::on_ensure_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    ui->listWidget->clear();
    int order_id=ui->lineEdit->text().toInt();
    ui->listWidget->addItem(QString::number(order_id) + "号订单:");
    QSqlQuery query(db);
    query.prepare("select * from orderdetail where order_id = :order_id");
    query.bindValue(":order_id", order_id);
    if (query.exec())
    {
        while (query.next())
        {
            QString detail_id=query.value("detail_id").toString();
            QString dish_id=query.value("dish_id").toString();
            QString quantity=query.value("quantity").toString();
            QString item=detail_id+" "+dish_id+"号菜品，数量："+quantity;
            ui->listWidget->addItem(item);
        }
    }
    else {
        qDebug() << "查询失败:" << query.lastError().text();
    }
    QSqlQuery query2(db);
    query2.prepare("select actual_price from orders where order_id=:order_id");
    query2.bindValue(":order_id", order_id);
    query2.exec();
    while (query2.next())
    {
        QString actual_price= query2.value("actual_price").toString();
        QString item="实际总价："+actual_price;
        ui->listWidget->addItem(item);
    }
}

//支付
void payment::on_pay_clicked()
{
    int order_id=ui->lineEdit->text().toInt();
    QSqlQuery query;
    query.prepare("UPDATE orders SET or_status=:or_status WHERE order_id=:order_id");
    query.bindValue(":or_status", "已支付");
    query.bindValue(":order_id", order_id);
    if(query.exec())
    {
        QMessageBox::information(this, "提示", "支付成功！");
    }
    else QMessageBox::information(this, "警告", "支付失败！");
}


