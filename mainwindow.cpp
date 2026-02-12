#include "mainwindow.h"

#include "studentviewer.h"
#include "subjectviewer.h"
#include "examviewer.h"

#include "studenteditor.h"
#include "subjecteditor.h"
#include "exameditor.h"

#include "confirmbox.h"

#include "utils.h"

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
#include <QTextBrowser>
#include <QShortcut>
#include <QStatusBar>

#define PATH QCoreApplication::applicationDirPath()

bool MainWindow::init()
{
    database = new Database(path);
    return database->readAll();
}

void MainWindow::saveData()
{
    qDebug()<<1;
    if(database->writeAll())
    {
        statusBar()->showMessage("Saved successfully",2000);
    }
}

void MainWindow::readData()
{
    database->readAll();
}

template<typename viewerType>
void MainWindow::showWidget()
{
    if(centralWidget()!=nullptr)
        centralWidget()->close();
    viewerType *viewer = new viewerType(database,this);
    viewer->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(viewer);
    viewer->show();
}

void MainWindow::showStudentViewer()
{
    showWidget<StudentViewer>();
}

void MainWindow::showSubjectViewer()
{
    showWidget<SubjectViewer>();
}

void MainWindow::showExamViewer()
{
    showWidget<ExamViewer>();
}

void MainWindow::showStudentEditor()
{
    showWidget<StudentEditor>();
}

void MainWindow::showExamEditor()
{
    showWidget<ExamEditor>();
}

void MainWindow::showSubjectEditor()
{
    showWidget<SubjectEditor>();
}

void MainWindow::deleteStudent()
{
    ConfirmBox *box = new ConfirmBox("Enter student's id");
    if(box->exec()==QDialog::Accepted)
        database->deleteStudent(box->toConfirmInfo());
    box->deleteLater();
}

void MainWindow::deleteExam()
{
    ConfirmBox *box = new ConfirmBox("Enter Exam name");
    if(box->exec()==QDialog::Accepted)
        database->deleteExam(box->toConfirmInfo());
    box->deleteLater();
}

void MainWindow::deleteSubject()
{
    ConfirmBox *box = new ConfirmBox("Enter Subject name");
    if(box->exec()==QDialog::Accepted)
        database->deleteSubject(box->toConfirmInfo());
    box->deleteLater();
}

void MainWindow::createMenuToolBar()
{
    toolbar = addToolBar("Menu");
    toolbar->setMovable(false);

    {
        QMenu *fileMenu = new QMenu("file",this);

        QAction *readAction = fileMenu->addAction("Read");
        connect(readAction,&QAction::triggered,this,&MainWindow::readData);

        QAction *saveAction = fileMenu->addAction("Save");
        connect(saveAction,&QAction::triggered,this,&MainWindow::saveData);

        fileMenu->addSeparator();
        QAction *exitAction = fileMenu->addAction("Exit");
        connect(exitAction,&QAction::triggered,this,&QWidget::close);

        QToolButton *fileBtn = new QToolButton(this);
        fileBtn->setMenu(fileMenu);
        fileBtn->setPopupMode(QToolButton::InstantPopup);
        fileBtn->setText("file");
        toolbar->addWidget(fileBtn);
    }

    {
        QMenu *viewMenu = new QMenu("view",this);

        QAction *viewStu = viewMenu->addAction("ViewStudents");
        connect(viewStu,&QAction::triggered,this,&MainWindow::showStudentViewer);

        QAction *viewExam = viewMenu->addAction("ViewExams");
        connect(viewExam,&QAction::triggered,this,&MainWindow::showExamViewer);

        QAction *viewSub = viewMenu->addAction("ViewSubjects");
        connect(viewSub,&QAction::triggered,this,&MainWindow::showSubjectViewer);

        viewMenu->addSeparator();
        QAction *closeAll = viewMenu->addAction("CloseAll");
        connect(closeAll,&QAction::triggered,this,[=](){
            if(centralWidget()!=nullptr)
                centralWidget()->close();
        });

        QToolButton *viewBtn = new QToolButton(this);
        viewBtn->setMenu(viewMenu);
        viewBtn->setPopupMode(QToolButton::InstantPopup);
        viewBtn->setText("view");
        toolbar->addWidget(viewBtn);
    }

    {
        QMenu *editMenu = new QMenu("edit",this);

        QAction *stuAddAction = editMenu->addAction("AddStudent");
        connect(stuAddAction,&QAction::triggered,this,&MainWindow::showStudentEditor);
        QAction *stuDelAction = editMenu->addAction("DeleteStudent");
        connect(stuDelAction,&QAction::triggered,this,&MainWindow::deleteStudent);
        editMenu->addSeparator();

        QAction *examAddAction = editMenu->addAction("AddExam");
        connect(examAddAction,&QAction::triggered,this,&MainWindow::showExamEditor);
        QAction *examDelAction = editMenu->addAction("DeleteExam");
        connect(examDelAction,&QAction::triggered,this,&MainWindow::deleteExam);
        editMenu->addSeparator();

        QAction *subAddAction = editMenu->addAction("AddSubject");
        connect(subAddAction,&QAction::triggered,this,&MainWindow::showSubjectEditor);
        QAction *subDelAction = editMenu->addAction("DeleteSubject");
        connect(subDelAction,&QAction::triggered,this,&MainWindow::deleteSubject);

        QToolButton *editBtn = new QToolButton(this);
        editBtn->setMenu(editMenu);
        editBtn->setPopupMode(QToolButton::InstantPopup);
        editBtn->setText("edit");
        toolbar->addWidget(editBtn);
    }

    {
        QMenu *aboutMenu = new QMenu("about",this);

        QAction *aboutAction = aboutMenu->addAction("About");
        connect(aboutAction,&QAction::triggered,this,[=](){
            QTextBrowser *broswer = new QTextBrowser(this);
            if(centralWidget()!=nullptr)
                centralWidget()->close();
            broswer->setText(getFileText(QDir::cleanPath(PATH+"/data/about.txt")));
            setCentralWidget(broswer);
            broswer->show();
        });

        QAction *helpAction = aboutMenu->addAction("Help");
        connect(helpAction,&QAction::triggered,this,[=](){
            QTextBrowser *broswer = new QTextBrowser(this);
            if(centralWidget()!=nullptr)
                centralWidget()->close();
            broswer->setText(getFileText(QDir::cleanPath(PATH+"/data/help.txt")));
            setCentralWidget(broswer);
        });

        QToolButton *aboutBtn = new QToolButton(this);
        aboutBtn->setMenu(aboutMenu);
        aboutBtn->setText("about");
        aboutBtn->setPopupMode(QToolButton::InstantPopup);
        toolbar->addWidget(aboutBtn);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QPixmap pixmap(PATH+"/data/bg.png");
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(pixmap.scaled(this->size(),
                                          Qt::IgnoreAspectRatio,
                                          Qt::SmoothTransformation)));
    this->setPalette(palette);
}

void MainWindow::bindShortCuts()
{
    QShortcut *saveShortCut = new QShortcut(QKeySequence::Save,this);
    connect(saveShortCut,&QShortcut::activated,this,&MainWindow::saveData);

    QShortcut *readShortCut = new QShortcut(QKeySequence("Ctrl+r"),this);
    connect(readShortCut,&QShortcut::activated,this,&MainWindow::readData);

    QShortcut *helpShortCut = new QShortcut(QKeySequence("F1"),this);
    connect(helpShortCut,&QShortcut::activated,this,[=](){
            QTextBrowser *broswer = new QTextBrowser(this);
            if(centralWidget()!=nullptr)
                centralWidget()->close();
            broswer->setText(getFileText(QDir::cleanPath(PATH+"/data/help.txt")));
            setCentralWidget(broswer);
    });
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"),2000);
    statusBar()->setSizeGripEnabled(false);
}

MainWindow::MainWindow(QString setPath,QWidget *parent)
    : QMainWindow(parent)
{
    path = setPath;
    if(!init())
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not init"));
        close();
    }
    createMenuToolBar();
    createStatusBar();

    setWindowIcon(QIcon("://logo.ico"));
    setFont(QFont("Monospace",12,1));
    resize(800,450);
}

MainWindow::~MainWindow() {}
