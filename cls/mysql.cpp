#include "mysql.h"

#include <QString>
#include <string>
using namespace std;

mySql::mySql()
{
    /*SQlite connection lib*/
    Creator_SQL_Connection();

   /* 表格，存在不用创建，否则在路径下新创建 */
//    Creator_FACE_Table();
//    Creator_CCD_Table();
//    Creator_COATING_MACHINE_Table();
}

/*创建SQLite数据库连接*/
void mySql::Creator_SQL_Connection(void)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");    /*创建QSql数据库*/

    if(db.open())
    {
       qDebug() << "数据库连接成功!";
    }
    else
    {
        qDebug() << "数据库连接失败!" << db.lastError();
    }
}

/*创建面密度仪表格*/
void mySql::Creator_FACE_Table(void)
{
     QSqlQuery face_query;

     if(!face_query.exec("CREATE TABLE FACE_TABLE (id INTEGER PRIMARY KEY, 产品型号 TEXT)"))
     {
          qDebug() << "Error: Failed to create table" << face_query.lastError();
     }
     else
     {
          qDebug() << "Table created successsfully";
     }

}

/*创建CCD表格*/
void mySql::Creator_CCD_Table(void)
{
    QSqlQuery ccd_query;

    if(!ccd_query.exec("CREATE TABLE CCD_TABLE (id INTEGER PRIMARY KEY, 名称 TEXT, 单位 TEXT, 地址 TEXT, 值 REAL)"))
    {
         qDebug() << "Error: Failed to create table" << ccd_query.lastError();
    }
    else
    {
         qDebug() << "Table created successsfully";
    }

}

/*创建涂布机表格*/
void mySql::Creator_COATING_MACHINE_Table(void)
{
    QSqlQuery coatingMachine_query;

    if(!coatingMachine_query.exec("CREATE TABLE COATING_MACHINE_TABLE  (id INTEGER PRIMARY KEY, 名称 TEXT, 单位 TEXT, 地址 TEXT, 值 REAL)"))
    {
         qDebug() << "Error: Failed to create table" << coatingMachine_query.lastError();
    }
    else
    {
         qDebug() << "Table created successsfully";
    }

}

/*插入数据，面密度仪表格*/
void mySql::InsertInto_FACE_Table(void)
{
    QSqlQuery face_query;
    face_query.exec("INSERT INTO FACE_TABLE VALUES (1,'3','1','05','123','1','1','10','30','0.11','0.55','1','10.5','10.0','makeout','10','100','0.1','0.01','0.01','50','300','2026-1-20')");
}

/*插入数据，CCD表格*/
void mySql::InsertInto_CCD_Table(const char* reviceData)
{
        QSqlQuery ccd_query;

        string str = "INSERT INTO CCD_TABLE VALUES ";

         const char* ch = reviceData;

         std::string  result;
         result += str;
         result += ch;

         QString qStr = QString::fromStdString(result);
         ccd_query.prepare(qStr);
         ccd_query.exec();
}

/*插入数据，涂布机表格*/
void mySql::InsertInto_COATING_MACHINE_Table(void)
{
    QSqlQuery coating_machine_query;
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (1, '设备运行状态', '启动/停止', '%DB600.DBD0', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (2, '设备正转速度', 'm/min', '%DB600.DBD12', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (3, '设备实时速度', 'm/min', '%DB600.DBD16', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (4, '机头A涂布状态', '', '%DB600.DBD4', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (5, '机头B涂布状态', '', '%DB600.DBD8', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (6, '机头A_A料涂布压力实时值', 'Kpa', '%DB600.DBD20', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (7, '机头A_B料涂布压力实时值', 'Kpa', '%DB600.DBD24', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (8, '机头A_A料回流压力实时值', 'Kpa', '%DB600.DBD28', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (9, '机头A_B料回流压力实时值', 'Kpa', '%DB600.DBD32', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (10, '机头A_A料螺杆泵泵速设定值', 'rpm', '%DB600.DBD36', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (11, '机头A_B料螺杆泵泵速设定值', 'rpm', '%DB600.DBD40', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (12, '机头A_A料螺杆泵泵速实时值', 'rpm', '%DB600.DBD44', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (13, '机头A_B料螺杆泵泵速实时值', 'rpm', '%DB600.DBD48', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (14, '机头B_A料涂布压力实时值', 'Kpa', '%DB600.DBD52', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (15, '机头B_B料涂布压力实时值', 'Kpa', '%DB600.DBD56', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (16, '机头B_A料回流压力实时值', 'Kpa', '%DB600.DBD60', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (17, '机头B_B料回流压力实时值', 'Kpa', '%DB600.DBD64', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (18, '机头B_A料螺杆泵泵速设定值', 'rpm', '%DB600.DBD68', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (19, '机头B_B料螺杆泵泵速设定值', 'rpm', '%DB600.DBD72', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (20, '机头B_A料螺杆泵泵速实时值', 'rpm', '%DB600.DBD76', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (21, '机头B_B料螺杆泵泵速实时值', 'rpm', '%DB600.DBD80', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (22, '机头A_A浆料实时流量', 'kg/H', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (23, '机头A_B浆料实时流量', 'kg/H', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (24, '机头B_A浆料实时流量', 'kg/H', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (25, '机头B_B浆料实时流量', 'kg/H', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (26, '机头A_A浆料实时密度', 'kg/I', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (27, '机头A_B浆料实时密度', 'kg/I', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (28, '机头B_A浆料实时密度', 'kg/I', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (29, '机头B_B浆料实时密度', 'kg/I', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (30, '机头A_A料浆料温度', '℃', '%DB600.DBD92', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (31, '机头A_B料浆料温度', '℃', '%DB600.DBD96', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (32, '机头B_A料浆料温度', '℃', '%DB600.DBD100', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (33, '机头B_B料浆料温度', '℃', '%DB600.DBD104', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (34, '机头A左GAP设定值', 'μm', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (35, '机头A右GAP设定值', 'μm', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (36, '机头B左GAP设定值', 'μm', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (37, '机头B右GAP设定值', 'μm', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (38, '机头A左GAP实时值', 'μm', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (39, '机头A右GAP实时值', 'μm', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (40, '机头B左GAP实时值', 'μm', '', 0 )" );
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (41, '机头B右GAP实时值', 'μm', '', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (42, '单面产能', 'm', '%DB600.DBD84', 0 )");
    coating_machine_query.exec("INSERT INTO COATING_MACHINE_TABLE VALUES (43, '双面产能', 'm', '%DB600.DBD88', 0 )" );

}


/*面密度仪表，清空*/
bool mySql::ClearFree_FACE_Table(void)
{
     QSqlQuery face_query;

     return face_query.exec("DELETE FROM FACE_TABLE") ;

}
/*CCD表，清空*/
bool mySql::ClearFree_CCD_Table(void)
{
     QSqlQuery ccd_query;

     return ccd_query.exec("DELETE FROM CCD_TABLE");
}
/*涂布机表，清空*/
bool mySql::ClearFree_COATING_MACHINE_Table(void)
{
     QSqlQuery coating_machine_query;

     return coating_machine_query.exec("DELETE FROM COATING_MACHINE_TABLE");
}

/*查找表格*/
void mySql::Find_FACE_Table(void)
{
      QSqlQuery query;
      query.exec("SELECT * FROM CCD_TABLE");

      if(!query.exec())
      {
          qDebug() << "Error: Fail to query table." << query.lastError();
      }
      else
      {
          while(query.next())
          {
              int id = query.value(0).toInt();
              QString 名称 = query.value(1).toString();
              QString 单位 = query.value(2).toString();
              QString 地址 = query.value(3).toString();
              QString 值 = query.value(4).toString();

              qDebug() <<QString("id:%1  名称:%2  单位:%3  地址:%4  值:%5").arg(id).arg(名称).arg(单位).arg(地址).arg(值);
          }
      }

}

/*修改表格*/
void mySql::Update_FACE_Table(void)
{
    QSqlQuery query;
    query.exec("UPDATE  CCD_TABLE  SET  名称 = '正面'  WHERE  ID = 1");
    if(!query.exec())
    {
         qDebug() << query.lastError();
    }
    else
    {
         qDebug() << "updated!";
    }
}






