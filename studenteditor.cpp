#include "studenteditor.h"

#include "utils.h"

QString StudentEditorTable::getItemText(int row,int column)
{
    return item(row,column)->text();
}

StudentEditorTable::StudentEditorTable(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

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
    stu.name = nameEdit->text();
    for(int i1=0;i1<database->exams.count();i1++)
    {
        Exam exam;
        for(int i2=0;i2<database->subjects.count();i2++)
        {
            exam.subjects.push_back(text2Sub(table->getItemText(i1,i2)));
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
