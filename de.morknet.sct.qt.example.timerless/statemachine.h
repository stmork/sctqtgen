#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-qt-gen/TimerlessStatemachine.h"

class StateMachine : public TimerlessStatemachine
{
public:
	explicit StateMachine(QObject * parent = nullptr);
};

#endif // STATEMACHINE_H
