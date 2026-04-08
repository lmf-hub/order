#ifndef PAYMENT_H
#define PAYMENT_H

#include <QWidget>

namespace Ui {
class payment;
}

class payment : public QWidget
{
    Q_OBJECT

public:
    explicit payment(QWidget *parent = nullptr);
    ~payment();

private slots:
    void on_pay_clicked();

    void on_ensure_clicked();

private:
    Ui::payment *ui;
};

#endif // PAYMENT_H
