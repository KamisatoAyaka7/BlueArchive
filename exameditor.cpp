#include "exameditor.h"

#include "utils.h"

QString ExamEditorTable::getItemText(int row,int column)
{
    return item(row,column)->text();
}

ExamEditorTable::ExamEditorTable(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

    setRowCount(database->subjects.count());
    setVerticalHeaderLabels(database->subjects);
    setColumnCount(database->students.size());
    setHorizontalHeaderLabels(getStudentNames(database));
}

ExamEditorTable::ExamEditorTable(QWidget *parent)
{
    setParent(parent);
}

void ExamEditor::getNewExam()
{
    database->exams<<nameEdit->text();
    for(int i1=0;i1<database->students.size();i1++)
    {
        Exam exam;
        for(int i2=0;i2<database->subjects.count();i2++)
        {
            exam.subjects.push_back(text2Sub(table->getItemText(i2,i1)));
        }
        database->students[i1].exams.push_back(exam);
    }
}

ExamEditor::ExamEditor(Database *db,QWidget *parent)
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
    connect(nameEdit,&QLineEdit::returnPressed,this,&ExamEditor::getNewExam);

    confirmBtn = new QToolButton(this);
    confirmBtn->setText("Confirm");
    toolbar->addWidget(confirmBtn);
    connect(confirmBtn,&QToolButton::clicked,this,&ExamEditor::getNewExam);

    table = new ExamEditorTable(database,this);
    layout->addWidget(table);
}
