#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "src-gen/AbstractStateMachineAdaptor.h"

class Statemachine : public AbstractStateMachineAdaptor
{
public:
	Statemachine();

private:
	void initializeValues() override;
};

#endif // STATEMACHINE_H
