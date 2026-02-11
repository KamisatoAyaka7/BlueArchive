#ifndef UTILS_H
#define UTILS_H

#include "QTableWidgetItem"

#include "student.h"

QTableWidgetItem *createAnItem(Student *stu,int subIndex,int examIndex);
QTableWidgetItem *createAnItem(Subject *subject);
Subject text2Sub(QString text);
QString sub2Text(Subject *subject);

#endif // UTILS_H
