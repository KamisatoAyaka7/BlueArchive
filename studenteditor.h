#ifndef STUDENTEDITOR_H
#define STUDENTEDITOR_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "database.h"

class StudentEditorTable : public QTableWidget
{
    Q_OBJECT
public:
    StudentEditorTable(Database *db,QWidget *parent = nullptr);
    StudentEditorTable(QWidget *parent = nullptr);

    QString getItemText(int row,int column);

    Database *database;
};

class StudentEditor : public QWidget
{
    Q_OBJECT
public:
    StudentEditor(Database *db,QWidget *parent = nullptr);
    void getNewStudent();

    Database *database;
    StudentEditorTable *table;
    QLineEdit *nameEdit,*idEdit;
    QToolButton *confirmBtn;
    QToolBar *toolbar;
};

#endif // STUDENTEDITOR_H
