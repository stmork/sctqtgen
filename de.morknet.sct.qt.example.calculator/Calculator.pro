#-------------------------------------------------
#
# Project created by QtCreator 2016-02-28T08:52:50
#
#-------------------------------------------------

QT                  += core gui
CONFIG              += c++11
QMAKE_EXTRA_TARGETS += generate

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


generate.commands = ant

SOURCES += main.cpp\
	mainwindow.cpp \
	src-gen/AbstractCalculator.cpp \
	src-gen/AbstractCalculatorDispatcher.cpp \
	src-gen/StatemachineTimer.cpp \
	calculatorstatemachine.cpp

HEADERS  += mainwindow.h \
	src-gen/AbstractCalculator.h \
	src-gen/AbstractCalculatorDispatcher.h \
	src-gen/StatemachineTimer.h \
	src/sc_types.h \
	src/StatemachineInterface.h \
	src/TimedStatemachineInterface.h \
	src/TimerInterface.h \
	calculatorstatemachine.h

FORMS    += mainwindow.ui

RESOURCES += \
	resources.qrc

linux-*
{
	target.path = ./calculator
	INSTALLS += target
}
