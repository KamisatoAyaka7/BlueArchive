#include "student.h"

void Subject::setGoalScore(double setScore)
{
    goalScore = setScore*10;
}

void Subject::setRealScore(double setScore)
{
    realScore = setScore*10;
}

double Subject::toGoalScore()
{
    return static_cast<double>(goalScore)/10;
}

double Subject::toRealScore()
{
    return static_cast<double>(realScore)/10;
}

Subject::Subject(short gR,short rR,double gS,double rS)
{
    goalRank = gR;
    realRank = rR;
    setGoalScore(gS);
    setRealScore(rS);
}

Subject::Subject()
{
    Subject(0,0,0,0);
}

Student::Student(QString setName,QString setId)
{
    name = setName;
    id = setId;
}

Student::Student()
{
    Student("",0);
}
