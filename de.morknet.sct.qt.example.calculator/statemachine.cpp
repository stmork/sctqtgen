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
	sc_integer op   = getOperand();
	sc_integer accu = getAccu();

	switch (operation)
	{
	case ADD:
		accu = op + accu;
		break;
	case SUB:
		accu = op - accu;
		break;
	case MULT:
		accu = op * accu;
		break;
	case DIV:
		accu = op / accu;
		break;
	default:
		// Intentionally left blank
		break;
	}
	operation = NONE;
	setOperand(accu);
}

void StateMachine::Digit(sc_integer digit)
{
	setAccu(getAccu() * 10 + digit);
}
