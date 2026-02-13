#include "studenteditor.h"

#include "utils.h"

#include <QMessageBox>

QString StudentEditorTable::getItemText(int row,int column)
{
    return item(row,column)->text();
}

StudentEditorTable::StudentEditorTable(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

    setTableColor(this);

    setRowCount(database->exams.count());
    setVerticalHeaderLabels(database->exams);
    setColumnCount(database->subjects.count());
    setHorizontalHeaderLabels(database->subjects);
}

StudentEditorTable::StudentEditorTable(QWidget *parent)
{
    setParent(parent);
}

void StudentEditor::getNewStudent()
{
    Student stu;
    stu.id = idEdit->text();
    if(stu.id.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Student's id can't be empty"));
        return;
    }
    for(int i1=0;i1<database->students.size();i1++)
    {
        if(database->students[i1].id==stu.id)
        {
            QMessageBox::warning(this, tr("Error"), tr("Student already exists"));
            return;
        }
    }
    stu.name = nameEdit->text();
    for(int i1=0;i1<database->exams.count();i1++)
    {
        Exam exam;
        for(int i2=0;i2<database->subjects.count();i2++)
        {
            bool ok=false;
            Subject newSub = text2Sub(table->getItemText(i1,i2),&ok);
            if(!ok)
            {
                QMessageBox::warning(this, tr("Error"), tr("Could not convert"));
                return;
            }
            exam.subjects.push_back(newSub);
        }
        stu.exams.push_back(exam);
    }
    database->students.push_back(stu);
}

StudentEditor::StudentEditor(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    toolbar = new QToolBar(this);
    layout->addWidget(toolbar);

    closeBtn = new QToolButton(this);
    closeBtn->setText("close");
    connect(closeBtn,&QToolButton::clicked,this,&QWidget::close);
    toolbar->addWidget(closeBtn);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("name");
    toolbar->addWidget(nameEdit);
    connect(nameEdit,&QLineEdit::returnPressed,this,&StudentEditor::getNewStudent);

    idEdit = new QLineEdit(this);
    idEdit->setPlaceholderText("id");
    toolbar->addWidget(idEdit);
    connect(idEdit,&QLineEdit::returnPressed,this,&StudentEditor::getNewStudent);

    confirmBtn = new QToolButton(this);
    confirmBtn->setText("Confirm");
    toolbar->addWidget(confirmBtn);
    connect(confirmBtn,&QToolButton::clicked,this,&StudentEditor::getNewStudent);

    table = new StudentEditorTable(database,this);
    layout->addWidget(table);
}
