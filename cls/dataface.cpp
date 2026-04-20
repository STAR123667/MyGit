#include "dataface.h"
#include "ui_dataface.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>


dataface::dataface(QWidget *parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    ui(new Ui::dataface)
{
        ui->setupUi(this);
        populateThemeBox();
        populateAnimationBox();
        populateLegendBox();

        QChartView *chartView;

        chartView = new QChartView(createAreaChart());
        ui->gridLayout->addWidget(chartView, 1, 0);
        m_charts << chartView;

        //![5]
        chartView = new QChartView(createLineChart());
        ui->gridLayout->addWidget(chartView, 1, 1);
        //![5]
        m_charts << chartView;

        chartView = new QChartView(createBarChart(m_valueCount));
        ui->gridLayout->addWidget(chartView, 2, 0);
        m_charts << chartView;

        chartView = new QChartView(createSplineChart());
        ui->gridLayout->addWidget(chartView, 2, 1);
        m_charts << chartView;

        ui->antialiasCheckBox->setChecked(true);

        QPalette pal = qApp->palette();
        pal.setColor(QPalette::Window,  QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText,  QRgb(0x404044));
        qApp->setPalette(pal);

        updateUI();

}

dataface::~dataface()
{
    delete ui;
}


DataTable dataface::generateRandomData(int listCount, int valueMax, int valueCount) const
{
        DataTable dataTable;

        for (int i(0); i < listCount; i++)
        {
             DataList dataList;
             qreal yValue(0);
             for (int j(0); j < valueCount; j++)
             {
                        yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
                        QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                                      yValue);
                        QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
                        dataList << Data(value, label);
             }
             dataTable << dataList;
        }
        return dataTable;
}


void dataface::populateThemeBox()
{
    // add items to theme combobox
    ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void dataface::populateAnimationBox()
{
    // add items to animation combobox
    ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void dataface::populateLegendBox()
{
    // add items to legend combobox
    ui->legendComboBox->addItem("No Legend ", 0);
    ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}


QChart *dataface::createAreaChart() const
{
       QChart *chart = new QChart();
       chart->setTitle("面密度仪实时数据");

       // The lower series initialized to zero values
       QLineSeries *lowerSeries = 0;
       QString name("Series ");
       int nameIndex = 0;
       for (int i(0); i < m_dataTable.count(); i++) {
           QLineSeries *upperSeries = new QLineSeries(chart);
           for (int j(0); j < m_dataTable[i].count(); j++) {
               Data data = m_dataTable[i].at(j);
               if (lowerSeries) {
                   const QVector<QPointF>& points = lowerSeries->pointsVector();
                   upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
               } else {
                   upperSeries->append(QPointF(j, data.first.y()));
               }
           }
           QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
           area->setName(name + QString::number(nameIndex));
           nameIndex++;
           chart->addSeries(area);
           lowerSeries = upperSeries;
       }

       chart->createDefaultAxes();
       chart->axes(Qt::Horizontal).first()->setRange(0, m_valueCount - 1);
       chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax);
       // Add space to label to add space between labels and axis
       QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
       Q_ASSERT(axisY);
       axisY->setLabelFormat("%.1f  ");

       return chart;

}


QChart *dataface::createBarChart(int valueCount) const
{
     Q_UNUSED(valueCount);
     QChart *chart = new QChart();
     chart->setTitle("横向趋势图");

     QStackedBarSeries *series = new QStackedBarSeries(chart);
     for (int i(0); i < m_dataTable.count(); i++)
     {
          QBarSet *set = new QBarSet("Bar set " + QString::number(i));
          for (const Data & data : m_dataTable[i])
              *set << data.first.y();
          series->append(set);
     }

     chart->addSeries(series);
     chart->createDefaultAxes();
     chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax * 2);

     QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
     Q_ASSERT(axisY);
     axisY->setLabelFormat("%.1f   ");

     return chart;
}


//QChart *dataface::createPieChart() const
//{
//      QChart *chart = new QChart();
//      chart->setTitle("Pie chart");

//      QPieSeries *series = new QPieSeries(chart);
//      for (const Data &data : m_dataTable[0])
//      {
//          QPieSlice *slice = series->append(data.second, data.first.y());
//          if(data == m_dataTable[0].first())
//          {
//              slice->setLabelVisible();
//              slice->setExploded();
//              slice->setExplodeDistanceFactor(0.5);
//          }
//      }
//      series->setPieSize(0.4);
//      chart->addSeries(series);

//      return chart;
//}


QChart *dataface::createLineChart() const
{
      QChart *chart = new QChart();
      chart->setTitle("毫米趋势图");

      QString name("Series ");
      int nameIndex = 0;
      for (const DataList &list : m_dataTable)
      {
            QLineSeries *series = new QLineSeries(chart);
            for (const Data &data : list)
              series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
      }

      chart->createDefaultAxes();
      chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
      chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

      QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
      Q_ASSERT(axisY);
      axisY->setLabelFormat("%.1f  ");

      return chart;
}


QChart *dataface::createSplineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("纵向趋势图");

    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : m_dataTable)
    {
          QSplineSeries *series = new QSplineSeries(chart);
          for (const Data &data : list)
            series->append(data.first);
          series->setName(name + QString::number(nameIndex));
          nameIndex++;
          chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}


//QChart *dataface::createScatterChart() const
//{
//    QChart *chart = new QChart();
//    chart->setTitle("Scatter chart");

//    QString name("Series ");
//    int nameIndex = 0;
//    for (const DataList &list : m_dataTable)
//    {
//          QScatterSeries *series = new QScatterSeries(chart);
//          for (const Data &data : list)
//            series->append(data.first);
//          series->setName(name + QString::number(nameIndex));
//          nameIndex++;
//          chart->addSeries(series);
//    }

//    chart->createDefaultAxes();
//    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);
//    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);

//    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
//    Q_ASSERT(axisY);
//    axisY->setLabelFormat("%.1f  ");
//    return chart;
//}


void dataface::updateUI()
{
     //![6]
     QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(ui->themeComboBox->itemData(ui->themeComboBox->currentIndex()).toInt());
     //![6]
     const auto charts = m_charts;
     if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme)
     {
         for (QChartView *chartView : charts)
         {
             //![7]
             chartView->chart()->setTheme(theme);
             //![7]
         }

         // Set palette colors based on selected theme
              //![8]
              QPalette pal = window()->palette();
              if (theme == QChart::ChartThemeLight) {
                  pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
                  pal.setColor(QPalette::WindowText, QRgb(0x404044));
              //![8]
              } else if (theme == QChart::ChartThemeDark) {
                  pal.setColor(QPalette::Window, QRgb(0x121218));
                  pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
              } else if (theme == QChart::ChartThemeBlueCerulean) {
                  pal.setColor(QPalette::Window, QRgb(0x40434a));
                  pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
              } else if (theme == QChart::ChartThemeBrownSand) {
                  pal.setColor(QPalette::Window, QRgb(0x9e8965));
                  pal.setColor(QPalette::WindowText, QRgb(0x404044));
              } else if (theme == QChart::ChartThemeBlueNcs) {
                  pal.setColor(QPalette::Window, QRgb(0x018bba));
                  pal.setColor(QPalette::WindowText, QRgb(0x404044));
              } else if (theme == QChart::ChartThemeHighContrast) {
                  pal.setColor(QPalette::Window, QRgb(0xffab03));
                  pal.setColor(QPalette::WindowText, QRgb(0x181818));
              } else if (theme == QChart::ChartThemeBlueIcy) {
                  pal.setColor(QPalette::Window, QRgb(0xcee7f0));
                  pal.setColor(QPalette::WindowText, QRgb(0x404044));
              } else {
                  pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
                  pal.setColor(QPalette::WindowText, QRgb(0x404044));
              }
              window()->setPalette(pal);

     }

     // Update antialiasing
       //![11]
       bool checked = ui->antialiasCheckBox->isChecked();
       for (QChartView *chart : charts)
           chart->setRenderHint(QPainter::Antialiasing, checked);
       //![11]

       // Update animation options
       //![9]
       QChart::AnimationOptions options(
                   ui->animatedComboBox->itemData(ui->animatedComboBox->currentIndex()).toInt());
       if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
           for (QChartView *chartView : charts)
               chartView->chart()->setAnimationOptions(options);
       }
       //![9]

       // Update legend alignment
       //![10]
       Qt::Alignment alignment(
                   ui->legendComboBox->itemData(ui->legendComboBox->currentIndex()).toInt());

       if (!alignment) {
           for (QChartView *chartView : charts)
               chartView->chart()->legend()->hide();
       } else {
           for (QChartView *chartView : charts) {
               chartView->chart()->legend()->setAlignment(alignment);
               chartView->chart()->legend()->show();
           }
       }
       //![10]
       //!
}



void dataface::on_Updata_Button_pressed()
{
    QChartView *chartView;

    chartView = new QChartView(createAreaChart());
    ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    //![5]
    chartView = new QChartView(createLineChart());
    ui->gridLayout->addWidget(chartView, 1, 1);
    //![5]
    m_charts << chartView;

    chartView = new QChartView(createBarChart(m_valueCount));
    ui->gridLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart());
    ui->gridLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;
}

