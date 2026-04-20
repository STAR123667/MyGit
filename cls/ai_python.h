#ifndef AI_PYTHON_H
#define AI_PYTHON_H

#include <QCoreApplication>
#include <QProcess>
#include  <QDebug>

class ai_python
{
public:
    ai_python();
    void ccd_updata_TableCSV();
    void face_updata_TableCSV();
    void coating_machine_updata_TableCSV();
    void clean_data_AI();
    void line_break_AI();
};

#endif // AI_PYTHON_H
