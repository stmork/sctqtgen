#include "statemachine.h"

Statemachine::Statemachine(QObject * parent) :
	AbstractStateMachine(parent),
	timer_service(nullptr)
{
	setTimerService(&timer_service);
}
