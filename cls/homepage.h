#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QApplication>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QHorizontalBarSeries>
#include <QList>
#include <QPair>
#include <QLineEdit>
#include <QLineSeries>
#include <QStackedBarSeries>
#include <QTextEdit>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE   /*must use*/

namespace Ui {
class homepage;
}

class homepage : public QWidget
{
    Q_OBJECT

public:
    explicit homepage(QWidget *parent = nullptr);
    ~homepage();

    void Motor_site_view();
    void Face_data_view();
    QChart *MotorSite_data_dealwith() const;
    QChart *Face_data_dealwith() const;
    QChartView *DG_View;
    QChartView *FACE_View;

    void Face_Real_View();
    QChart *FaceData_TendencyChart () const;
    QChartView *FACE_REAL_VIEW;


private:
    Ui::homepage *ui;

private slots:

    void on_comboBox_home_currentIndexChanged(int index);

};

#endif // HOMEPAGE_H
