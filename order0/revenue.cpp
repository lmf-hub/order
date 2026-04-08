#include "revenue.h"
#include "ui_revenue.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
revenue::revenue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::revenue)
{
    ui->setupUi(this);
}

revenue::~revenue()
{
    delete ui;
}

void project::on_revenue_clicked()
{
    revenue*w=new revenue;
    w->show();
    w->setWindowTitle("营收");
    QSqlDatabase db=QSqlDatabase::database();
}

void revenue::on_check_clicked()
{
    ui->textEdit->clear();
    // 验证日期输入
        if (ui->start->date() > ui->end->date()) {
            ui->textEdit->setText("错误：结束日期不能早于开始日期");
            return;
        }
    QSqlQuery query;
    // 调用存储结构
    if (!query.prepare("CALL revenue(:start_date, :end_date)")) {
        qDebug() << "Prepare failed:" << query.lastError().text();
        return;
    }
    QDate start_date=ui->start->date();
    QDate end_date=ui->end->date();
    query.bindValue(":start_date",start_date.toString("yyyy-MM-dd"));
    query.bindValue(":end_date",end_date.toString("yyyy-MM-dd"));
    if (!query.exec())
    {
        qDebug() << "调用存储过程失败:" << query.lastError().text();
        return;
    }
    query.exec("SELECT @order_quantity as order_quantity,@total_revenue as total_revenue");
    if (query.next())
    {
        int order_quantity=query.value(0).toInt();
        double total_revenue=query.value(1).toDouble();
        QString item = QString("订单总数：%1\n总收入：%2元")
                          .arg(order_quantity)
                          .arg(total_revenue, 0, 'f', 2); // 保留两位小数
        ui->textEdit->setText(item);
    }
}

void revenue::on_Summary_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    ui->listWidget->clear();
    QDate start_date=ui->start->date();
    QDate end_date=ui->end->date();
    QSqlQuery query(db);
    query.prepare("select orders.order_id,order_date,price,di_name,quantity "
                  "from orders join orderdetail on orders.order_id = orderdetail.order_id "
                  "join dish on dish.dish_id = orderdetail.dish_id "
                  "where order_date between :start_date and :end_date "
                  "order by orders.order_id" );
    query.bindValue(":start_date",start_date.toString("yyyy-MM-dd"));
    query.bindValue(":end_date",end_date.toString("yyyy-MM-dd"));
    if (query.exec())
    {
        while (query.next())
        {
            QString order_id=query.value("order_id").toString();
            QString order_date=query.value("order_date").toString();
            QString price=query.value("price").toString();
            QString di_name=query.value("di_name").toString();
            QString quantity=query.value("quantity").toString();
            QString item=order_id+" "+order_date+" "+price+"元 "+di_name+" "+quantity+"份";
            ui->listWidget->addItem(item);
        }
    }
    else {
        qDebug() << "查询失败:" << query.lastError().text();
    }
}
