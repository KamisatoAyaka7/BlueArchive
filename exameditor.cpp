#include "exameditor.h"

#include "utils.h"

#include "QMessageBox"

QString ExamEditorTable::getItemText(int row,int column)
{
    return item(row,column)->text();
}

ExamEditorTable::ExamEditorTable(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

    setTableColor(this);

    setRowCount(database->subjects.count());
    setVerticalHeaderLabels(database->subjects);
    setColumnCount(database->students.size());
    setHorizontalHeaderLabels(getStudentNames(database));

    createTableItems(this);
}

ExamEditorTable::ExamEditorTable(QWidget *parent)
{
    setParent(parent);
}

void ExamEditor::getNewExam()
{
    database->exams<<nameEdit->text();
    bool ok=false;
    for(unsigned int i1=0;i1<database->students.size();i1++)
    {
        Exam exam;
        for(unsigned int i2=0;i2<database->subjects.count();i2++)
        {
            Subject newSub = text2Sub(table->getItemText(i2,i1),&ok);
            if(!ok)
            {
                QString info = "Could not convert:\n";
                info+="cell: row:"+QString::number(i2+1)+" column:"+QString::number(i1+1);
                QMessageBox::warning(this, tr("Error"), info);
            }
            exam.subjects.push_back(newSub);
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
