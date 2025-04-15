cmake_minimum_required(VERSION 3.16)
project(Sct-Qt-Generator VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wextra -Wpedantic)
add_compile_options(-Wshadow)
add_compile_options(-Wsuggest-override)

add_subdirectory(de.morknet.sct.qt.example.calculator)
add_subdirectory(de.morknet.sct.qt.example.delayedexit)
add_subdirectory(de.morknet.sct.qt.example.history)
add_subdirectory(de.morknet.sct.qt.example.orthogonal)
add_subdirectory(de.morknet.sct.qt.example.synchronization)
add_subdirectory(de.morknet.sct.qt.example.timerless)
add_subdirectory(de.morknet.sct.qt.example.trigger)

add_custom_target(cppcheck
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND cppcheck --language=c++ --std=c++14
		--xml-version=2 --force -q -j `nproc`
		*.example.*/*.cpp *.example.*/*.h 2>cppcheck.xml
)

set_property(
	TARGET cppcheck
	APPEND
	PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_SOURCE_DIR}/cppcheck.xml
)
