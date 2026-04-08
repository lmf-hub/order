#ifndef TABLES_H
#define TABLES_H

#include <QWidget>

namespace Ui {
class tables;
}

class tables : public QWidget
{
    Q_OBJECT

public:
    explicit tables(QWidget *parent = nullptr);
    ~tables();

private slots:
    void on_tables_show_clicked();

private:
    Ui::tables *ui;
};

#endif // TABLES_H
