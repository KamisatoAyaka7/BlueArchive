#include "mainwindow.h"
#include "accessdialog.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AccessDialog ad;
    if(ad.exec()==QDialog::Accepted)
    {
        QString mainPath = QDir::cleanPath(QCoreApplication::applicationDirPath()+"/data/"+ad.toSelectedClass());
        ad.close();
        MainWindow w(mainPath);
        w.setWindowOpacity(0.9);
        w.show();
        return a.exec();
    }

    return 0;
}
