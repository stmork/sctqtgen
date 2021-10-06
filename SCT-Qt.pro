TEMPLATE         = subdirs
SUBDIRS          = Calculator DelayedExit TimerLess Trigger History Orthogonal

Calculator.file  = de.morknet.sct.qt.example.calculator/Calculator.pro
DelayedExit.file = de.morknet.sct.qt.example.delayedexit/DelayedExit.pro
TimerLess.file   = de.morknet.sct.qt.example.timerless/Timerless.pro
Trigger.file     = de.morknet.sct.qt.example.trigger/Trigger.pro
History.file     = de.morknet.sct.qt.example.history/History.pro
Orthogonal.file  = de.morknet.sct.qt.example.orthogonal/Orthogonal.pro

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_EXTRA_TARGETS += astyle regen

astyle.commands = astyle *.example.*/*.cpp *.example.*/*.h
regen.commands  = bin/regen-examples.sh
