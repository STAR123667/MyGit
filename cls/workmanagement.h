#ifndef WORKMANAGEMENT_H
#define WORKMANAGEMENT_H

#include <QWidget>

namespace Ui {
class workmanagement;
}

class workmanagement : public QWidget
{
    Q_OBJECT

public:
    explicit workmanagement(QWidget *parent = nullptr);
    ~workmanagement();

private:
    Ui::workmanagement *ui;

};

#endif // WORKMANAGEMENT_H
