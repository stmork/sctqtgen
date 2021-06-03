#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-qt-gen/DelayedStatemachine.h"

class StateMachine : public DelayedStatemachine
{
public:
	explicit StateMachine(QObject * parent = nullptr);
};

#endif // STATEMACHINE_H
