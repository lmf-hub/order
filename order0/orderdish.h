#ifndef ORDERDISH_H
#define ORDERDISH_H

#include <QWidget>

namespace Ui {
class orderdish;
}

class orderdish : public QWidget
{
    Q_OBJECT

public:
    explicit orderdish(QWidget *parent = nullptr);
    ~orderdish();

private slots:
    void on_finish_clicked();

    void on_add_dish_clicked();

private:
    Ui::orderdish *ui;
};

#endif // ORDERDISH_H
