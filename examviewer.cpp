#include "examviewer.h"

#include "utils.h"

ExamTable::ExamTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

    setRowCount(database->subjects.count());
    setVerticalHeaderLabels(database->subjects);
    setColumnCount(database->students.size());
    QStringList stuNameList;
    for(int i1=0;i1<database->students.size();i1++)
    {
        stuNameList<<database->students[i1].name;
        for(int i2=0;i2<database->subjects.size();i2++)
        {
            setItem(i2,i1,createAnItem(&database->students[i1],index,i2));
        }
    }
    setHorizontalHeaderLabels(stuNameList);
    connect(this,&QTableWidget::cellChanged,this,&ExamTable::m_dataChanged);
    connect(database,&Database::s_dataChanged,this,&ExamTable::getDataChanged);
}

ExamTable::ExamTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&ExamTable::m_dataChanged);
    connect(database,&Database::s_dataChanged,this,&ExamTable::getDataChanged);
}

void ExamTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    database->f_dataChanged(column,index,row,text2Sub(newText));
}

void ExamTable::getDataChanged(int stu,int exam,int sub)
{
    if(exam!=index)
        return;
    Subject *subject = &database->students[stu].exams[exam].subjects[sub];
    item(sub,stu)->setText(sub2Text(subject));
}

ExamViewer::ExamViewer(Database *db,QWidget *parent)
{
    setParent(parent);
    database = db;

    tab = new QTabWidget(this);
    for(int i1=0;i1<database->exams.count();i1++)
    {
        tab->addTab(new ExamTable(database,i1,this),database->exams[i1]);
    }
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tab);
    setLayout(layout);
}

ExamViewer::ExamViewer(QWidget *parent)
{
    setParent(parent);
}
