/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/AbstractStateMachineAdaptor.h"
#include <QtDebug>
#include <inttypes.h>

/**
 * The callback instances are setup inside this constructor.
 * It's easy to say that the callback instances are implemented
 * by our class instance itself.
 */
AbstractStateMachineAdaptor::AbstractStateMachineAdaptor()
{
	AbstractStateMachine::setTimer(this);
	AbstractStateMachine::init();
}

/**
 * The destructor calls the statemachine's exit() method,
 * calls the react() method for processing outgoing signals
 * and frees all known timer.
 */
AbstractStateMachineAdaptor::~AbstractStateMachineAdaptor()
{
	for(StatemachineTimer *timer : timerMap.values())
	{
		timer->disconnect(
			timer, &StatemachineTimer::out_timeout,
			this, &AbstractStateMachineAdaptor::sct_timeout);
		timer->stop();

		delete timer;
	}
}

void AbstractStateMachineAdaptor::start()
{
	// Do some custom initialization.
	initializeValues();

	AbstractStateMachine::clearOutEvents();
	AbstractStateMachine::enter();
	react();
}

void AbstractStateMachineAdaptor::stop()
{
	AbstractStateMachine::clearOutEvents();
	AbstractStateMachine::exit();
	react();
}

void AbstractStateMachineAdaptor::runCycle()
{
	AbstractStateMachine::runCycle();
	react();
}

void AbstractStateMachineAdaptor::react()
{
	bool internalEventOccured = false;

	/**********************************
	 * Gui scope
	 *********************************/
	
	if (ifaceGui.isRaised_lanes())
	{
		sctQtDebug("emit lanes()...");
		emit lanes();
	}
	if (ifaceGui.isRaised_update())
	{
		sctQtDebug("emit update()...");
		emit update();
	}
	if (ifaceGui.isRaised_wait())
	{
		sctQtDebug("emit wait()...");
		emit wait();
	}

	/**********************************
	 * Internal scope
	 *********************************/
	
	internalEventOccured |= ifaceInternalSCI.isRaised_trigger();

	// Check for internal events
	if (internalEventOccured)
	{
		runCycle();
	}
}

void AbstractStateMachineAdaptor::sctQtDebug(const QString &message) const
{
	qDebug() << message;
}


/**********************************
 * Gui scope
 *********************************/


void AbstractStateMachineAdaptor::pressed( )
{
	sctQtDebug("pressed()...");
	ifaceGui.raise_pressed();
	runCycle();
}

/**
 * This method implements the canceling of the statemachine.
 * It intentionally does nothing.
 */
void AbstractStateMachineAdaptor::cancel()
{
	sctQtDebug("Cancel.");
}

/*********************************************************************/
/*                                                                   */
/*     Timer callbacks                                               */
/*                                                                   */
/*********************************************************************/

/**
 * This method implements the TimerInterface class provided by
 * the YAKINDU SCT. It intends to initialize and start a timer
 * In this Qt implementation the timer is mapped from a
 * sc_eventid. A timer is only created on first request. The
 * timer is initialized per cycle time and periodicity and
 * connected via a Qt signal into this class for statemachine
 * callback. Note that a timer may be reinitialized!
 *
 * @see sct_timeout()
 */
void AbstractStateMachineAdaptor::setTimer(
		TimedStatemachineInterface *statemachine,
		const sc_eventid event,
		const sc_integer time,
		const sc_boolean isPeriodic)
{
	Q_UNUSED(statemachine);
	StatemachineTimer *timer = timerMap[event];
	const bool high_precision = (time % 1000) != 0;

	if (timer == nullptr)
	{
		timer = new StatemachineTimer(this, event);
		timerMap.insert(event, timer);
	}
	timer->setTimerType(high_precision ? Qt::TimerType::PreciseTimer : Qt::TimerType::CoarseTimer);
	timer->setInterval(time);
	timer->setSingleShot(!isPeriodic);
	timer->connect(
		timer, &StatemachineTimer::out_timeout,
		this, &AbstractStateMachineAdaptor::sct_timeout);
	timer->start();

	if (high_precision)
	{
		sctQtDebug(QString::asprintf("Activated timer %" PRIxPTR " with timeout %dms.", event, time));
	}
	else
	{
		sctQtDebug(QString::asprintf("Activated timer %" PRIxPTR " with timeout %ds.", event, time / 1000));
	}
}

/**
 * This method deinitialize a timer belonging to a sc_eventid. The timer
 * is not deleted but disconnected from Qt signal/slot.
 */
void AbstractStateMachineAdaptor::unsetTimer(
	TimedStatemachineInterface *statemachine,
	const sc_eventid event)
{
	Q_UNUSED(statemachine);
	StatemachineTimer *timer = timerMap[event];

	if (timer != nullptr)
	{
		timer->disconnect(
			timer, &StatemachineTimer::out_timeout,
			this, &AbstractStateMachineAdaptor::sct_timeout);
		timer->stop();
		sctQtDebug(QString::asprintf("Disabled timer %" PRIxPTR ".", event));
	}
}

/**
 * This Qt slot is signalled by a timer belonging to the given
 * sc_eventid.
 */
void AbstractStateMachineAdaptor::sct_timeout(const sc_eventid event)
{
	sctQtDebug(QString::asprintf("Time event occured with id %" PRIxPTR ".", event));
	raiseTimeEvent(event);
	runCycle();
}
