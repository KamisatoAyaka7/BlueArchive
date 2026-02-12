#ifndef SUBJECTEDITOR_H
#define SUBJECTEDITOR_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "database.h"

class SubjectEditorTable : public QTableWidget
{
    Q_OBJECT
public:
    SubjectEditorTable(Database *db,QWidget *parent = nullptr);
    SubjectEditorTable(QWidget *parent = nullptr);

    QString getItemText(int row,int column);

    Database *database;
};

class SubjectEditor : public QWidget
{
    Q_OBJECT
public:
    SubjectEditor(Database *db,QWidget *parent = nullptr);
    void getNewSubject();

    Database *database;
    SubjectEditorTable *table;
    QLineEdit *nameEdit;
    QToolButton *closeBtn,*confirmBtn;
    QToolBar *toolbar;
};

#endif // SUBJECTEDITOR_H
