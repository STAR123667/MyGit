#ifndef DATAFACE_H
#define DATAFACE_H

//#include <QWidget>
//#include <QChartView>
//#include <QChart>
//#include <QWidget>
//#include <QApplication>
//#include <QBarSeries>
//#include <QBarSet>
//#include <QLegend>
//#include <QBarCategoryAxis>
//#include <QValueAxis>
//#include <QHorizontalBarSeries>
//#include <QList>
//#include <QPair>
//#include <QLineEdit>
//#include <QLineSeries>
//#include <QStackedBarSeries>
//#include <QTextEdit>
//#include <QLabel>

//#include <QXYSeries>           /*折线图  曲线图 散点图*/
//#include <QLineSeries>         /*折线图 */
//#include <QSplineSeries>      /*曲线图 */
//#include <QScatterSeries>    /*散点图 */
//#include <QAreaSeries>



#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
namespace Ui {
class dataface;
}
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE    /*must use*/

class dataface : public QWidget
{
    Q_OBJECT

public:
    explicit dataface(QWidget *parent = nullptr);
    ~dataface();

private slots:
     void updateUI();

     void on_Updata_Button_pressed();

private:
     DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
//    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
//    QChart *createScatterChart() const;

private:
    Ui::dataface *ui;
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;
};

#endif // DATAFACE_H


