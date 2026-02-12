QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accessdialog.cpp \
    confirmbox.cpp \
    database.cpp \
    exameditor.cpp \
    examviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    studenteditor.cpp \
    studentviewer.cpp \
    subjecteditor.cpp \
    subjectviewer.cpp\
    utils.cpp

HEADERS += \
    accessdialog.h \
    confirmbox.h \
    database.h \
    exameditor.h \
    examviewer.h \
    mainwindow.h \
    student.h \
    studenteditor.h \
    studentviewer.h \
    subjecteditor.h \
    subjectviewer.h \
    utils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = logo.rc

VERSION = 0.2026.2.12
QMAKE_TARGET_COMPANY = szy
QMAKE_TARGET_DESCRIPTION = StudentExamManagementSystem
QMAKE_TARGET_COPYRIGHT = Copyright(C) 2025
QMAKE_TARGET_PRODUCT = BlondeArchive
RC_LANG = 0x0800

RESOURCES += \
    logo.qrc
