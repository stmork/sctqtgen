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
	src-gen/AbstractStateMachineAdaptor.cpp \
	src-gen/AbstractStateMachine.cpp \
	src-gen/StatemachineTimer.cpp \
    statemachine.cpp

HEADERS += \
	mainwindow.h \
	src-lib/sc_types.h \
	src-lib/StatemachineInterface.h \
	src-lib/TimedStatemachineInterface.h \
	src-lib/TimerInterface.h \
	src-gen/AbstractStateMachine.h \
	src-gen/AbstractStateMachineAdaptor.h \
	src-gen/StatemachineTimer.h \
    statemachine.h

FORMS += \
	mainwindow.ui

linux-*
{
	target.path = ./calculator
	INSTALLS += target
}
