#include "statemachine.h"

Statemachine::Statemachine(QObject * parent) :
	TriggerStatemachine(parent),
	timer_service(nullptr)
{
	setTimerService(&timer_service);
}
