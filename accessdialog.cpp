#include "accessdialog.h"

void AccessDialog::m_mul(quint64 *l1,quint64 *l2,quint64 *l3,int s1,int s2,int s3)
{
    if(s3<s1+s2)
        return;
    for(int i=0;i<s3;i++)
        l3[i]=0;
    quint64 temp=0;
    for(int i1=0;i1<s1;i1++)
    {
        for(int i2=0;i2<s2;i2++)
        {
            temp = l1[i1]*l2[i2];
            l3[i1+i2]+=temp<<32>>32;
            l3[i1+i2+1]+=temp>>32;
        }
        for(int i=i1;i<i1+s2+1;i++)
        {
            l3[i+1]+=l3[i]>>32;
            l3[i]=l3[i]<<32>>32;
        }
    }
}

AccessDialog::AccessDialog(QWidget *parent)
{
    setParent(parent);
}
