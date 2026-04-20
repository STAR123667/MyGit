#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QWidget>

namespace Ui {
class datamanagement;
}

class datamanagement : public QWidget
{
    Q_OBJECT

public:
    explicit datamanagement(QWidget *parent = nullptr);
    ~datamanagement();

private slots:
    void on_pushButton_1_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::datamanagement *ui;
};

#endif // DATAMANAGEMENT_H
