cmake_minimum_required(VERSION 3.16)
project(History VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES
	main.cpp
	mainwindow.cpp
	src-gen/HistoryStatemachine.cpp
)

set(HEADERS
	mainwindow.h
	src-gen/HistoryStatemachine.h
	src-lib/sc_self_pointer.h
	src-lib/sc_statemachine.h
	src-lib/sc_types.h
)

set(FORMS
   mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
