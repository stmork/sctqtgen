#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-qt-gen/AbstractStateMachine.h"
#include "src-qt-lib/sc_qt_timerservice.h"

class Statemachine :
		public AbstractStateMachine
{
	Q_OBJECT

private:
	sc::qt::SCTimerService timer_service;

public:
	explicit Statemachine(QObject * parent = nullptr);
};

#endif // STATEMACHINE_H
