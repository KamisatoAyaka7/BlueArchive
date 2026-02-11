#include "subjectviewer.h"

#include "utils.h"

SubjectTable::SubjectTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

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
    connect(database,&Database::s_dataChanged,this,&SubjectTable::getDataChanged);
}

SubjectTable::SubjectTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&SubjectTable::m_dataChanged);
    connect(database,&Database::s_dataChanged,this,&SubjectTable::getDataChanged);
}

void SubjectTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    database->f_dataChanged(column,row,index,text2Sub(newText));
}

void SubjectTable::getDataChanged(int stu,int exam,int sub)
{
    if(sub!=index)
        return;
    Subject *subject = &database->students[stu].exams[exam].subjects[sub];
    item(exam,stu)->setText(sub2Text(subject));
}

SubjectViewer::SubjectViewer(Database *db,QWidget *parent)
{
    setParent(parent);
    database = db;

    tab = new QTabWidget(this);
    for(int i1=0;i1<database->subjects.count();i1++)
    {
        tab->addTab(new SubjectTable(database,i1,this),database->subjects[i1]);
    }
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tab);
    setLayout(layout);
}

SubjectViewer::SubjectViewer(QWidget *parent)
{
    setParent(parent);
}
