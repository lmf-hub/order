#include "orderdetail.h"
#include "ui_orderdetail.h"
#include "orders.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
orderdetail::orderdetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderdetail)
{
    ui->setupUi(this);
}

orderdetail::~orderdetail()
{
    delete ui;
}

void orders::on_orderdetail_clicked()
{
    orderdetail*w=new orderdetail;
    w->show();
    w->setWindowTitle("订单详细信息");
    QSqlDatabase db=QSqlDatabase::database();
}


//选择订单号
void orderdetail::on_choose_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("select order_id from orders order by order_id");
        while (query.next())
        {
            QString order_id=query.value("order_id").toString();
            ui->order_id->addItem(order_id);
        }
}


//双击显示订单详情
void orderdetail::on_order_id_doubleClicked(const QModelIndex &index)
{
    QSqlDatabase db=QSqlDatabase::database();

        QListWidgetItem *current = ui->order_id->currentItem();
        if (current) {
            // 获取当前选中的订单号
            QString orderid = current->text();
            ui->detail->clear();
            ui->detail->addItem(orderid + "号订单:");
            QSqlQuery query(db);
            query.prepare("select * from orderdetail where order_id = :order_id");
            query.bindValue(":order_id", orderid);
            if (query.exec())
            {
                while (query.next())
                {
                    QString detail_id=query.value("detail_id").toString();
                    QString dish_id=query.value("dish_id").toString();
                    QString quantity=query.value("quantity").toString();
                    QString item=detail_id+" "+dish_id+"号菜品，数量："+quantity;
                    ui->detail->addItem(item);
                }
            }
            else {
                qDebug() << "查询失败:" << query.lastError().text();
            }
        }
        else {
            qDebug() << "没有选中的订单项";
        }
}
