#ifndef CALCULATORSTATEMACHINE_H
#define CALCULATORSTATEMACHINE_H

#include "src-qt-gen/Calculator.h"
#include "src-qt-lib/sc_timer_service.h"

class CalculatorStateMachine :
		public Calculator,
		public Calculator::InternalOperationCallback,
		public sc::timer::TimerTask,
		public sc::timer::TimerService
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
	void start();
	void stop();

protected:
	virtual void Add() override;
	virtual void Sub() override;
	virtual void Mult() override;
	virtual void Div() override;
	virtual void Clear() override;
	virtual void Equals() override;
	virtual void Digit(sc_integer digit) override;
};

#endif // CALCULATORSTATEMACHINE_H
