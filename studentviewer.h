#ifndef STUDENTVIEWER_H
#define STUDENTVIEWER_H

#include<QWidget>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTabWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QToolButton>

#include "database.h"

class StudentTable : public QTableWidget
{
    Q_OBJECT
public:
    StudentTable(QWidget *parent = nullptr);
    StudentTable(Database *db,int setIndex,QWidget *parent = nullptr);

    Database *database;
    int index = 0;
private slots:
    void m_dataChanged(int row,int column);

};

class StudentViewer : public QWidget
{
    Q_OBJECT

public:
    StudentViewer(QWidget *parent = nullptr);
    StudentViewer(Database *db,QWidget *parent = nullptr);

    Database *database;
    QToolBar *toolbar;
    QTabWidget *tab;
};

#endif // STUDENTVIEWER_H
