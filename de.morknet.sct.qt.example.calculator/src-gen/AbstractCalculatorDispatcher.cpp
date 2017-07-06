/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/AbstractCalculatorDispatcher.h"
#include <QtDebug>

/**
 * The callback instances are setup inside this constructor.
 * It's easy to say that the callback instances are implemented
 * by our class instance itself.
 */
AbstractCalculatorDispatcher::AbstractCalculatorDispatcher()
{
	AbstractCalculator::setTimer(this);
	setInternalSCI_OCB(this);
	init();
}

/**
 * The destructor calls the statemachines exit() method,
 * calls the react() method for processing outgoing signals
 * and frees all known timer.
 */
AbstractCalculatorDispatcher::~AbstractCalculatorDispatcher()
{
	for(StatemachineTimer *timer : timerMap.values())
	{
		timer->stop();
		timer->disconnect(timer, SIGNAL(out_timeout(sc_eventid)), this, SLOT(timeout(sc_eventid)));

		delete timer;
	}
}

void AbstractCalculatorDispatcher::start()
{
	// Do some custom initialization.
	initializeValues();

	clearOutEvents();
	enter();
	react();
}

void AbstractCalculatorDispatcher::stop()
{
	clearOutEvents();
	exit();
	react();
}

void AbstractCalculatorDispatcher::runCycle()
{
	AbstractCalculator::runCycle();
	react();
}

void AbstractCalculatorDispatcher::react()
{

	/**********************************
	 * Gui scope
	 *********************************/
	
	if (ifaceGui.isRaised_exit())
	{
		emit Exit();
	}
	if (ifaceGui.isRaised_showAccu())
	{
		emit ShowAccu(ifaceGui.get_showAccu_value());
	}
}


/**********************************
 * Gui scope
 *********************************/


void AbstractCalculatorDispatcher::Button0( )
{
	sctQtDebug("Button0()...");
	ifaceGui.raise_button0();
	runCycle();
}

void AbstractCalculatorDispatcher::Button1( )
{
	sctQtDebug("Button1()...");
	ifaceGui.raise_button1();
	runCycle();
}

void AbstractCalculatorDispatcher::Button2( )
{
	sctQtDebug("Button2()...");
	ifaceGui.raise_button2();
	runCycle();
}

void AbstractCalculatorDispatcher::Button3( )
{
	sctQtDebug("Button3()...");
	ifaceGui.raise_button3();
	runCycle();
}

void AbstractCalculatorDispatcher::Button4( )
{
	sctQtDebug("Button4()...");
	ifaceGui.raise_button4();
	runCycle();
}

void AbstractCalculatorDispatcher::Button5( )
{
	sctQtDebug("Button5()...");
	ifaceGui.raise_button5();
	runCycle();
}

void AbstractCalculatorDispatcher::Button6( )
{
	sctQtDebug("Button6()...");
	ifaceGui.raise_button6();
	runCycle();
}

void AbstractCalculatorDispatcher::Button7( )
{
	sctQtDebug("Button7()...");
	ifaceGui.raise_button7();
	runCycle();
}

void AbstractCalculatorDispatcher::Button8( )
{
	sctQtDebug("Button8()...");
	ifaceGui.raise_button8();
	runCycle();
}

void AbstractCalculatorDispatcher::Button9( )
{
	sctQtDebug("Button9()...");
	ifaceGui.raise_button9();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonAdd( )
{
	sctQtDebug("ButtonAdd()...");
	ifaceGui.raise_buttonAdd();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonClear( )
{
	sctQtDebug("ButtonClear()...");
	ifaceGui.raise_buttonClear();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonDiv( )
{
	sctQtDebug("ButtonDiv()...");
	ifaceGui.raise_buttonDiv();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonEquals( )
{
	sctQtDebug("ButtonEquals()...");
	ifaceGui.raise_buttonEquals();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonMult( )
{
	sctQtDebug("ButtonMult()...");
	ifaceGui.raise_buttonMult();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonSub( )
{
	sctQtDebug("ButtonSub()...");
	ifaceGui.raise_buttonSub();
	runCycle();
}

/**
 * This method implements the canceling of the statemachine.
 * It intentionally does nothing.
 */
void AbstractCalculatorDispatcher::cancel()
{
	sctQtDebug("Cancel.");
}

void AbstractCalculatorDispatcher::sctQtLog(const QString &message) const
{
	qDebug() << message;
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
 * @see timeout()
 */
void AbstractCalculatorDispatcher::setTimer(
		TimedStatemachineInterface *statemachine,
		sc_eventid event, sc_integer time, sc_boolean isPeriodic)
{
	Q_UNUSED(statemachine);
	StatemachineTimer *timer = timerMap[event];

	if (timer == nullptr)
	{
		timer = new StatemachineTimer(event);
		timerMap.insert(event, timer);
	}
	timer->setInterval(time);
	timer->setSingleShot(!isPeriodic);
	timer->start();
	timer->connect(timer, SIGNAL(out_timeout(sc_eventid)), this, SLOT(timeout(sc_eventid)));

	if ((time >= 1000) && ((time % 1000) == 0))
	{
		sctQtDebug(QString::asprintf("Activated timer %p with timeout %ds.", event, time / 1000));
	}
	else
	{
		sctQtDebug(QString::asprintf("Activated timer %p with timeout %dms.", event, time));
	}
}

/**
 * This method deinitialize a timer belonging to a sc_eventid. The timer
 * is not deleted but disconnected from Qt signal/slot.
 */
void AbstractCalculatorDispatcher::unsetTimer(TimedStatemachineInterface *statemachine, sc_eventid event)
{
	Q_UNUSED(statemachine);
	StatemachineTimer *timer = timerMap[event];

	if (timer != nullptr)
	{
		timer->disconnect(timer, SIGNAL(out_timeout(sc_eventid)), this, SLOT(timeout(sc_eventid)));
		timer->stop();
		sctQtDebug(QString::asprintf("Disabled timer %p.", event));
	}
}

/**
 * This Qt slot is signalled by a timer belonging to the given
 * sc_eventid.
 */
void AbstractCalculatorDispatcher::timeout(sc_eventid event)
{
	sctQtDebug(QString::asprintf("Time event occured with id %p", event));
	raiseTimeEvent(event);
	runCycle();
}
