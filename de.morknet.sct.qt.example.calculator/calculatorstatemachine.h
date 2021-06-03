#ifndef CALCULATORSTATEMACHINE_H
#define CALCULATORSTATEMACHINE_H

#include "src-qt-gen/CalculatorStatemachine.h"
#include "src-qt-lib/sc_qt_timerservice.h"

class CalculatorStateMachine :
	public CalculatorStatemachine,
	public CalculatorStatemachine::InternalOperationCallback
{
	Q_OBJECT

private:
	sc::qt::SCTimerService timer_service;

	enum Operation
	{
		NONE,
		ADD,
		SUB,
		MULT,
		DIV
	} operation;

public:
	explicit CalculatorStateMachine(QObject * parent = nullptr);

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
