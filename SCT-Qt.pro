TEMPLATE         = subdirs
SUBDIRS          = Calculator DelayedExit TimerLess Trigger

Calculator.file  = de.morknet.sct.qt.example.calculator/Calculator.pro
DelayedExit.file = de.morknet.sct.qt.example.delayedexit/DelayedExit.pro
TimerLess.file   = de.morknet.sct.qt.example.timerless/Timerless.pro
Trigger.file     = de.morknet.sct.qt.example.trigger/Trigger.pro

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_CLEAN += cppcheck.xml
QMAKE_EXTRA_TARGETS += astyle cppcheck regen

astyle.commands = astyle *.example.*/*.cpp *.example.*/*.h
regen.commands  = bin/regen-examples.sh
cppcheck.commands = cppcheck \
	--language=c++ --std=c++14 \
	--xml-version=2 --force -q -j 3 \
	*.example.*/*.cpp *.example.*/*.h 2>cppcheck.xml
