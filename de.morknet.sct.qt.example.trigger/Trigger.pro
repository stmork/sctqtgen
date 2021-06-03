QT                  += core gui widgets
CONFIG              += c++11
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app
TARGET               = Trigger
QMAKE_CXXFLAGS      += -Wextra -Wshadow -Wsuggest-override

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	statemachine.cpp \
	src-qt-gen/TriggerStatemachine.cpp \
	src-qt-lib/sc_qt_timerservice.cpp

HEADERS += \
	mainwindow.h \
	statemachine.h \
	src-qt-gen/TriggerStatemachine.h \
	src-qt-lib/sc_rxcpp.h \
	src-qt-lib/sc_statemachine.h \
	src-qt-lib/sc_timer.h \
	src-qt-lib/sc_qt_timerservice.h \
	src-qt-lib/sc_types.h

FORMS += \
	mainwindow.ui

generate.commands = ant
