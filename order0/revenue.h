#ifndef REVENUE_H
#define REVENUE_H

#include <QWidget>

namespace Ui {
class revenue;
}

class revenue : public QWidget
{
    Q_OBJECT

public:
    explicit revenue(QWidget *parent = nullptr);
    ~revenue();

private slots:
    void on_check_clicked();

    void on_Summary_clicked();

private:
    Ui::revenue *ui;
};

#endif // REVENUE_H
