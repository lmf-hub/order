#include "orderdish.h"
#include "ui_orderdish.h"
#include "orders.h"
#include <QSqlDatabase>     //需要的头文件
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include <QList>
#include <QPair>
#include<qmessagebox.h>
orderdish::orderdish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderdish)
{
    ui->setupUi(this);
}

orderdish::~orderdish()
{
    delete ui;
}

void orders::on_order_dish_clicked()
{
    orderdish*w=new orderdish;
    w->show();
    w->setWindowTitle("点餐");
    QSqlDatabase db=QSqlDatabase::database();
}

//下单
void orderdish::on_finish_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    //订单号生成：前一个订单号递增
    QSqlQuery query("select max(order_id) from orders");
    int id=0;
       if(query.next()) {
           id=query.value(0).toInt();
       }
       int order_id=id+1;
    //属性值获取:餐桌号，顾客编号，点餐日期
    int table_id=ui->table_id->text().toInt();
    QVariant customer_id; // 默认是null，如果是临时顾客可以不填顾客id
    QString idText = ui->customer_id->text();
    if (!idText.isEmpty()) {
        customer_id = idText.toInt(); // 转换为int存储
    }
    QDate order_date=ui->dateEdit->date();
    QDate currentDate = QDate::currentDate();
    if(order_date>currentDate) {
        QMessageBox::warning(this, "日期无效", "输入的日期不能大于当前日期,点餐失败！");
    }
    else{

    //获取点菜的数量
    int d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12;
    d1=ui->spinBox->text().toInt();
    d2=ui->spinBox_2->text().toInt();
    d3=ui->spinBox_3->text().toInt();
    d4=ui->spinBox_4->text().toInt();
    d5=ui->spinBox_5->text().toInt();
    d6=ui->spinBox_6->text().toInt();
    d7=ui->spinBox_7->text().toInt();
    d8=ui->spinBox_8->text().toInt();
    d9=ui->spinBox_9->text().toInt();
    d10=ui->spinBox_10->text().toInt();
    d11=ui->spinBox_11->text().toInt();
    d12=ui->spinBox_12->text().toInt();
    double total_price=15*d1+25*d2+35*d3+35*d4+25*d5+55*d6+25*d7+45*d8+15*d9+10*d10+2*d11+8*d12;
    QSqlQuery query2;
    query2.prepare("select discount_rate from customer where customer_id=:customer_id");
    query2.bindValue(":customer_id",customer_id);
    query2.exec();
    double discount_rate;
       if(query2.next()) {
           discount_rate =query2.value(0).toDouble();
       }
       else{
           discount_rate=1.00;
       }
    double actual_price=total_price*discount_rate;
    ui->total_price->setText(QString::number(actual_price));
    //点餐内容
    int dish=101;
    int data[]={d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12};
    const char *name[]={"清炒时蔬","地三鲜","红烧肉","香煎鸡胸肉","青椒肉丝","宫保鸡丁","番茄蛋汤","玉米排骨汤",
                 "韭菜盒子","红糖糍粑","农夫山泉","雪花啤酒"};
    for(int i=0;i<12;i++)
    {
        if(data[i]!=0)
        {
            QString item=QString::number(dish);
            QString item2=QString::number(data[i]);
            QString item3=name[i];
            ui->listWidget->addItem(item+" "+item3+" "+item2+"份");
        }
        dish=dish+1;
    }
    //向orders表格中插入内容
    QSqlQuery query3;
    query3.prepare("insert into orders (order_id,table_id,customer_id,"
                  "order_date,total_price,discount_rate,actual_price,or_status) "
                  "values (:order_id,:table_id,:customer_id,:order_date,"
                  ":total_price,:discount_rate,:actual_price,:or_status)");
    query3.bindValue(":order_id", order_id);
    query3.bindValue(":table_id", table_id);
    query3.bindValue(":customer_id",customer_id);
    query3.bindValue(":order_date",order_date);//默认今天
    query3.bindValue(":total_price",total_price);
    query3.bindValue(":discount_rate",discount_rate);
    query3.bindValue(":actual_price",actual_price);
    query3.bindValue(":or_status","未支付");
    query3.exec();
    //向orderdetail表格中插入内容
    //获取订单号和数量
    QList<QPair<int, int>> dishQuantities={
        {101,d1},{102,d2},{103,d3},{104,d4},{105,d5},{106,d6},
        {107,d7},{108,d8},{109,d9},{110,d10},{111,d11},{112,d12}
    };
    QSqlQuery query5;
    for (const auto& dishQuantity : dishQuantities) {
        QSqlQuery query4("select max(detail_id) from orderdetail");
        int id2=0;
           if(query4.next()) {
               id2=query4.value(0).toInt();
           }

      int detail_id=id2+1;
      int dish_id = dishQuantity.first;
      int quantity = dishQuantity.second;
      if(quantity!=0){
        query5.prepare("insert into orderdetail(detail_id,order_id,dish_id,quantity) "
                       "values (:detail_id,:order_id,:dish_id,:quantity)");
        query5.bindValue(":detail_id", detail_id);
        query5.bindValue(":order_id", order_id);
        query5.bindValue(":dish_id",dish_id);
        query5.bindValue(":quantity",quantity);
        query5.exec();
        }
     }
    }

}

//加菜
void orderdish::on_add_dish_clicked()
{
    QSqlDatabase db=QSqlDatabase::database();
    int order_id=ui->lineEdit->text().toInt();
    //获取点菜的数量
    int d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12;
    d1=ui->spinBox->text().toInt();
    d2=ui->spinBox_2->text().toInt();
    d3=ui->spinBox_3->text().toInt();
    d4=ui->spinBox_4->text().toInt();
    d5=ui->spinBox_5->text().toInt();
    d6=ui->spinBox_6->text().toInt();
    d7=ui->spinBox_7->text().toInt();
    d8=ui->spinBox_8->text().toInt();
    d9=ui->spinBox_9->text().toInt();
    d10=ui->spinBox_10->text().toInt();
    d11=ui->spinBox_11->text().toInt();
    d12=ui->spinBox_12->text().toInt();
    double total_price=15*d1+25*d2+35*d3+35*d4+25*d5+55*d6+25*d7+45*d8+15*d9+10*d10+2*d11+8*d12;
    QSqlQuery query2;
    QVariant customer_id; // 默认是null，如果是临时顾客可以不填顾客id
    QString idText = ui->customer_id->text();
    if (!idText.isEmpty()) {
        customer_id = idText.toInt(); // 转换为int存储
    }
    query2.prepare("select discount_rate from customer where customer_id=:customer_id");
    query2.bindValue(":customer_id",customer_id);
    query2.exec();
    double discount_rate;
       if(query2.next()) {
           discount_rate =query2.value(0).toDouble();
       }
       else{
           discount_rate=1.00;
       }
    double actual_price=total_price*discount_rate;
    ui->total_price->setText(QString::number(actual_price));
    //点餐内容
    int dish=101;
    int data[]={d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12};
    const char *name[]={"清炒时蔬","地三鲜","红烧肉","香煎鸡胸肉","青椒肉丝","宫保鸡丁","番茄蛋汤","玉米排骨汤",
                 "韭菜盒子","红糖糍粑","农夫山泉","雪花啤酒"};
    for(int i=0;i<12;i++)
    {
        if(data[i]!=0)
        {
            QString item=QString::number(dish);
            QString item2=QString::number(data[i]);
            QString item3=name[i];
            ui->listWidget->addItem(item+" "+item3+" "+item2+"份");
        }
        dish=dish+1;
    }
    //获取加菜之前的总价和实际总价
    QSqlQuery query3(db);
    query3.prepare("select total_price,actual_price from orders where order_id=:order_id");
    query3.bindValue(":order_id", order_id);
    if (!query3.exec()) {
        qDebug() << "查询失败:" << query3.lastError().text();
        return;
    }

    double total_price_before=0.0,actual_price_before=0.0;
    if(query3.next())
    {
        total_price_before= query3.value("total_price").toDouble();
        actual_price_before= query3.value("actual_price").toDouble();
    }
    else {
        qDebug() << "未找到订单 ID:" << order_id;
        return;
    }
    QSqlQuery query;
    query.prepare("update orders set total_price=:total_price_after,actual_price=:actual_price_after WHERE order_id=:order_id");
    double total_price_after=total_price+total_price_before;
    double actual_price_after=actual_price+actual_price_before;
    query.bindValue(":total_price_after", total_price_after);
    query.bindValue(":actual_price_after", actual_price_after);
    query.bindValue(":order_id", order_id);
    if (!query.exec()) {
        qDebug() << "更新失败:" << query.lastError().text();
        return;
    }
    //向orderdetail表格中插入内容
    //获取订单号和数量
    QList<QPair<int, int>> dishQuantities={
        {101,d1},{102,d2},{103,d3},{104,d4},{105,d5},{106,d6},
        {107,d7},{108,d8},{109,d9},{110,d10},{111,d11},{112,d12}
    };
    for (const auto& dishQuantity : dishQuantities) {
        QSqlQuery query4("select max(detail_id) from orderdetail");
        int id=0;
           if(query4.next()) {
               id=query4.value(0).toInt();
           }
           int detail_id_max=id+1;
        int dish_id = dishQuantity.first;
        int quantity = dishQuantity.second;//加菜所选的数量
        if(quantity!=0){
            QSqlQuery query5;
            query5.prepare("insert into orderdetail(detail_id,order_id,dish_id,quantity) "
                           "values (:detail_id,:order_id,:dish_id,:quantity)");
            query5.bindValue(":detail_id", detail_id_max);
            query5.bindValue(":order_id", order_id);
            query5.bindValue(":dish_id",dish_id);
            query5.bindValue(":quantity",quantity);
            if (!query5.exec()) {
                qDebug() << "插入失败:" << query5.lastError().text();
                return;
                }
        }
    }
}
