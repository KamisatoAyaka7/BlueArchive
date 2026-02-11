#ifndef SUBJECTVIEWER_H
#define SUBJECTVIEWER_H

#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTabWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>

#include "database.h"

class SubjectTable : public QTableWidget
{
    Q_OBJECT
public:
    SubjectTable(QWidget *parent = nullptr);
    SubjectTable(Database *db,int setIndex,QWidget *parent = nullptr);

    Database *database;
    int index = 0;
private slots:
    void m_dataChanged(int row,int column);
    void getDataChanged(int stu,int exam,int sub);
};

class SubjectViewer : public QWidget
{
    Q_OBJECT
public:
    SubjectViewer(QWidget *parent = nullptr);
    SubjectViewer(Database *db,QWidget *parent = nullptr);

    Database *database;
    QTabWidget *tab;
};

#endif // SUBJECTVIEWER_H
