#include "queue.h"
#include "ui_queue.h"
#include "orderdish.h"
#include "ui_orderdish.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
queue::queue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queue)
{
    ui->setupUi(this);
}

queue::~queue()
{
    delete ui;
}

void project::on_queue_clicked()
{
    queue*w=new queue;
    w->show();
    w->setWindowTitle("取号");
    QSqlDatabase db=QSqlDatabase::database();
}

//取号
void queue::on_new_queue_clicked()
{
    //取号id生成：前一个递增
    QSqlQuery query("select max(queue_id) from queue");
    int id=0;
    if(query.next()) {
        id=query.value(0).toInt();
    }
    int queue_id=id+1;
    QVariant customer_id; // 默认是null，如果是临时顾客可以不填顾客id
    QString idText = ui->customer_id->text();
    if (!idText.isEmpty()) {
        customer_id = idText.toInt(); // 转换为int存储
    }
    QString name=ui->name->text();
    QString phone=ui->phone->text();
    QSqlQuery query3;
    query3.prepare("insert into queue(queue_id,customer_id,customer_name,phone,call_status) "
                  "values (:queue_id,:customer_id,:customer_name,:phone,:call_status)");
    query3.bindValue(":queue_id", queue_id);
    query3.bindValue(":customer_id", customer_id);
    query3.bindValue(":customer_name", name);
    query3.bindValue(":phone", phone);
    query3.bindValue(":call_status", "等待");
    if(query3.exec())
    {
        QMessageBox::information(this, "提示", "取号成功！");
    }
    else QMessageBox::information(this, "警告", "取号失败！");
}

//查看等待顾客
void queue::on_check_queue_clicked()
{
    ui->listWidget->clear();//清空上次查询内容
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
    query.exec("select queue_id,customer_id, customer_name,phone ,call_status from queue where call_status='等待'");
    while (query.next())
    {
        QString queue_id,customer_id, customer_name,phone ,queue_number, call_status;
        queue_id= query.value("queue_id").toString();
        customer_id= query.value("customer_id").toString();
        customer_name= query.value("customer_name").toString();
        phone= query.value("phone").toString();
        call_status= query.value("call_status").toString();
        QString item=queue_id+"号 "+customer_id+" "+customer_name+"客人,联系方式："+phone
                +" 状态："+call_status;
        ui->listWidget->addItem(item);
    }
}


//叫号
void queue::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QSqlDatabase db=QSqlDatabase::database();
    QListWidgetItem *current = ui->listWidget->currentItem();
        if (current) {
            // 获取当前选中的取号id
            QString text= current->text(),queue_id;
            QSqlQuery query;
            QRegularExpression re("^(\\d+)号");//由于listWidget中信息存储按照"X号"，因此可以这样获取queue_id
            QRegularExpressionMatch match = re.match(text);
            if (match.hasMatch()) {
                 queue_id = match.captured(1);
                }
            query.prepare("update queue set call_status='已叫号' where queue_id=:queue_id");
            query.bindValue(":queue_id",queue_id);
            if(query.exec())
            {
                QMessageBox::information(this, "提示", "已叫号！");
                orderdish*w=new orderdish;
                w->show();
            }
            else QMessageBox::information(this, "警告", "叫号失败！");
        }

}
