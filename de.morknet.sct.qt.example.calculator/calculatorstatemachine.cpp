#include "calculatorstatemachine.h"

using namespace sc::timer;

CalculatorStateMachine::CalculatorStateMachine() :
	Calculator(nullptr),
	TimerService(this, 0)
{
	setInternalOperationCallback(this);
	setTimerService(this);

	operation = NONE;
}

void CalculatorStateMachine::start()
{
	enter();
}

void CalculatorStateMachine::stop()
{
	exit();
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

	switch(operation)
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
