#include "utils.h"

QTableWidgetItem *createAnItem(Student *stu,int subIndex,int examIndex)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    Subject *subject = &stu->exams[examIndex].subjects[subIndex];
    item->setText(sub2Text(subject));
    setItemColor(item);
    return item;
}

QTableWidgetItem *createAnItem(Subject *subject)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(sub2Text(subject));
    setItemColor(item);
    return item;
}

Subject text2Sub(QString text)
{
    Subject newSub;
    newSub.setRealScore(text.split(",")[0].split("/")[0].toDouble());
    newSub.setGoalScore(text.split(",")[0].split("/")[1].toDouble());
    newSub.realRank = text.split(",")[1].split("/")[0].toInt();
    newSub.goalRank = text.split(",")[1].split("/")[1].toInt();
    return newSub;
}

QString sub2Text(Subject *subject)
{
    return QString::number(subject->toRealScore())+"/"+
            QString::number(subject->toGoalScore())+","+
            QString::number(subject->realRank)+"/"+
            QString::number(subject->goalRank);
}

void setItemColor(QTableWidgetItem *item)
{
    Subject subject = text2Sub(item->text());
    if(subject.goalRank<subject.realRank)
    {
        item->setBackground(QBrush(Qt::red));
        if(subject.goalScore>subject.realScore)
        {
            item->setBackground(QBrush(Qt::blue));
        }
    }
    else if(subject.goalScore>subject.realScore)
    {
        item->setBackground(QBrush(Qt::yellow));
    }
}
