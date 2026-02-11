#ifndef ACCESSDIALOG_H
#define ACCESSDIALOG_H

#include "QDialog"

class AccessDialog : public QDialog
{
public:
    AccessDialog(QWidget *parent = nullptr);

private:
    void m_mul(quint64 *l1,quint64 *l2,quint64 *l3,int s1,int s2,int s3);
    void exponentiation(quint64 *l1,int s1,int index);
};

#endif // ACCESSDIALOG_H
