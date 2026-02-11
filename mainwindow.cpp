#include "mainwindow.h"

#include "studentviewer.h"
#include "subjectviewer.h"
#include "examviewer.h"

#include <QDir>
#include <QCoreApplication>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

bool MainWindow::init()
{
    database = new Database(path);
    return database->readAll();
}

void MainWindow::showStudentViewer()
{
    StudentViewer *viewer = new StudentViewer(database);
    viewer->show();
}

void MainWindow::showSubjectViewer()
{
    SubjectViewer *viewer = new SubjectViewer(database);
    viewer->show();
}

void MainWindow::showExamViewer()
{
    ExamViewer *viewer = new ExamViewer(database);
    viewer->show();
}

MainWindow::MainWindow(QString setPath,QWidget *parent)
    : QMainWindow(parent)
{
    path = setPath;
    if(!init())
        QMessageBox::warning(this, tr("Error"), tr("Could not init"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    {
        QHBoxLayout *hlayout = new QHBoxLayout(this);
        QToolButton *btn1 = new QToolButton(this);
        btn1->setText("ViewStudents");
        hlayout->addWidget(btn1);

        QToolButton *btn2 = new QToolButton(this);
        btn2->setText("ViewSubjects");
        hlayout->addWidget(btn2);

        QToolButton *btn3 = new QToolButton(this);
        btn3->setText("ViewExams");
        hlayout->addWidget(btn3);

        connect(btn1,&QToolButton::clicked,this,&MainWindow::showStudentViewer);
        connect(btn2,&QToolButton::clicked,this,&MainWindow::showSubjectViewer);
        connect(btn3,&QToolButton::clicked,this,&MainWindow::showExamViewer);

        layout->addLayout(hlayout);
    }

    setLayout(layout);
}

MainWindow::~MainWindow() {}
