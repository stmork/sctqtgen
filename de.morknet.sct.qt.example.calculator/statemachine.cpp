#include "statemachine.h"

StateMachine::StateMachine(QObject * parent) :
	CalculatorStatemachine(parent),
	SelfPointer<CalculatorStatemachine::InternalOperationCallback>(this),
	timer_service(std::make_shared<sc::qt::SCTimerService>())
{
	setInternalOperationCallback(self);
	setTimerService(timer_service);

	operation = NONE;
}

void StateMachine::Add()
{
	operation = ADD;
}

void StateMachine::Sub()
{
	operation = SUB;
}

void StateMachine::Mult()
{
	operation = MULT;
}

void StateMachine::Div()
{
	operation = DIV;
}

void StateMachine::Clear()
{
	operation = NONE;
}

void StateMachine::Equals()
{
	switch (operation)
	{
	case ADD:
		accu = operand + accu;
		break;
	case SUB:
		accu = operand - accu;
		break;
	case MULT:
		accu = operand * accu;
		break;
	case DIV:
		accu = operand / accu;
		break;
	default:
		// Intentionally left blank
		break;
	}
	operation = NONE;
	operand = accu;
}

void StateMachine::Digit(sc::integer digit)
{
	accu = accu * 10 + digit;
}
