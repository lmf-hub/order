#ifndef DISH_H
#define DISH_H

#include <QWidget>

namespace Ui {
class dish;
}

class dish : public QWidget
{
    Q_OBJECT

public:
    explicit dish(QWidget *parent = nullptr);
    ~dish();

private slots:
    void on_dish_show_clicked();

    void on_top_clicked();

private:
    Ui::dish *ui;
};

#endif // DISH_H
