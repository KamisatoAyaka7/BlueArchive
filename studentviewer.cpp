#include "studentviewer.h"

#include "utils.h"

#include <QMessageBox>

void StudentTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    if(sub2Text(&database->students[index].exams[row].subjects[column]) == newText)
        return;
    bool ok=false;
    Subject newSub = text2Sub(newText,&ok);
    if(!ok)
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not convert"));
        return;
    }
    database->f_dataChanged(index,row,column,newSub);
    setItemColor(item(row,column),&newSub);
}

StudentTable::StudentTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

    setEditTriggers(QAbstractItemView::AllEditTriggers);

    setRowCount(database->exams.count());
    setVerticalHeaderLabels(database->exams);
    setColumnCount(database->subjects.count());
    setHorizontalHeaderLabels(database->subjects);

    for(unsigned int i1=0;i1<database->exams.count();i1++)
    {
        for(unsigned int i2=0;i2<database->subjects.count();i2++)
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
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    tab = new QTabWidget(this);
    tab->setMovable(true);
    for(unsigned int i1=0;i1<database->students.size();i1++)
    {
        tab->addTab(new StudentTable(database,i1,this),database->students[i1].name);
        tab->setTabToolTip(i1,database->students[i1].id);
    }

    layout->addWidget(tab);
    setLayout(layout);
}
