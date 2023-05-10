#include "statemachine.h"

using namespace sc::qt;

Statemachine::Statemachine(QObject * parent) :
	TriggerStatemachine(parent),
	timer_service(std::make_shared<SCTimerService>())
{
	setTimerService(timer_service);
}
