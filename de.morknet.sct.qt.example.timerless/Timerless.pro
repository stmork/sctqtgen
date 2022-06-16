QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app

QMAKE_CXXFLAGS      += -Wextra -Wshadow -Wsuggest-override
QMAKE_CLEAN         += $$TARGET

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	statemachine.cpp \
	src-qt-gen/TimerlessStatemachine.cpp

HEADERS += \
	mainwindow.h \
	statemachine.h \
	src-qt-lib/sc_types.h \
	src-qt-lib/sc_rxcpp.h \
	src-qt-lib/sc_statemachine.h \
	src-qt-gen/TimerlessStatemachine.h

FORMS += \
	mainwindow.ui

generate.commands = ant
