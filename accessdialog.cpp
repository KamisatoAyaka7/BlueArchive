#include "accessdialog.h"

#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

QStringList AccessDialog::getClasses()
{
    QDir dataDir(QCoreApplication::applicationDirPath()+"/data/");
    return dataDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}

QString AccessDialog::toSelectedClass()
{
    return classBox->currentText();
}

void AccessDialog::createNewClass(QString name)
{
    QString folderPath = QDir::cleanPath(QCoreApplication::applicationDirPath()+"/data/"+name);
    QDir dir;
    if(dir.exists(folderPath)||name.isEmpty())
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not create"));
        return;
    }
    dir.mkdir(folderPath);
    QFile basic(QDir::cleanPath(folderPath+"/basic.json"));
    if(!basic.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Could not create"));
        return;
    }
    basic.write("{\"subjects\":[],\"exams\":[]}");
    basic.close();
    dir.mkdir(QDir::cleanPath(folderPath+"/students_data"));
    classBox->addItem(name);
}

AccessDialog::AccessDialog(QWidget *parent)
{
    setParent(parent);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QHBoxLayout *selectLayout = new QHBoxLayout(this);
    classBox = new QComboBox(this);
    classBox->addItems(getClasses());
    selectLayout->addWidget(classBox);
    selectBtn = new QToolButton(this);
    selectBtn->setText("Login");
    selectLayout->addWidget(selectBtn);
    layout->addLayout(selectLayout);

    QHBoxLayout *createLayout = new QHBoxLayout(this);
    createEdit = new QLineEdit(this);
    createLayout->addWidget(createEdit);
    createBtn = new QToolButton(this);
    createBtn->setText("Create");
    createLayout->addWidget(createBtn);
    layout->addLayout(createLayout);

    connect(selectBtn,&QToolButton::clicked,this,&QDialog::accept);
    connect(createEdit,&QLineEdit::returnPressed,this,[=](){
        createNewClass(createEdit->text());
    });
    connect(createBtn,&QToolButton::clicked,this,[=](){
        createNewClass(createEdit->text());
    });
}
