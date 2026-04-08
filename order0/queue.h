#ifndef QUEUE_H
#define QUEUE_H

#include <QWidget>

namespace Ui {
class queue;
}

class queue : public QWidget
{
    Q_OBJECT

public:
    explicit queue(QWidget *parent = nullptr);
    ~queue();

private slots:
    void on_new_queue_clicked();

    void on_check_queue_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::queue *ui;
};

#endif // QUEUE_H
