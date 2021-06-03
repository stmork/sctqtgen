#-------------------------------------------------
#
# Project created by QtCreator 2017-12-16T11:50:04
#
#-------------------------------------------------

QT                  += core gui
CONFIG              += c++11
QMAKE_EXTRA_TARGETS += generate

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Trigger
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

generate.commands = ant

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	statemachine.cpp \
	src-qt-gen/TriggerStatemachine.cpp \
	src-qt-lib/sc_qt_timerservice.cpp

HEADERS += \
	mainwindow.h \
	src-qt-gen/TriggerStatemachine.h \
	statemachine.h \
	src-qt-lib/sc_rxcpp.h \
	src-qt-lib/sc_statemachine.h \
	src-qt-lib/sc_timer.h \
	src-qt-lib/sc_qt_timerservice.h \
	src-qt-lib/sc_types.h

FORMS += \
	mainwindow.ui

linux-*
{
	target.path = ./calculator
	INSTALLS += target
}
