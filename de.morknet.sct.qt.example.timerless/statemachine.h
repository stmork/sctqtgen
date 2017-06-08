#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-gen/AbstractStateMachineDispatcher.h"

class StateMachine : public AbstractStateMachineDispatcher
{
public:
	StateMachine();

	inline void initializeValues() override
	{
		// Do nothing
	}
};

#endif // STATEMACHINE_H
