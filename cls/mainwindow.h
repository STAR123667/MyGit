#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
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
/*其他页面包含头文件*/
#include <QTreeWidgetItem>
#include "manualoperation.h"
#include "ui_manualoperation.h"
#include "homepage.h"
#include "ui_homepage.h"
#include "dataface.h"
#include "ui_dataface.h"
#include "configurationmanagement.h"
#include "ui_configurationmanagement.h"
#include "datamanagement.h"
#include "ui_datamanagement.h"
#include "systemmanagement.h"
#include "ui_systemmanagement.h"
#include "workmanagement.h"
#include "ui_workmanagement.h"
#include "pagecontrol.h"
#include "ui_pagecontrol.h"

/*CANalyst-II 包含头文件*/
#include "canthread.h"
/*sqlist*/
#include "mysql.h"
/*network*/
#include "network.h"
#include "ui_network.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    manualOperation *Page_ManualOperation;
    homepage *Page_HomePage;
    dataface *Page_DataFace;
    configurationmanagement *Page_ConfigManagement;
    datamanagement *Page_DataManagement;
    systemmanagement *Page_SystemManagement;
    workmanagement *Page_WorkManagement;
    PageControl *Page_PageControl;

    network *Page_NetWork;
    mySql *Page_sqlist;

private:
    Ui::MainWindow *ui;
    canthread *CAN_Thread;/*CAN 对象*/
    network *Net_work;

private slots:
    void updateTime();
    void on_tabWidget_currentChanged(int index);
    void on_T_OPEN_valueChanged(int value);
    void on_BS_OPEN_valueChanged(int value);
    void on_CAP_OPEN_valueChanged(int value);
    void on_CAN_OPEN_valueChanged(int value);

};
#endif // MAINWINDOW_H

