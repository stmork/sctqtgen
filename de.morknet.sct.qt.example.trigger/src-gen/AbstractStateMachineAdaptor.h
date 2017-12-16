/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#ifndef ABSTRACTSTATEMACHINEADAPTOR_H
#define ABSTRACTSTATEMACHINEADAPTOR_H

#include <QObject>
#include <QHash>
#include "src-gen/AbstractStateMachine.h"
#include "src-lib/TimerInterface.h"
#include "src-gen/StatemachineTimer.h"

#define QT_SCT_DEBUG 1

/**
 * This class provides a link layer which wires the in and out events
 * to the signal and slots of a Qt application.
 */
class AbstractStateMachineAdaptor :
	public    QObject,
	public    AbstractStateMachine,
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
	AbstractStateMachineAdaptor();

	/**
	 * The destructor frees all resources allocated from this
	 * Qt/SCT layer.
	 */
	virtual ~AbstractStateMachineAdaptor();

private slots:
	/**
	 * This slot is triggered from QTimer.
	 *
	 * @param event The timer event id which uniquely identifies the timer.
	 */
	void timeout(const sc_eventid event);

public slots:
	/**
	 * This method initializes the statemachine and runs
	 * the first cycle. The virtual method initializeValues()
	 * is for initializing some statemachine values. After
	 * entering the statemachine the method react() is run
	 * to evaluate possible raised out events.
	 */
	void start();

	/**
	 * This method stops the statemachine and runs
	 * the last cycle. After leaving the statemachine
	 * the method react() is run to evaluate possible
	 * raised out events.
	 */
	void stop();

	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This callback acts as a slot for
	 * the in event pressed.
	 */
	virtual void Pressed( );


signals:
	/**********************************
	 * Gui scope
	 *********************************/
	
	/**
	 * This out event emits signal lanes.
	 */
	void Lanes( );

	/**
	 * This out event emits signal update.
	 */
	void Update( );

	/**
	 * This out event emits signal wait.
	 */
	void Wait( );


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
		const sc_eventid event,
		const sc_integer time,
		const sc_boolean isPeriodic) override;
	virtual void unsetTimer(TimedStatemachineInterface* statemachine,
		const sc_eventid event) override;
	virtual void cancel() override;
};

#endif // ABSTRACTSTATEMACHINEADAPTOR_H
