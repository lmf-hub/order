#include "top_dish.h"
#include "dish.h"
#include "ui_top_dish.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
top_dish::top_dish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::top_dish)
{
    ui->setupUi(this);
}

top_dish::~top_dish()
{
    delete ui;
}

void dish::on_top_clicked()
{
    top_dish*w=new top_dish;
    w->show();
    w->setWindowTitle("菜品受欢迎排行榜");
    QSqlDatabase db=QSqlDatabase::database();
}
