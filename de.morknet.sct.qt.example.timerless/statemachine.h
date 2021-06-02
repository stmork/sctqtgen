#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-qt-gen/AbstractTimerLess.h"

class StateMachine :
	public AbstractTimerLess
{
public:
	explicit StateMachine(QObject * parent = nullptr);
};

#endif // STATEMACHINE_H
