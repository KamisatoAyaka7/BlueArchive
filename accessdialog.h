#ifndef ACCESSDIALOG_H
#define ACCESSDIALOG_H

#include "QDialog"
#include "QComboBox"
#include "QLineEdit"
#include "QToolButton"

class AccessDialog : public QDialog
{
    Q_OBJECT
public:
    AccessDialog(QWidget *parent = nullptr);

    QStringList getClasses();
    QString toSelectedClass();

private:
    void onSelectBtnClicked();

    QComboBox *classBox;
    QToolButton *selectBtn,*createBtn;
    QLineEdit *createEdit;

    void createNewClass(QString name);
};

#endif // ACCESSDIALOG_H
