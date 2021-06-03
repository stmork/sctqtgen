#include "calculatorstatemachine.h"

CalculatorStateMachine::CalculatorStateMachine(QObject * parent) :
	CalculatorStatemachine(parent),
	timer_service(nullptr)
{
	setInternalOperationCallback(this);
	setTimerService(&timer_service);

	operation = NONE;
}

void CalculatorStateMachine::Add()
{
	operation = ADD;
}

void CalculatorStateMachine::Sub()
{
	operation = SUB;
}

void CalculatorStateMachine::Mult()
{
	operation = MULT;
}

void CalculatorStateMachine::Div()
{
	operation = DIV;
}

void CalculatorStateMachine::Clear()
{
	operation = NONE;
}

void CalculatorStateMachine::Equals()
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

void CalculatorStateMachine::Digit(sc_integer digit)
{
	setAccu(getAccu() * 10 + digit);
}
