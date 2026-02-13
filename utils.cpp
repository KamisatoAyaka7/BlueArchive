#include "utils.h"

QTableWidgetItem *createAnItem(Student *stu,int subIndex,int examIndex)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    Subject *subject = &stu->exams[examIndex].subjects[subIndex];
    item->setText(sub2Text(subject));
    setItemColor(item,subject);
    return item;
}

QTableWidgetItem *createAnItem(Subject *subject)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(sub2Text(subject));
    setItemColor(item,subject);
    return item;
}

//abondoned
bool checkText2Sub(QString text)
{
    QStringList list = text.split(",");
    if(list.count()!=2)
        return false;
    QStringList list1 = list[0].split("/"),
        list2 = list[1].split("/");
    if(list1.count()!=2||list2.count()!=2)
        return false;
    return true;
}

Subject text2Sub(QString text,bool *ok)
{
    Subject newSub;
    bool ok1=false,ok2=true,ok3=true,ok4=true,ok5=true;
    QStringList list0 = text.split(",");
    if(list0.count()==2)
    {
        QStringList list1 = list0[0].split("/"),list2 = list0[1].split("/");
        if(list1.count()==1&&list2.count()==1)
        {
            newSub.setRealScore(text.split(",")[0].toDouble(&ok2));
            newSub.setGoalScore(0);
            newSub.realRank = text.split(",")[1].toInt(&ok4);
            newSub.goalRank = 0;
            ok1=true;
        }
        else if(list1.count()==1&&list2.count()==1)
        {
            newSub.setRealScore(text.split(",")[0].split("/")[0].toDouble(&ok2));
            newSub.setGoalScore(text.split(",")[0].split("/")[1].toDouble(&ok3));
            newSub.realRank = text.split(",")[1].split("/")[0].toInt(&ok4);
            newSub.goalRank = text.split(",")[1].split("/")[1].toInt(&ok5);
            ok1=true;
        }
    }
    *ok = ok1&&ok2&&ok3&&ok4&&ok5;
    return newSub;
}

QString sub2Text(Subject *subject)
{
    if(subject->goalRank==0||subject->goalScore==0)
    {
        return QString::number(subject->toRealScore())+","+
               QString::number(subject->realRank);
    }
    else
    {
    return QString::number(subject->toRealScore())+"/"+
            QString::number(subject->toGoalScore())+","+
            QString::number(subject->realRank)+"/"+
            QString::number(subject->goalRank);
    }
}

void setItemColor(QTableWidgetItem *item,Subject *sub)
{
    item->setBackground(QBrush(QColor("#ffffe9")));
    if(sub->goalRank==0||sub->goalScore==0)
        return;
    if(sub->goalRank<sub->realRank)
    {
        item->setBackground(QBrush(QColor("#fff894")));
        if(sub->goalScore>sub->realScore)
        {
            item->setBackground(QBrush(QColor("#ffda7d")));
        }
    }
    else if(sub->goalScore>sub->realScore)
    {
        item->setBackground(QBrush(QColor("#bbffc0")));
    }
}

QStringList getStudentNames(Database *db)
{
    QStringList names;
    for(int i=0;i<db->students.size();i++)
    {
        names<<db->students[i].name;
    }
    return names;
}

QString getFileText(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    QString str = QString::fromUtf8(file.readAll());
    file.close();
    return str;
}

void setTableColor(QTableWidget *table)
{
    for(int i1=0;i1<table->rowCount();i1++)
    {
        for(int i2=0;i2<table->columnCount();i2++)
        {
            table->item(i1,i2)->setBackground(QBrush(QColor("#ffffe9")));
        }
    }
    table->setAlternatingRowColors(true);
}
