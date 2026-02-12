#include "studentviewer.h"

#include "utils.h"

void StudentTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    if(sub2Text(&database->students[index].exams[row].subjects[column]) == newText)
        return;
    database->f_dataChanged(index,row,column,text2Sub(newText));
    setItemColor(item(row,column));
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
}

StudentTable::StudentTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&StudentTable::m_dataChanged);
}

StudentViewer::StudentViewer(QWidget *parent)
{
    setParent(parent);
}

StudentViewer::StudentViewer(Database *db,QWidget *parent)
{
    setParent(parent);
    database = db;

    QVBoxLayout *layout = new QVBoxLayout(this);

    toolbar = new QToolBar("",this);
    toolbar->setMovable(false);

    QToolButton *btn = new QToolButton(this);
    btn->setText("close");
    connect(btn,&QToolButton::clicked,this,&QWidget::close);
    toolbar->addWidget(btn);

    tab = new QTabWidget(this);
    for(int i1=0;i1<database->students.size();i1++)
    {
        tab->addTab(new StudentTable(database,i1,this),database->students[i1].name);
        tab->setTabToolTip(i1,QString::number(database->students[i1].id));
    }

    layout->addWidget(toolbar);
    layout->addWidget(tab);
    setLayout(layout);
}
