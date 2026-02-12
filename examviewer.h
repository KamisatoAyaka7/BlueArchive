#ifndef EXAMVIEWER_H
#define EXAMVIEWER_H

#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTabWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QToolButton>

#include "database.h"

class ExamTable : public QTableWidget
{
    Q_OBJECT
public:
    ExamTable(QWidget *parent = nullptr);
    ExamTable(Database *db,int setIndex,QWidget *parent = nullptr);

    Database *database;
    int index = 0;

private slots:
    void m_dataChanged(int row,int column);
};

class ExamViewer : public QWidget
{
    Q_OBJECT
public:
    ExamViewer(QWidget *parent = nullptr);
    ExamViewer(Database *db,QWidget *parent = nullptr);

    Database *database;
    QToolBar *toolbar;
    QTabWidget *tab;
};

#endif // EXAMVIEWER_H
