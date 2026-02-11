#ifndef DATABASE_H
#define DATABASE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QFile>

#include "student.h"

class Database : public QObject
{
    Q_OBJECT
public:
    Database();
    Database(QString setPath);

    bool readStudentData(QString inPath,Student *setStudent);
    bool readBasicData();
    bool writeStudentData(Student *setStudent);

    bool readAll();
    bool writeAll();

    std::vector<Student> students;
    QStringList subjects,exams;
    QString path;

    void f_dataChanged(int stu,int exam,int sub,Subject newData);

signals:
    void s_dataChanged(int stu,int exam,int sub);
};

#endif // DATABASE_H
