QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app

QMAKE_CXXFLAGS      += -Wextra -Wshadow -Wsuggest-override
QMAKE_CLEAN         += $$TARGET

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
