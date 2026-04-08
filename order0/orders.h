#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>

namespace Ui {
class orders;
}

class orders : public QWidget
{
    Q_OBJECT

public:
    explicit orders(QWidget *parent = nullptr);
    ~orders();

private slots:
    void on_orders_show_clicked();

    void on_order_dish_clicked();

    void on_orderdetail_clicked();

private:
    Ui::orders *ui;
};

#endif // ORDERS_H
