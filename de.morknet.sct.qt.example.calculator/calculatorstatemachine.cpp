#include "calculatorstatemachine.h"

CalculatorStateMachine::CalculatorStateMachine()
{
}

void CalculatorStateMachine::initializeValues()
{
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
	sc_integer op   = ifaceInternalSCI.get_operand();
	sc_integer accu = ifaceInternalSCI.get_accu();

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
	}
	operation = NONE;
	ifaceInternalSCI.set_operand(accu);
}

void CalculatorStateMachine::Digit(sc_integer digit)
{
	ifaceInternalSCI.set_accu(ifaceInternalSCI.get_accu() * 10 + digit);
}
