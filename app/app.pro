#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T08:27:14
#
#-------------------------------------------------
QT       += core gui
QT       += concurrent

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
    converter/kerasconverter.cpp \
    converter/pythonconverter.cpp \
    graphmodel/graphmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    modelcontrol/modelcontrol.cpp \
    modelscene.cpp \
    partinfomodel.cpp \
    partitem.cpp \
    portitem.cpp \
    project/project_control.cpp \
    project/project_object.cpp \
    projectsettingdialog.cpp \
    compileconfigurationdialog.cpp \
    popoutnotification.cpp \
    pythonsupport/qtpython.cpp \
    modelconfigurationdialog.cpp \
    dataconfigurationdialog.cpp \
    tbvisuaizationdialog.cpp \
    trainconfigurationdialog.cpp

HEADERS += \
    connectionitem.h \
    converter/converter.h \
    graphmodel/graphmodel.h \
    graphmodel/graphmodel_name.h \
    mainwindow.h \
    modelcontrol/modelcontrol.h \
    modelscene.h \
    partinfomodel.h \
    partitem.h \
    portitem.h \
    project/project_control.h \
    project/project_object.h \
    project/sereialize.hpp \
    projectsettingdialog.h \
    pythonsupport/pythonadapter.h \
    utils/configurations.h \
    utils/enum_cast.hpp \
    utils/exceptions.h \
    utils/string_utils.h \
    compileconfigurationdialog.h \
    popoutnotification.h \
    modelconfigurationdialog.h \
    dataconfigurationdialog.h \
    tbvisuaizationdialog.h \
    trainconfigurationdialog.h

FORMS += \
    mainwindow.ui \
    projectsettingdialog.ui \
    compileconfigurationdialog.ui \
    popoutnotification.ui \
    modelconfigurationdialog.ui \
    dataconfigurationdialog.ui \
    tbvisuaizationdialog.ui \
    trainconfigurationdialog.ui

INCLUDEPATH += \
    ../../cereal/include

win32 {
    SOURCES += pythonsupport/windowspython.cpp
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

