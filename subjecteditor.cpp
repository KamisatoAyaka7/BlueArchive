#include "subjecteditor.h"

#include "utils.h"

#include <QMessageBox>

QString SubjectEditorTable::getItemText(int row,int column)
{
    return item(row,column)->text();
}

SubjectEditorTable::SubjectEditorTable(Database *db,QWidget *parent)
{
    database = db;
    setParent(parent);

    setTableColor(this);

    setRowCount(database->exams.count());
    setVerticalHeaderLabels(database->exams);
    setColumnCount(database->students.size());
    setHorizontalHeaderLabels(getStudentNames(database));
}

SubjectEditorTable::SubjectEditorTable(QWidget *parent)
{
    setParent(parent);
}

void SubjectEditor::getNewSubject()
{
    database->subjects<<nameEdit->text();
    for(int i1=0;i1<database->students.size();i1++)
    {
        for(int i2=0;i2<database->exams.count();i2++)
        {
            bool ok = false;
            Subject newSub = text2Sub(table->getItemText(i2,i1),&ok);
            if(!ok)
            {
                QMessageBox::warning(this, tr("Error"), tr("Could not convert"));
                return;
            }
            database->students[i1].exams[i2].subjects.push_back(newSub);
        }
    }
}

SubjectEditor::SubjectEditor(Database *db,QWidget *parent)
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
    connect(nameEdit,&QLineEdit::returnPressed,this,&SubjectEditor::getNewSubject);

    confirmBtn = new QToolButton(this);
    confirmBtn->setText("Confirm");
    toolbar->addWidget(confirmBtn);
    connect(confirmBtn,&QToolButton::clicked,this,&SubjectEditor::getNewSubject);

    table = new SubjectEditorTable(database,this);
    layout->addWidget(table);
}
