#include "examviewer.h"

#include "utils.h"

#include "QMessageBox"

ExamTable::ExamTable(Database *db,int setIndex,QWidget *parent)
{
    setParent(parent);
    index = setIndex;
    database = db;

    setEditTriggers(QAbstractItemView::AllEditTriggers);

    setRowCount(database->subjects.count());
    setVerticalHeaderLabels(database->subjects);
    setColumnCount(database->students.size());
    QStringList stuNameList={};
    for(int i1=0;i1<database->students.size();i1++)
    {
        stuNameList<<database->students[i1].name;
        for(int i2=0;i2<database->subjects.size();i2++)
        {
            setItem(i2,i1,createAnItem(&database->students[i1],i2,index));
        }
    }
    setHorizontalHeaderLabels(stuNameList);
    connect(this,&QTableWidget::cellChanged,this,&ExamTable::m_dataChanged);
}

ExamTable::ExamTable(QWidget *parent)
{
    setParent(parent);
    connect(this,&QTableWidget::cellChanged,this,&ExamTable::m_dataChanged);
}

void ExamTable::m_dataChanged(int row,int column)
{
    QString newText = item(row,column)->text();
    if(sub2Text(&database->students[column].exams[index].subjects[row])==newText)
        return;
    bool ok=false;
    Subject newSub = text2Sub(newText,&ok);
    if(!ok)
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not convert"));
        return;
    }
    database->f_dataChanged(column,index,row,newSub);
    setItemColor(item(row,column),&newSub);
}

ExamViewer::ExamViewer(Database *db,QWidget *parent)
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
    for(int i1=0;i1<database->exams.count();i1++)
    {
        tab->addTab(new ExamTable(database,i1,this),database->exams[i1]);
    }

    layout->addWidget(tab);
    setLayout(layout);
}

ExamViewer::ExamViewer(QWidget *parent)
{
    setParent(parent);
}
