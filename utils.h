#ifndef UTILS_H
#define UTILS_H

#include "QTableWidgetItem"

#include "student.h"
#include "database.h"

QTableWidgetItem *createAnItem(Student *stu,int subIndex,int examIndex);
QTableWidgetItem *createAnItem(Subject *subject);
Subject text2Sub(QString text);
QString sub2Text(Subject *subject);
void setItemColor(QTableWidgetItem *item);
QStringList getStudentNames(Database *db);

#endif // UTILS_H
