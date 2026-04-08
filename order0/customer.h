#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>

namespace Ui {
class customer;
}

class customer : public QWidget
{
    Q_OBJECT

public:
    explicit customer(QWidget *parent = nullptr);
    ~customer();

private slots:
    void on_show_coustomer_clicked();

    void on_delete_vip_clicked();

    void on_open_clicked();

private:
    Ui::customer *ui;

};

#endif // CUSTOMER_H
