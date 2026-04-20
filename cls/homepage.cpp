#include "homepage.h"
#include "ui_homepage.h"



#include <QAbstractAxis>



homepage::homepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);

    Motor_site_view();/*电杆实时位置*/
    Face_data_view(); /*面密度仪实时数据*/

    Face_Real_View();

}

homepage::~homepage()
{
    delete ui;
}

void homepage::Motor_site_view()
{
   ui->gridLayout_motor->removeWidget(DG_View);
   DG_View = new QChartView(MotorSite_data_dealwith());
   DG_View->chart()->legend()->hide();   /*不显示标题颜色*/
   ui->gridLayout_motor->addWidget(DG_View);
}

QChart *homepage::MotorSite_data_dealwith() const
{
   QChart *MotorView = new QChart();

   QFont font;
   //MotorView->setTitle("电杆实时位置");
   font.setPointSize(16);
   MotorView->setFont(font);

   QBarSeries *series1 = new QBarSeries();
   MotorView->addSeries(series1);

   QBarCategoryAxis *axisX = new QBarCategoryAxis();
   axisX->append(QStringList() <<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22"<<"23"<<"24"<<"25"<<"26"<<"27"<<"28");
   axisX->setGridLineVisible(0);
   MotorView->addAxis(axisX, Qt::AlignBottom);
   axisX->setLabelsFont(QFont("Arial",10));

     QValueAxis *axisY = new QValueAxis();
     axisY->setRange(0,2000);
     axisY->setGridLineVisible(1);
     axisY->setTickCount(5);
     axisY->setLabelFormat("%d");
     axisY->setLabelsColor(Qt::red);
     axisY->setLineVisible(false);
     MotorView->addAxis(axisY, Qt::AlignLeft);

     QPen gridLinePen(Qt::gray);
     gridLinePen.setStyle(Qt::DotLine);
     gridLinePen.setWidth(0);
     axisY->setGridLinePen(gridLinePen);

     QChartView * chartView = new QChartView();
     chartView->setChart(MotorView);

     QBarSeries *bar = new QBarSeries();
     bar->setLabelsFormat("@value");
     bar->setBarWidth(3);
     bar->setLabelsVisible(1);
     bar->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

     QBarSet *bs1 = new QBarSet("电杆实时位置 :um");
     bs1->setBrush(Qt::red);
     bs1->setLabelColor(Qt::black);
     bs1->setBorderColor(Qt::black);
     //bs1->setLabelFont(QFont("Arial",10));
     for(int i=0;i<28;i++)
     {  bs1->append(i+500);
     }

     //bar->append(bs1);
     MotorView->addSeries(bar);
     bar->attachAxis(axisX);
     bar->attachAxis(axisY);

    return MotorView;
}

void homepage::Face_data_view()
{
   ui->gridLayout_face->removeWidget(FACE_View);
   FACE_View = new QChartView(Face_data_dealwith());
   FACE_View->chart()->legend()->hide();   /*不显示标题颜色*/
   ui->gridLayout_face->addWidget(FACE_View);
}

QChart *homepage::Face_data_dealwith() const
{
    QChart *FaceView = new QChart();

    /**/
    QBarSet *bar = new QBarSet("面密度仪实时数据");

    uint16_t addValue=10;
    for(uint8_t i=0; i<=28; i++)
    {
        *bar << addValue;
        addValue += 10;
    }
//    *bar << 5 << 10 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6
//         << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6
//         << 372.6 << 375.6 << 376.6 << 377.6 << 377.6 << 377.6 << 370.6 << 378.6;
    bar->setColor(QColor(0,162,232));
    bar->setLabelColor(Qt::red);

    /**/
    QBarSeries *series = new QBarSeries();
    series->append(bar);
    series->setLabelsFormat("@value");
    series->setBarWidth(0.9);
    series->setLabelsVisible(1);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    FaceView->addSeries(series);
    FaceView->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10"
               << "11" << "12" << "13" << "14" << "15" << "16" << "17" << "18" << "19"
               << "20" << "21" << "22" << "23" << "24" << "25" << "26" << "27" << "28";

     /*x*/
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setGridLineVisible(0);
    axisX->setLabelsFont(QFont("Arial",10));
    axisX->setRange("0", "380.6");
    FaceView->addAxis(axisX,Qt::AlignBottom);

     /*y*/
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 380.6);
    axisY->setTickCount(7);
    axisY->setGridLineVisible(1);
    axisY->setLabelFormat("%.1f");
    axisY->setLabelsEditable(true);
    axisY->setLabelsColor(Qt::red);
    axisY->setLineVisible(false);
    series->attachAxis(axisY);
    FaceView->addAxis(axisY,Qt::AlignLeft);

    /**/
    QChartView *chartView = new QChartView(FaceView);
    chartView->setChart(FaceView);
    chartView->setRenderHint(QPainter::Antialiasing);

    return FaceView;
}


void homepage::Face_Real_View()
{
    ui->gridLayout_FaceTendencyChart->removeWidget(FACE_REAL_VIEW);
    FACE_REAL_VIEW = new QChartView(FaceData_TendencyChart());
    ui->gridLayout_FaceTendencyChart->addWidget(FACE_REAL_VIEW);
}

QChart *homepage::FaceData_TendencyChart () const
{
    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(1, 7);
    series->append(2, 8);
    series->append(3, 2);
    series->append(4, 3);
    series->append(5, 5);
    series->append(6, 8);

    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart Example");

    QChartView *chartView = new QChartView(chart);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chart;
}


void homepage::on_comboBox_home_currentIndexChanged(int index)
{
    switch(index){
    case 0:{

        ui->stackedWidget_home->setCurrentIndex(0);

    }break;
    case 1:{

        ui->stackedWidget_home->setCurrentIndex(1);

    }break;
    default:break;
    }
}

