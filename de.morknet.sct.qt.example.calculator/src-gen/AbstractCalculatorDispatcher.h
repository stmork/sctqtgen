/*
 * Copyright Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#ifndef ABSTRACTCALCULATORDISPATCHER_H
#define ABSTRACTCALCULATORDISPATCHER_H

#include <QObject>
#include <QHash>
#include "src-gen/AbstractCalculator.h"
#include "src-gen/TimerInterface.h"
#include "src-gen/StatemachineTimer.h"

class AbstractCalculatorDispatcher :
	public    QObject,
	public    AbstractCalculator,
	protected AbstractCalculator::InternalSCI_OCB,
	protected TimerInterface
{
	Q_OBJECT

	QHash<sc_eventid, StatemachineTimer *> timerMap;

public:
	AbstractCalculatorDispatcher();
	virtual ~AbstractCalculatorDispatcher();

	void start();
	void stop();

public slots:
	/* Triggered from QTimer */
	void timeout(sc_eventid event);

	/**********************************
	 * Gui scope
	 *********************************/
	
	virtual void Button0();
	virtual void Button1();
	virtual void Button2();
	virtual void Button3();
	virtual void Button4();
	virtual void Button5();
	virtual void Button6();
	virtual void Button7();
	virtual void Button8();
	virtual void Button9();
	virtual void ButtonAdd();
	virtual void ButtonClear();
	virtual void ButtonDiv();
	virtual void ButtonEquals();
	virtual void ButtonMult();
	virtual void ButtonSub();

signals:
	/**********************************
	 * Gui scope
	 *********************************/
	
	void Exit();
	void ShowAccu(sc_integer);


protected:
	virtual void initializeValues() = 0;
	virtual void runCycle() override;
	virtual void react();
	virtual void cancel() override;

	void setTimer(TimedStatemachineInterface* statemachine, sc_eventid event, sc_integer time, sc_boolean isPeriodic) override;
	void unsetTimer(TimedStatemachineInterface* statemachine, sc_eventid event) override;
};

#endif // ABSTRACTCALCULATORDISPATCHER_H
