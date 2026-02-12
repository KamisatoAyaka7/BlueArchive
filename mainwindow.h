#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString setPath,QWidget *parent = nullptr);
    ~MainWindow();

    QString path;
    Database *database;
    QToolBar *toolbar;

private:
    void showStudentViewer();
    void showSubjectViewer();
    void showExamViewer();

    void createMenuToolBar();

    bool init();
};
#endif // MAINWINDOW_H
