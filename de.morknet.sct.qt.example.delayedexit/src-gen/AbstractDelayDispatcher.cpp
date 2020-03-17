/*
 * Copyright (C) 2020 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/AbstractDelayDispatcher.h"
#include <QtDebug>

/**
 * The callback instances are setup inside this constructor.
 * It's easy to say that the callback instances are implemented
 * by our class instance itself.
 */
AbstractDelayDispatcher::AbstractDelayDispatcher(QObject * parent) :
	QObject(parent)
{
	AbstractDelay::init();
}

/**
 * The destructor calls the statemachine's exit() method,
 * calls the react() method for processing outgoing signals
 * and frees all known timer.
 */
AbstractDelayDispatcher::~AbstractDelayDispatcher()
{
}

void AbstractDelayDispatcher::start(void)
{
	// Do some custom initialization.
	initializeValues();

	AbstractDelay::clearOutEvents();
	AbstractDelay::enter();
	react();
}

void AbstractDelayDispatcher::stop(void)
{
	AbstractDelay::clearOutEvents();
	AbstractDelay::exit();
	react();
}

void AbstractDelayDispatcher::runCycle()
{
	AbstractDelay::runCycle();
	react();
}

void AbstractDelayDispatcher::react(void)
{

	/**********************************
	 * Gui scope
	 *********************************/
	
	if (ifaceGui.isRaised_doSomething())
	{
		sctQtDebug("emit doSomething()...");
		emit doSomething();
	}
	if (ifaceGui.isRaised_stateA())
	{
		sctQtDebug("emit stateA()...");
		emit stateA();
	}
	if (ifaceGui.isRaised_stopped())
	{
		sctQtDebug("emit stopped()...");
		emit stopped();
	}
	if (ifaceGui.isRaised_stopping())
	{
		sctQtDebug("emit stopping()...");
		emit stopping(ifaceGui.get_stopping_value());
	}
	if (ifaceGui.isRaised_triggerStop())
	{
		sctQtDebug("emit triggerStop()...");
		emit triggerStop();
	}
}

void AbstractDelayDispatcher::sctQtDebug(const QString & message) const
{
	qDebug() << message;
}


/**********************************
 * Gui scope
 *********************************/


void AbstractDelayDispatcher::button1( )
{
	sctQtDebug("button1()...");
	ifaceGui.raise_button1();
	runCycle();
}

void AbstractDelayDispatcher::button2( )
{
	sctQtDebug("button2()...");
	ifaceGui.raise_button2();
	runCycle();
}

void AbstractDelayDispatcher::complete( )
{
	sctQtDebug("complete()...");
	ifaceGui.raise_complete();
	runCycle();
}
