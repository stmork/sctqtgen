#ifndef DELAYEDSTATEMACHINE_H
#define DELAYEDSTATEMACHINE_H

#include "src-gen/AbstractDelayDispatcher.h"

class DelayedStateMachine : public AbstractDelayDispatcher
{
public:
	DelayedStateMachine();

	virtual void initializeValues() override;
};

#endif // DELAYEDSTATEMACHINE_H
