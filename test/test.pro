include(gtest_dependency.pri)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alchimia_test
TEMPLATE = app

CONFIG += console
CONFIG += c++11

SOURCES += \
    test_graphmodel.cpp \
    ../app/converter/kerasconverter.cpp \
    ../app/converter/pythonconverter.cpp \
    ../app/graphmodel/graphmodel.cpp

HEADERS += \
    ../app/converter/converter.h \
    ../app/graphmodel/graphmodel.h \
    ../app/graphmodel/graphmodel_name.h \
    ../app/utils/configurations.h \
    ../app/utils/enum_cast.hpp \
    ../app/utils/exceptions.h \
    ../app/utils/string_utils.h \
    tst_case.h

INCLUDEPATH += \
    ../app

