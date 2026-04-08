#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include <QWidget>

namespace Ui {
class orderdetail;
}

class orderdetail : public QWidget
{
    Q_OBJECT

public:
    explicit orderdetail(QWidget *parent = nullptr);
    ~orderdetail();

private slots:
    void on_choose_clicked();



    void on_order_id_doubleClicked(const QModelIndex &index);

private:
    Ui::orderdetail *ui;
};

#endif // ORDERDETAIL_H
