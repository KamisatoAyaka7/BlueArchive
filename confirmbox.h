#ifndef CONFIRMBOX_H
#define CONFIRMBOX_H

#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QToolButton>

#include <qdialog.h>

class ConfirmBox : public QDialog
{
    Q_OBJECT
public:
    ConfirmBox(QString what,QWidget *parent = nullptr);

    QString toConfirmInfo();

private:
    QLineEdit *edit;
    QToolButton *btn;
};

#endif // CONFIRMBOX_H
