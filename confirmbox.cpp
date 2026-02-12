#include "confirmbox.h"

ConfirmBox::ConfirmBox(QString what,QWidget *parent)
{
    setParent(parent);
    setWindowTitle("Confirm");

    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);

    edit = new QLineEdit(this);
    edit->setPlaceholderText(what);
    layout->addWidget(edit);
    connect(edit,&QLineEdit::returnPressed,this,&QDialog::accept);

    btn = new QToolButton(this);
    btn->setText("Confirm");
    layout->addWidget(btn);
    connect(btn,&QToolButton::clicked,this,&QDialog::accept);
}

QString ConfirmBox::toConfirmInfo()
{
    return edit->text();
}
