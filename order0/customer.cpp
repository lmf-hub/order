#include "customer.h"
#include "ui_customer.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
customer::customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customer)
{
    ui->setupUi(this);

}

void project::on_customer_clicked()
{
    customer*w=new customer;
    w->show();
    w->setWindowTitle("vip顾客名单");
    QSqlDatabase db=QSqlDatabase::database();
}

//查询顾客信息
void customer::on_show_coustomer_clicked()
{
    ui->listWidget->clear();//清空上次查询内容
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("select * from customer ");
    while (query.next())
    {
        QString customer_id= query.value("customer_id").toString();
        QString name= query.value("name").toString();
        QString phone= query.value("phone").toString();
        QString vip_level=query.value("vip_level").toString();
        QString discount_rate=query.value("discount_rate").toString();
        QString item=customer_id+"号 "+name+"  "+phone+"  vip"+vip_level+"  discount_rate"+discount_rate;
        ui->listWidget->addItem(item);

    }
}

//顾客退卡则删除该顾客信息
void customer::on_delete_vip_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query;
    QListWidgetItem *current = ui->listWidget->currentItem();
    if (current) {
            // 获取当前选中的顾客id
            QString text= current->text();
            int customer_id;
            QRegularExpression re("^(\\d+)号");//由于listWidget中信息存储按照"X号"，因此可以这样获取
            QRegularExpressionMatch match = re.match(text);
            if (match.hasMatch()) {
                 customer_id = match.captured(1).toInt();
                }
    query.prepare("DELETE FROM customer WHERE customer_id= :customer_id");
    query.bindValue(":customer_id", customer_id);
    if(query.exec())
    {
        QMessageBox::information(this, "提示", "退卡成功！");
    }
    else QMessageBox::information(this, "警告", "退卡失败！");
    }
}

//办理vip卡
void customer::on_open_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    //顾客id生成：前一个id递增
    QSqlQuery query("select max(customer_id) from customer");
    int id=0;
    if(query.next()) {
        id=query.value(0).toInt();
    }
    int customer_id=id+1;
    QString name=ui->name->text();
    QString phone=ui->phone->text();
    QSqlQuery query2;
    query2.prepare("insert into customer(customer_id,name,phone,vip_level,discount_rate) "
                   "values (:customer_id,:name,:phone,:vip_level,:discount_rate)");
    query2.bindValue(":customer_id", customer_id);
    query2.bindValue(":name", name);
    query2.bindValue(":phone",phone);
    query2.bindValue(":vip_level",1);
    query2.bindValue(":discount_rate",0.95);
    if(query2.exec())
    {
        QMessageBox::information(this, "提示", "开卡成功！");
    }
    else QMessageBox::information(this, "警告", "开卡失败！");

}

customer::~customer()
{
    delete ui;
}
