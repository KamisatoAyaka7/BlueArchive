#include "subjectviewer.h"

#include "utils.h"

#include <QMessageBox>

SubjectTable::SubjectTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

    setEditTriggers(QAbstractItemView::AllEditTriggers);

    setRowCount(database->exams.count());
    setVerticalHeaderLabels(database->exams);
    setColumnCount(database->students.size());
    QStringList stuNameList;
    for(int i1=0;i1<database->students.size();i1++)
    {
        stuNameList<<database->students[i1].name;
        for(int i2=0;i2<database->exams.size();i2++)
        {
            setItem(i2,i1,createAnItem(&database->students[i1],index,i2));
        }
    }
    setHorizontalHeaderLabels(stuNameList);

    connect(this,&QTableWidget::cellChanged,this,&SubjectTable::m_dataChanged);
}

SubjectTable::SubjectTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&SubjectTable::m_dataChanged);
}

void SubjectTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    if(sub2Text(&database->students[column].exams[row].subjects[index])==newText)
        return;
    bool ok=false;
    Subject newSub = text2Sub(newText,&ok);
    if(!ok)
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not convert"));
        return;
    }
    database->f_dataChanged(column,row,index,newSub);
    setItemColor(item(row,column),&newSub);
}

SubjectViewer::SubjectViewer(Database *db,QWidget *parent)
{
    setParent(parent);
    database = db;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QToolButton *btn = new QToolButton(this);
    btn->setText("close");
    connect(btn,&QToolButton::clicked,this,&QWidget::close);

    tab = new QTabWidget(this);
    tab->setMovable(true);
    for(int i1=0;i1<database->subjects.count();i1++)
    {
        tab->addTab(new SubjectTable(database,i1,this),database->subjects[i1]);
    }

    layout->addWidget(tab);
    setLayout(layout);
}

SubjectViewer::SubjectViewer(QWidget *parent)
{
    setParent(parent);
}
