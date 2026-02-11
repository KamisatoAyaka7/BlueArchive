#ifndef STUDENT_H
#define STUDENT_H

#include <vector>

#include <QString>

class Subject
{
public:
    Subject();
    Subject(short gR,short rR,double gS,double rS);

    short goalRank=0,realRank=0;
    short goalScore=0,realScore=0;

    void setGoalScore(double setScore);
    void setRealScore(double setScore);

    double toGoalScore();
    double toRealScore();

};

class Exam
{
public:
    std::vector<Subject> subjects;

};

class Student
{
public:
    Student();
    Student(QString setName,long setId);

    QString name;
    long long id;

    std::vector<Exam> exams;
};

#endif // STUDENT_H
