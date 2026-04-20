#ifndef MANUALOPERATION_H
#define MANUALOPERATION_H

/*CANalyst-II 包含头文件*/
#include "canthread.h"
/*对话框 包含头文件*/
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
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

#include <QMainWindow>

#define MOTOR_ADDRESS_BASE_ID  0X00000200
#define MOTOR_SYNC_MESSAGE_ID  0X00000080

QT_CHARTS_USE_NAMESPACE/*must use*/

extern uint8_t  openStart;

namespace Ui {
class manualOperation;
}

class manualOperation : public QWidget
{
    Q_OBJECT

public:
    explicit manualOperation(QWidget *parent = nullptr);
    ~manualOperation();

    void DanMode_dataSlave(void);
    void AllMode_dataSlave(void);
    void HightMode_dataSlave(void);

    void OnlyModeSend(uint8_t Area);  /*单区模式发送*/
    void HightModeSend(void); /*高级模式发送*/
    void CAN_WarningMessage_Show(void); /*CAN警告消息提示*/


      void FaceReal_DataChart();                /*面密度仪实时数据图*/
      QChartView *facereal_chartview;
      QChart *FaceRealData_Dealwith() const;

      void FaceReal_TendencyChart();      /*面密度仪趋势图*/
      QChartView *FACE_REAL_TendencyChart;
      QChart *FaceData_TendencyChart_Dealwith () const;

      void FaceReal_DataChart2();                /*面密度仪实时数据图*/
      QChartView *facereal_chartview2;
      void FaceReal_TendencyChart2();      /*面密度仪趋势图*/
      QChartView *FACE_REAL_TendencyChart2;

      void FaceReal_DataChart3();                /*面密度仪实时数据图*/
      QChartView *facereal_chartview3;
      void FaceReal_TendencyChart3();      /*面密度仪趋势图*/
      QChartView *FACE_REAL_TendencyChart3;

private:
    Ui::manualOperation *ui;

    typedef struct DEVICE_CLASS{

        uint16_t Motor_AdjSite[30];  /*电杆调节量*/
        uint16_t Motor_Site[30];       /*电杆当前位置*/
        uint16_t Motor_address[30]; /*电杆地址*/
        uint8_t  Can_SendBuffer[8];  /*发送缓冲区*/
        int mT_Height[28];               /*面密度高度*/
        QString gMT_num;
        QString gT_status;
        QString WString;   /*转换值*/
        int Wint;               /*转换值*/

    }DEVICE_TYPEDEF;

     DEVICE_TYPEDEF device_typedef;

       VCI_CAN_OBJ  vco;

private slots:

    void on_SelectMode_Button1_clicked();
    void on_SelectMode_Button2_clicked();
    void on_SelectMode_Button3_clicked();
    void on_SelectMode_Button4_clicked();

    void on_motor3_open_button_valueChanged(int value);
    void on_motor4_open_button_valueChanged(int value);
    void on_motor5_open_button_valueChanged(int value);
    void on_motor6_open_button_valueChanged(int value);
    void on_motor7_open_button_valueChanged(int value);
    void on_motor8_open_button_valueChanged(int value);
    void on_motor9_open_button_valueChanged(int value);
    void on_motor10_open_button_valueChanged(int value);
    void on_motor11_open_button_valueChanged(int value);
    void on_motor12_open_button_valueChanged(int value);
    void on_motor13_open_button_valueChanged(int value);

    void on_pushButton_modeArae1_clicked();
    void on_pushButton_modeArae2_clicked();

    void on_all_open_button_valueChanged(int value);

    void on_motor18_open_button_valueChanged(int value);
    void on_motor19_open_button_valueChanged(int value);
    void on_motor20_open_button_valueChanged(int value);
    void on_motor21_open_button_valueChanged(int value);
    void on_motor22_open_button_valueChanged(int value);
    void on_motor23_open_button_valueChanged(int value);
    void on_motor24_open_button_valueChanged(int value);
    void on_motor25_open_button_valueChanged(int value);
    void on_motor26_open_button_valueChanged(int value);
    void on_motor27_open_button_valueChanged(int value);
    void on_motor28_open_button_valueChanged(int value);

    void on_motor3_add_button_pressed();
    void on_motor3_sub_button_pressed();
    void on_motor4_add_button_pressed();
    void on_motor4_sub_button_released();
    void on_motor5_add_button_pressed();
    void on_motor5_sub_button_pressed();
    void on_motor6_add_button_pressed();
    void on_motor6_sub_button_pressed();
    void on_motor7_add_button_pressed();
    void on_motor7_sub_button_pressed();
    void on_motor8_add_button_pressed();
    void on_motor8_sub_button_pressed();
    void on_motor9_add_button_pressed();
    void on_motor9_sub_button_pressed();
    void on_motor10_add_button_pressed();
    void on_motor10_sub_button_pressed();
    void on_motor11_add_button_pressed();
    void on_motor11_sub_button_pressed();
    void on_motor12_add_button_pressed();
    void on_motor12_sub_button_pressed();
    void on_motor13_add_button_pressed();
    void on_motor13_sub_button_pressed();
    void on_motor18_add_button_pressed();
    void on_motor18_sub_button_pressed();
    void on_motor19_add_button_pressed();
    void on_motor19_sub_button_pressed();
    void on_motor20_add_button_pressed();
    void on_motor20_sub_button_pressed();
    void on_motor21_add_button_pressed();
    void on_motor21_sub_button_pressed();
    void on_motor22_add_button_pressed();
    void on_motor22_sub_button_pressed();
    void on_motor23_add_button_pressed();
    void on_motor23_sub_button_pressed();
    void on_motor24_add_button_pressed();
    void on_motor24_sub_button_pressed();
    void on_motor25_add_button_pressed();
    void on_motor25_sub_button_pressed();
    void on_motor26_add_button_pressed();
    void on_motor26_sub_button_pressed();
    void on_motor27_add_button_pressed();
    void on_motor27_sub_button_pressed();
    void on_motor28_add_button_pressed();
    void on_motor28_sub_button_pressed();

    void on_pushButton_siteWrite_pressed();
    void on_pushButton_clear_pressed();

    void on_motor3_open_button2_valueChanged(int value);
    void on_motor4_open_button2_valueChanged(int value);
    void on_motor5_open_button2_valueChanged(int value);
    void on_motor6_open_button2_valueChanged(int value);
    void on_motor7_open_button2_valueChanged(int value);
    void on_motor8_open_button2_valueChanged(int value);
    void on_motor9_open_button2_valueChanged(int value);
    void on_motor10_open_button2_valueChanged(int value);
    void on_motor11_open_button2_valueChanged(int value);
    void on_motor12_open_button2_valueChanged(int value);
    void on_motor13_open_button2_valueChanged(int value);
    void on_motor18_open_button2_valueChanged(int value);
    void on_motor19_open_button2_valueChanged(int value);
    void on_motor20_open_button2_valueChanged(int value);
    void on_motor21_open_button2_valueChanged(int value);
    void on_motor22_open_button2_valueChanged(int value);
    void on_motor23_open_button2_valueChanged(int value);
    void on_motor24_open_button2_valueChanged(int value);
    void on_motor25_open_button2_valueChanged(int value);
    void on_motor26_open_button2_valueChanged(int value);
    void on_motor27_open_button2_valueChanged(int value);
    void on_motor28_open_button2_valueChanged(int value);
    void on_all_open_button2_valueChanged(int value);

    void on_motor3_add_button2_pressed();
    void on_motor3_sub_button2_pressed();
    void on_motor4_add_button2_pressed();
    void on_motor4_sub_button2_pressed();
    void on_motor5_add_button2_pressed();
    void on_motor5_sub_button2_pressed();
    void on_motor6_add_button2_pressed();
    void on_motor6_sub_button2_pressed();
    void on_motor7_add_button2_pressed();
    void on_motor7_sub_button2_pressed();
    void on_motor8_add_button2_pressed();
    void on_motor8_sub_button2_pressed();
    void on_motor9_add_button2_pressed();
    void on_motor9_sub_button2_pressed();

    void on_motor10_add_button2_pressed();
    void on_motor10_sub_button2_pressed();
    void on_motor11_add_button2_pressed();
    void on_motor11_sub_button2_pressed();
    void on_motor12_add_button2_pressed();
    void on_motor12_sub_button2_pressed();
    void on_motor13_add_button2_pressed();
    void on_motor13_sub_button2_pressed();
    void on_motor18_add_button2_pressed();
    void on_motor18_sub_button2_pressed();
    void on_motor19_add_button2_pressed();
    void on_motor19_sub_button2_pressed();
    void on_motor20_add_button2_pressed();
    void on_motor20_sub_button2_pressed();
    void on_motor21_add_button2_pressed();
    void on_motor21_sub_button2_pressed();
    void on_motor22_add_button2_pressed();
    void on_motor22_sub_button2_pressed();
    void on_motor23_add_button2_pressed();
    void on_motor23_sub_button2_pressed();
    void on_motor24_add_button2_pressed();
    void on_motor24_sub_button2_pressed();
    void on_motor25_add_button2_pressed();
    void on_motor25_sub_button2_pressed();
    void on_motor26_add_button2_pressed();
    void on_motor26_sub_button2_pressed();
    void on_motor27_add_button2_pressed();
    void on_motor27_sub_button2_pressed();
    void on_motor28_add_button2_pressed();
    void on_motor28_sub_button2_pressed();
    void on_pushButton_clear2_pressed();

    void on_hightMode_siteWrite_pressed();

    void on_motor1_open_button3_valueChanged(int value);
    void on_motor2_open_button3_valueChanged(int value);
    void on_motor3_open_button3_valueChanged(int value);
    void on_motor4_open_button3_valueChanged(int value);
    void on_motor5_open_button3_valueChanged(int value);
    void on_motor6_open_button3_valueChanged(int value);
    void on_motor7_open_button3_valueChanged(int value);
    void on_motor8_open_button3_valueChanged(int value);
    void on_motor9_open_button3_valueChanged(int value);
    void on_motor10_open_button3_valueChanged(int value);
    void on_motor11_open_button3_valueChanged(int value);
    void on_motor12_open_button3_valueChanged(int value);
    void on_motor13_open_button3_valueChanged(int value);
    void on_motor14_open_button3_valueChanged(int value);
    void on_motor15_open_button3_valueChanged(int value);
    void on_motor16_open_button3_valueChanged(int value);
    void on_motor17_open_button3_valueChanged(int value);
    void on_motor18_open_button3_valueChanged(int value);
    void on_motor19_open_button3_valueChanged(int value);
    void on_motor20_open_button3_valueChanged(int value);
    void on_motor21_open_button3_valueChanged(int value);
    void on_motor22_open_button3_valueChanged(int value);
    void on_motor23_open_button3_valueChanged(int value);
    void on_motor24_open_button3_valueChanged(int value);
    void on_motor25_open_button3_valueChanged(int value);
    void on_motor26_open_button3_valueChanged(int value);
    void on_motor27_open_button3_valueChanged(int value);
    void on_motor28_open_button3_valueChanged(int value);
    void on_motor29_open_button3_valueChanged(int value);
    void on_motor30_open_button3_valueChanged(int value);
    void on_all_open_button3_valueChanged(int value);
    void on_stackedWidget_currentChanged(int arg1);
    void on_pushButton_siteWrite2_pressed();
    void on_motor1_add_button3_pressed();
    void on_motor1_sub_button3_pressed();
    void on_motor2_add_button3_pressed();
    void on_motor2_sub_button3_pressed();
    void on_motor3_add_button3_pressed();
    void on_motor3_sub_button3_pressed();
    void on_motor4_add_button3_pressed();
    void on_motor4_sub_button3_pressed();
    void on_motor5_add_button3_pressed();
    void on_motor5_sub_button3_pressed();
    void on_motor6_add_button3_pressed();
    void on_motor6_sub_button3_pressed();
    void on_motor7_add_button3_pressed();
    void on_motor7_sub_button3_pressed();
    void on_motor8_add_button3_pressed();
    void on_motor8_sub_button3_pressed();
    void on_motor9_add_button3_pressed();
    void on_motor9_sub_button3_pressed();
    void on_motor10_add_button3_pressed();
    void on_motor10_sub_button3_pressed();
    void on_motor11_add_button3_pressed();
    void on_motor11_sub_button3_pressed();
    void on_motor12_add_button3_pressed();
    void on_motor12_sub_button3_pressed();
    void on_motor13_add_button3_pressed();
    void on_motor13_sub_button3_pressed();
    void on_motor14_add_button3_pressed();
    void on_motor14_sub_button3_pressed();
    void on_motor15_add_button3_pressed();
    void on_motor15_sub_button3_pressed();
    void on_motor16_add_button3_pressed();
    void on_motor16_sub_button3_pressed();
    void on_motor17_add_button3_pressed();
    void on_motor17_sub_button3_pressed();
    void on_motor18_add_button3_pressed();
    void on_motor18_sub_button3_pressed();
    void on_motor19_add_button3_pressed();
    void on_motor19_sub_button3_pressed();
    void on_motor20_add_button3_pressed();
    void on_motor20_sub_button3_pressed();
    void on_motor21_add_button3_pressed();
    void on_motor22_add_button3_pressed();
    void on_motor21_sub_button3_pressed();
    void on_motor22_sub_button3_pressed();
    void on_motor23_add_button3_pressed();
    void on_motor23_sub_button3_pressed();
    void on_motor24_add_button3_pressed();
    void on_motor24_sub_button3_pressed();
    void on_motor25_add_button3_pressed();
    void on_motor25_sub_button3_pressed();
    void on_motor26_add_button3_pressed();
    void on_motor26_sub_button3_pressed();
    void on_motor27_add_button3_pressed();
    void on_motor27_sub_button3_pressed();
    void on_motor28_add_button3_pressed();
    void on_motor28_sub_button3_pressed();
    void on_motor29_add_button3_pressed();
    void on_motor29_sub_button3_pressed();
    void on_motor30_add_button3_pressed();
    void on_motor30_sub_button3_pressed();
    void on_comboBox_allmode_currentIndexChanged(int index);
    void on_comboBox_hightmode_currentIndexChanged(int index);
    void on_comboBox_onlymode_currentIndexChanged(int index);
    void on_AutoSiteWrite_open_button_valueChanged(int value);
    void on_stackedWidget_onlymode_currentChanged(int arg1);
    void on_stackedWidget_allmode_currentChanged(int arg1);
    void on_stackedWidget_hightmode_currentChanged(int arg1);
    void on_pushButton_clear3_pressed();
};

#endif // MANUALOPERATION_H
