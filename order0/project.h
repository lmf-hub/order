#ifndef PROJECT_H
#define PROJECT_H

#include <QWidget>

namespace Ui {
class project;
}

class project : public QWidget
{
    Q_OBJECT

public:
    explicit project(QWidget *parent = nullptr);
    ~project();

private slots:
    void on_customer_clicked();

    void on_dish_clicked();

    void on_tables_clicked();

    void on_orders_clicked();



    void on_queue_clicked();

    void on_payment_clicked();

    void on_revenue_clicked();

private:

    Ui::project *ui;

};

#endif // PROJECT_H
