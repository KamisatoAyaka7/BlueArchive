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
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QToolButton>

bool MainWindow::init()
{
    database = new Database(path);
    return database->readAll();
}

void MainWindow::showStudentViewer()
{
    //toolbar->hide();
    if(centralWidget()!=nullptr)
        centralWidget()->close();
    StudentViewer *viewer = new StudentViewer(database,this);
    setCentralWidget(viewer);
    viewer->show();
    qDebug()<<1;
}

void MainWindow::showSubjectViewer()
{
    //toolbar->hide();
    if(centralWidget()!=nullptr)
        centralWidget()->close();
    SubjectViewer *viewer = new SubjectViewer(database,this);
    setCentralWidget(viewer);
    viewer->show();
}

void MainWindow::showExamViewer()
{
   //toolbar->hide();
    if(centralWidget()!=nullptr)
        centralWidget()->close();
    ExamViewer *viewer = new ExamViewer(database,this);
    setCentralWidget(viewer);
    viewer->show();
}

void MainWindow::createMenuToolBar()
{
    toolbar = addToolBar("Menu");
    toolbar->setMovable(false);

    {
        QMenu *viewMenu = new QMenu("view",this);

        QAction *viewStu = viewMenu->addAction("ViewStudents");
        connect(viewStu,&QAction::triggered,this,&MainWindow::showStudentViewer);

        QAction *viewSub = viewMenu->addAction("ViewSubjects");
        connect(viewSub,&QAction::triggered,this,&MainWindow::showSubjectViewer);

        QAction *viewExam = viewMenu->addAction("ViewExams");
        connect(viewExam,&QAction::triggered,this,&MainWindow::showExamViewer);

        QToolButton *viewBtn = new QToolButton(this);
        viewBtn->setMenu(viewMenu);
        viewBtn->setPopupMode(QToolButton::InstantPopup);
        viewBtn->setText("view");
        toolbar->addWidget(viewBtn);
    }
}

MainWindow::MainWindow(QString setPath,QWidget *parent)
    : QMainWindow(parent)
{
    path = setPath;
    if(!init())
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not init"));
    }
    createMenuToolBar();
}

MainWindow::~MainWindow() {}
