#include "studentviewer.h"

#include "utils.h"

void StudentTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    database->f_dataChanged(index,row,column,text2Sub(newText));
}

void StudentTable::getDataChanged(int stu,int exam,int sub)
{
    if(stu!=index)
        return;
    Subject *subject = &database->students[stu].exams[exam].subjects[sub];
    item(exam,sub)->setText(sub2Text(subject));
}

StudentTable::StudentTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

    setRowCount(database->exams.count());
    setVerticalHeaderLabels(database->exams);
    setColumnCount(database->subjects.count());
    setHorizontalHeaderLabels(database->subjects);

    for(int i1=0;i1<database->exams.count();i1++)
    {
        for(int i2=0;i2<database->subjects.count();i2++)
        {
            setItem(i1,i2,createAnItem(&database->students[index],i2,i1));
        }
    }

    connect(this,&QTableWidget::cellChanged,this,&StudentTable::m_dataChanged);
    connect(database,&Database::s_dataChanged,this,&StudentTable::getDataChanged);
}

StudentTable::StudentTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&StudentTable::m_dataChanged);
    connect(database,&Database::s_dataChanged,this,&StudentTable::getDataChanged);
}

StudentViewer::StudentViewer(QWidget *parent)
{
    setParent(parent);
}

StudentViewer::StudentViewer(Database *db,QWidget *parent)
{
    setParent(parent);
    database = db;

    tab = new QTabWidget(this);
    for(int i1=0;i1<database->students.size();i1++)
    {
        tab->addTab(new StudentTable(database,i1,this),database->students[i1].name);
        tab->setTabToolTip(i1,QString::number(database->students[i1].id));
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tab);
    setLayout(layout);
}
