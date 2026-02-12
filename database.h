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
    bool writeBasic();

    bool readAll();
    bool writeAll();

    void deleteStudent(QString id);
    void deleteExam(QString name);
    void deleteSubject(QString name);

    std::vector<Student> students;
    QStringList subjects,exams;
    QString path;

    void f_dataChanged(int stu,int exam,int sub,Subject newData);

};

#endif // DATABASE_H
