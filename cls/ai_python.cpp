#include "ai_python.h"

ai_python::ai_python()
{
}


void ai_python::ccd_updata_TableCSV()
{
        QProcess *ccd_process = new QProcess();
        ccd_process->setWorkingDirectory("/home/cat/closed_loop_system/AI_Python");
        ccd_process->start("python", QStringList() << "CCD_CSV_TABLE.py");

        if (ccd_process->waitForFinished()) {
                  qDebug() << "success_csv_ccd";
        }
        else {
                  qDebug() << "error_csv_ccd";
        }

       delete ccd_process;
}

void ai_python::face_updata_TableCSV()
{
    QProcess *face_process = new QProcess();
    face_process->setWorkingDirectory("/home/cat/closed_loop_system/AI_Python");
    face_process->start("python", QStringList() << "FACE_CSV_TABLE.py");

    if (face_process->waitForFinished()) {
              qDebug() << "success_csv_face";
    }
    else {
              qDebug() << "error_csv_face";
    }

   delete face_process;
}

void ai_python::coating_machine_updata_TableCSV()
{
      QProcess *coating_machine_process = new QProcess();
      coating_machine_process->setWorkingDirectory("/home/cat/closed_loop_system/AI_Python");
      coating_machine_process->start("python", QStringList() << "COATING_MACHINE_CSV_TABLE.py");

    if (coating_machine_process->waitForFinished()) {
              qDebug() << "success_csv_coating_machine";
    }
    else {
              qDebug() << "error_csv_coating_machine";
    }

   delete coating_machine_process;
}


void ai_python::clean_data_AI()
{
    QProcess *clean_process = new QProcess();

    clean_process->setWorkingDirectory("/home/cat/closed_loop_system/AI_Python");

    clean_process->start("python", QStringList() << "clearnData.py");

    if (clean_process->waitForFinished()) {
             qDebug() << "data clean success";
    }
    else {
             qDebug() << "data clean faile";
    }

   delete clean_process;

}


void ai_python::line_break_AI()
{
    QProcess *linebreak_process = new QProcess();

    linebreak_process->setWorkingDirectory("/home/cat/closed_loop_system/AI_Python");

    linebreak_process->start("python", QStringList() << "lineBrack.py");

    if (linebreak_process->waitForFinished()) {

            QString output = linebreak_process->readAllStandardOutput();

                qDebug() << "line break success" << output;
    }
    else {
                 qDebug() << "line break success" << linebreak_process->errorString();
    }

   delete linebreak_process;

}



