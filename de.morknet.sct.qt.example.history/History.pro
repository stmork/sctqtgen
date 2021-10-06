QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app
TARGET               = History

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	src-gen/HistoryStatemachine.cpp

HEADERS += \
	mainwindow.h \
	src-gen/HistoryStatemachine.h \
	src-lib/sc_statemachine.h \
	src-lib/sc_types.h

FORMS += \
	mainwindow.ui

generate.commands = ant
