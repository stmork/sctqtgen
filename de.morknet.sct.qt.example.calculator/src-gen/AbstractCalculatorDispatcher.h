/*
 * Copyright (C) 2017 - Steffen A. Mork
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
#include "src/TimerInterface.h"
#include "src-gen/StatemachineTimer.h"

#define QT_SCT_DEBUG 1

/**
 * This class provides a link layer which wires the in and out events
 * to the signal and slots of a Qt application.
 */
class AbstractCalculatorDispatcher :
	public    QObject,
	public    AbstractCalculator,
	protected AbstractCalculator::InternalSCI_OCB,
	protected TimerInterface
{
	Q_OBJECT

private:
	/**
	 * The QMap which maps von sc_eventid to a real
	 * StatemachineTimer instance.
	 */
	QHash<sc_eventid, StatemachineTimer *> timerMap;

public:
	/**
	 * The constructor initializes the Qt event layer and the YAKINDU
	 * statemachine. This layer implements all OCBs and signal/slot
	 * management.
	 */
	AbstractCalculatorDispatcher();

	/**
	 * The destructor frees all resources allocated from this
	 * Qt/SCT layer.
	 */
	virtual ~AbstractCalculatorDispatcher();

	/**
	 * This method initializes the statemachine and runs
	 * the first cycle. The virtual method initializeValues()
	 * is for initializing some statemachine values. After
	 * entering the statemachine the method react() is run
	 * to evaluate possible raised out events.
	 */
	void start();

	/**
	 * This method stopps the statemachine and runs
	 * the last cycle. After leaving the statemachine
	 * the method react() is run to evaluate possible
	 * raised out events.
	 */
	void stop();

public slots:
	/**
	 * This slot is triggered from QTimer.
	 *
	 * @param event The timer event id which uniquely identifies the timer.
	 */
	void timeout(sc_eventid event);

	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This callback acts as a slot for
	 * the in event Button0.
	 */
	virtual void Button0( );

	/**
	 * This callback acts as a slot for
	 * the in event Button1.
	 */
	virtual void Button1( );

	/**
	 * This callback acts as a slot for
	 * the in event Button2.
	 */
	virtual void Button2( );

	/**
	 * This callback acts as a slot for
	 * the in event Button3.
	 */
	virtual void Button3( );

	/**
	 * This callback acts as a slot for
	 * the in event Button4.
	 */
	virtual void Button4( );

	/**
	 * This callback acts as a slot for
	 * the in event Button5.
	 */
	virtual void Button5( );

	/**
	 * This callback acts as a slot for
	 * the in event Button6.
	 */
	virtual void Button6( );

	/**
	 * This callback acts as a slot for
	 * the in event Button7.
	 */
	virtual void Button7( );

	/**
	 * This callback acts as a slot for
	 * the in event Button8.
	 */
	virtual void Button8( );

	/**
	 * This callback acts as a slot for
	 * the in event Button9.
	 */
	virtual void Button9( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonAdd.
	 */
	virtual void ButtonAdd( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonClear.
	 */
	virtual void ButtonClear( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonDiv.
	 */
	virtual void ButtonDiv( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonEquals.
	 */
	virtual void ButtonEquals( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonMult.
	 */
	virtual void ButtonMult( );

	/**
	 * This callback acts as a slot for
	 * the in event ButtonSub.
	 */
	virtual void ButtonSub( );


signals:
	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This out event emits signal Exit.
	 */
	void Exit( );

	/**
	 * This out event emits signal ShowAccu.
	 *
	 * @param input The input event parameter.
	 */
	void ShowAccu(sc_integer input);


protected:
	/**
	 * This method is intended to initialize possible ressources of
	 * this Qt/SCT layer.
	 */
	virtual void initializeValues() = 0;

	/**
	 * This runs a single statemachine cycle. See
	 * documentation of YAKINDU statechart tools for
	 * more information. After running the cycle the
	 * method react() is run to evaluate possible
	 * raised out events.
	 */
	virtual void runCycle() override;

	/**
	 * This method converts raised out events into
	 * Qt signals. Events from internal scope are
	 * not converted into Qt signals. Instead a 
	 * further runCycle() is done.
	 */
	virtual void react();

	/**
	 * This method prints debug messages and may be
	 * overloaded to customize debug logging.
	 *
	 * @param message The message to log.
	 */
	virtual void sctQtDebug(const QString &message) const;

	virtual void setTimer(TimedStatemachineInterface* statemachine,
		sc_eventid event, sc_integer time, sc_boolean isPeriodic) override;
	virtual void unsetTimer(TimedStatemachineInterface* statemachine,
		sc_eventid event) override;
	virtual void cancel() override;
};

#endif // ABSTRACTCALCULATORDISPATCHER_H
