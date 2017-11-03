/*
 * Copyright (C) 2017 - Steffen A. Mork
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
AbstractDelayDispatcher::AbstractDelayDispatcher()
{
	init();
}

/**
 * The destructor calls the statemachine's exit() method,
 * calls the react() method for processing outgoing signals
 * and frees all known timer.
 */
AbstractDelayDispatcher::~AbstractDelayDispatcher()
{
}

void AbstractDelayDispatcher::start()
{
	// Do some custom initialization.
	initializeValues();

	clearOutEvents();
	enter();
	react();
}

void AbstractDelayDispatcher::stop()
{
	clearOutEvents();
	exit();
	react();
}

void AbstractDelayDispatcher::runCycle()
{
	AbstractDelay::runCycle();
	react();
}

void AbstractDelayDispatcher::react()
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
}

void AbstractDelayDispatcher::sctQtDebug(const QString &message) const
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
