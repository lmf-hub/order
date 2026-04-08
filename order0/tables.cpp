#include "tables.h"
#include "ui_tables.h"
#include "project.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include<qmessagebox.h>
tables::tables(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tables)
{
    ui->setupUi(this);
}

tables::~tables()
{
    delete ui;
}
void project::on_tables_clicked()
{
    tables*w=new tables;
    w->show();
    w->setWindowTitle("餐桌信息");
    QSqlDatabase db=QSqlDatabase::database();
}

void tables::on_tables_show_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query(db);
        query.exec("select table_id,seat_count from tables where status='空'");
        while (query.next())
        {
            QString table_id= query.value("table_id").toString();
            QString seat_count= query.value("seat_count").toString();
            QString item=table_id+"  "+seat_count+"人桌，可用";
            ui->listWidget->addItem(item);
        }
}
