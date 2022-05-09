QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app
TARGET               = DelayedExit

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	src-qt-gen/DelayedStatemachine.cpp \
	statemachine.cpp

HEADERS += \
	mainwindow.h \
	src-qt-lib/sc_types.h \
	src-qt-lib/sc_rxcpp.h \
	src-qt-lib/sc_statemachine.h \
	src-qt-gen/StatemachineInterface.h \
	src-qt-gen/DelayedStatemachine.h \
	statemachine.h

FORMS += \
	mainwindow.ui

generate.commands = ant
