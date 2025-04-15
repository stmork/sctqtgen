cmake_minimum_required(VERSION 3.16)
project(Calculator VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES
	main.cpp
	mainwindow.cpp
	src-qt-gen/CalculatorStatemachine.cpp
	src-qt-lib/sc_qt_timerservice.cpp
	statemachine.cpp
)

set(HEADERS
	src-qt-gen/CalculatorStatemachine.h
	src-qt-lib/sc_self_pointer.h
	src-qt-lib/sc_statemachine.h
	src-qt-lib/sc_timer.h
	src-qt-lib/sc_qt_timerservice.h
	src-qt-lib/sc_types.h
	statemachine.h
)

set(FORMS
	mainwindow.ui
)

set(RESOURCES
	resources.qrc
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
