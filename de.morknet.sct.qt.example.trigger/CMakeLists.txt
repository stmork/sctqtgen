cmake_minimum_required(VERSION 3.16)
project(Trigger VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES
	main.cpp
	mainwindow.cpp
	statemachine.cpp
	src-qt-gen/TriggerStatemachine.cpp
	src-qt-lib/sc_qt_timerservice.cpp
)

set(HEADERS
	mainwindow.h
	statemachine.h
	src-qt-gen/TriggerStatemachine.h
	src-qt-lib/sc_self_pointer.h
	src-qt-lib/sc_statemachine.h
	src-qt-lib/sc_timer.h
	src-qt-lib/sc_qt_timerservice.h
	src-qt-lib/sc_types.h
)

set(FORMS
   mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
