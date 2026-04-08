#ifndef TOP_DISH_H
#define TOP_DISH_H

#include <QWidget>

namespace Ui {
class top_dish;
}

class top_dish : public QWidget
{
    Q_OBJECT

public:
    explicit top_dish(QWidget *parent = nullptr);
    ~top_dish();

private:
    Ui::top_dish *ui;
};

#endif // TOP_DISH_H
