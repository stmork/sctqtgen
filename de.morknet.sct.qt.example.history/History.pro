QT       += core gui widgets

CONFIG += c++17

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
