#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>

#include "src-qt-gen/CalculatorStatemachine.h"
#include "src-qt-lib/sc_qt_timerservice.h"
#include "src-qt-lib/sc_self_pointer.h"

class StateMachine :
	public CalculatorStatemachine,
	public CalculatorStatemachine::InternalOperationCallback,
	protected SelfPointer<CalculatorStatemachine::InternalOperationCallback>
{
	Q_OBJECT

private:
	std::shared_ptr<sc::qt::SCTimerService> timer_service;

	enum Operation
	{
		NONE,
		ADD,
		SUB,
		MULT,
		DIV
	} operation;

public:
	explicit StateMachine(QObject * parent = nullptr);

protected:
	virtual void Add() override;
	virtual void Sub() override;
	virtual void Mult() override;
	virtual void Div() override;
	virtual void Clear() override;
	virtual void Equals() override;
	virtual void Digit(sc::integer digit) override;
};

#endif // STATEMACHINE_H
