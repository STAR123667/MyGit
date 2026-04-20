#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

class mySql
{
public:
    mySql();

    void Creator_SQL_Connection(void);

    void Creator_FACE_Table(void);
    void Creator_CCD_Table(void);
    void Creator_COATING_MACHINE_Table(void);

    void InsertInto_FACE_Table(void);
    void InsertInto_CCD_Table(const char* reviceData);
    void InsertInto_COATING_MACHINE_Table(void);

    bool ClearFree_FACE_Table(void);
    bool ClearFree_CCD_Table(void);
    bool ClearFree_COATING_MACHINE_Table(void);

    void Find_FACE_Table(void);

    void Update_FACE_Table(void);

    bool DB_ConnectionFlag;/**/

    QString DB_Name;

private:

};

#endif // MYSQL_H
