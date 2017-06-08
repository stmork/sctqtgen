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
	src-gen/sc_types.h \
	src-gen/StatemachineInterface.h \
	src-gen/StatemachineTimer.h \
	src-gen/TimedStatemachineInterface.h \
	src-gen/TimerInterface.h \
	calculatorstatemachine.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

linux-*
{
	target.path = ./calculator
	INSTALLS += target
}
