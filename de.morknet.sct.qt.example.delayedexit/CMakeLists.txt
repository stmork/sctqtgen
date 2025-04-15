cmake_minimum_required(VERSION 3.16)
project(DelayedExit VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES
	main.cpp
	mainwindow.cpp
	src-qt-gen/DelayedStatemachine.cpp
	statemachine.cpp
)

set(HEADERS
	mainwindow.h
	src-qt-lib/sc_types.h
	src-qt-lib/sc_statemachine.h
	src-qt-gen/DelayedStatemachine.h
	statemachine.h
)

set(FORMS
   mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
