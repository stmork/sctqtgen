#include "statemachine.h"

StateMachine::StateMachine(QObject * parent) :
	CalculatorStatemachine(parent),
	timer_service(nullptr)
{
	setInternalOperationCallback(this);
	setTimerService(&timer_service);

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
		operand += accu;
		break;
	case SUB:
		operand -= accu;
		break;
	case MULT:
		operand *= accu;
		break;
	case DIV:
		operand /= accu;
		break;
	default:
		// Intentionally left blank
		break;
	}
}

void StateMachine::Digit(sc::integer digit)
{
	accu = accu * 10 + digit;
}
