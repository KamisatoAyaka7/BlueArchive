#ifndef UTILS_H
#define UTILS_H

#include "QTableWidgetItem"

#include "student.h"
#include "database.h"

QTableWidgetItem *createAnItem(Student *stu,int subIndex,int examIndex);
QTableWidgetItem *createAnItem(Subject *subject);
Subject text2Sub(QString text,bool *ok);
QString sub2Text(Subject *subject);
bool checkText2Sub(QString text);
void setItemColor(QTableWidgetItem *item,Subject *sub);
QStringList getStudentNames(Database *db);
QString getFileText(QString path);
void setTableColor(QTableWidget *table);

#endif // UTILS_H
