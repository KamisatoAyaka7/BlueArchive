#ifndef EXAMEDITOR_H
#define EXAMEDITOR_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "database.h"

class ExamEditorTable : public QTableWidget
{
    Q_OBJECT
public:
    ExamEditorTable(Database *db,QWidget *parent = nullptr);
    ExamEditorTable(QWidget *parent = nullptr);

    QString getItemText(int row,int column);

    Database *database;
};

class ExamEditor : public QWidget
{
    Q_OBJECT
public:
    ExamEditor(Database *db,QWidget *parent = nullptr);
    void getNewExam();

    Database *database;
    ExamEditorTable *table;
    QLineEdit *nameEdit;
    QToolButton *closeBtn,*confirmBtn;
    QToolBar *toolbar;
};

#endif // EXAMEDITOR_H
