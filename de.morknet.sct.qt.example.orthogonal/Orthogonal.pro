QT                  += core gui widgets
CONFIG              += c++17
QMAKE_EXTRA_TARGETS += generate
TEMPLATE             = app
TARGET               = Orthogonal

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	src-gen/OrthogonalStatemachine.cpp

HEADERS += \
	mainwindow.h \
	src-gen/OrthogonalStatemachine.h \
	src-lib/sc_statemachine.h \
	src-lib/sc_types.h

FORMS += \
	mainwindow.ui

generate.commands = ant
