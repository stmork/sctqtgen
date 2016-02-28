#ifndef CALCULATORSTATEMACHINE_H
#define CALCULATORSTATEMACHINE_H

#include "src-gen/AbstractCalculatorDispatcher.h"

class CalculatorStateMachine : public AbstractCalculatorDispatcher
{
	Q_OBJECT

	enum Operation
	{
		NONE,
		ADD,
		SUB,
		MULT,
		DIV
	} operation;

public:
	CalculatorStateMachine();

protected:
	virtual void initializeValues() override;
	virtual void Add() override;
	virtual void Sub() override;
	virtual void Mult() override;
	virtual void Div() override;
	virtual void Clear() override;
	virtual void Equals() override;
	virtual void Digit(sc_integer digit) override;
};

#endif // CALCULATORSTATEMACHINE_H
