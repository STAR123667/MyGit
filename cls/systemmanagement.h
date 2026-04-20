#ifndef SYSTEMMANAGEMENT_H
#define SYSTEMMANAGEMENT_H

#include <QWidget>

namespace Ui {
class systemmanagement;
}

class systemmanagement : public QWidget
{
    Q_OBJECT

public:
    explicit systemmanagement(QWidget *parent = nullptr);
    ~systemmanagement();

private:
    Ui::systemmanagement *ui;
};

#endif // SYSTEMMANAGEMENT_H
