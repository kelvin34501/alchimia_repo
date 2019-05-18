#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T08:27:14
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alchimia
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    connectionitem.cpp \
    converter/kerasConverter.cpp \
    converter/pythonConverter.cpp \
    editorcontrol.cpp \
    graphmodel/graphModel.cpp \
    main.cpp \
    mainwindow.cpp \
    modelscene.cpp \
    partitem.cpp \
    project/project_control.cpp \
    project/project_object.cpp \
    projectsettingdialog.cpp

HEADERS += \
    connectionitem.h \
    converter/converter.h \
    editorcontrol.h \
    graphmodel/graphmodel.h \
    graphmodel/graphmodel_name.h \
    mainwindow.h \
    modelscene.h \
    partitem.h \
    project/project_control.h \
    project/project_object.h \
    project/sereialize.hpp \
    projectsettingdialog.h \
    pythonsupport/pythonadapter.h \
    utils/configurations.h \
    utils/enum_cast.hpp \
    utils/exceptions.h \
    utils/string_utils.h

FORMS += \
        mainwindow.ui \
        projectsettingdialog.ui

INCLUDEPATH += \
    ../../cereal/include

win32 {
    SOURCES += \
        pythonsupport/windowsPython.cpp
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

