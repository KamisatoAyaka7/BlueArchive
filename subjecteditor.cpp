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

    createTableItems(this);
}

SubjectEditorTable::SubjectEditorTable(QWidget *parent)
{
    setParent(parent);
}

void SubjectEditor::getNewSubject()
{
    database->subjects<<nameEdit->text();
    bool ok = false;
    for(unsigned int i1=0;i1<database->students.size();i1++)
    {
        for(unsigned int i2=0;i2<database->exams.count();i2++)
        {
            Subject newSub = text2Sub(table->getItemText(i2,i1),&ok);
            if(!ok)
            {
                QString info = "Could not convert:\n";
                info+="cell: row:"+QString::number(i2+1)+" column:"+QString::number(i1+1);
                QMessageBox::warning(this, tr("Error"), info);
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
