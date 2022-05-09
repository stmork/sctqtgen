QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app
TARGET               = Calculator

SOURCES += main.cpp\
	mainwindow.cpp \
	src-qt-gen/CalculatorStatemachine.cpp \
	src-qt-lib/sc_qt_timerservice.cpp \
	statemachine.cpp

HEADERS  += mainwindow.h \
	src-qt-gen/CalculatorStatemachine.h \
	src-qt-lib/sc_rxcpp.h \
	src-qt-lib/sc_statemachine.h \
	src-qt-lib/sc_timer.h \
	src-qt-lib/sc_qt_timerservice.h \
	src-qt-lib/sc_types.h \
	statemachine.h

FORMS    += mainwindow.ui

RESOURCES += \
	resources.qrc

generate.commands = ant
