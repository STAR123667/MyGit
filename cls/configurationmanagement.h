#ifndef CONFIGURATIONMANAGEMENT_H
#define CONFIGURATIONMANAGEMENT_H

#include <QWidget>

namespace Ui {
class configurationmanagement;
}

class configurationmanagement : public QWidget
{
    Q_OBJECT

public:
    explicit configurationmanagement(QWidget *parent = nullptr);
    ~configurationmanagement();

private slots:


    void on_gongyi_pushButton_clicked();

    void on_deviceConfing_pushButton_clicked();

    void on_autoConfing_pushButton_clicked();

    void on_fuzhuConfingpushButton_clicked();

    void on_testConfing_pushButton_clicked();

    void on_tubujiConfing_pushButton_clicked();

    void on_wrrogConfing_pushButton_clicked();

private:
    Ui::configurationmanagement *ui;
};

#endif // CONFIGURATIONMANAGEMENT_H
