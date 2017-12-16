/*
 * Copyright (C) 2017 - Steffen A. Mork
 *
 * NOTE: This code is automatically generated. So do not
 * change this file! The changes will be lost!
 *
 * $Id$
 * $Author$
 */

#include "src-gen/AbstractStateMachineDispatcher.h"
#include <QtDebug>

/**
 * The callback instances are setup inside this constructor.
 * It's easy to say that the callback instances are implemented
 * by our class instance itself.
 */
AbstractStateMachineDispatcher::AbstractStateMachineDispatcher()
{
	AbstractStateMachine::init();
}

/**
 * The destructor calls the statemachine's exit() method,
 * calls the react() method for processing outgoing signals
 * and frees all known timer.
 */
AbstractStateMachineDispatcher::~AbstractStateMachineDispatcher()
{
}

void AbstractStateMachineDispatcher::start()
{
	// Do some custom initialization.
	initializeValues();

	AbstractStateMachine::clearOutEvents();
	AbstractStateMachine::enter();
	react();
}

void AbstractStateMachineDispatcher::stop()
{
	AbstractStateMachine::clearOutEvents();
	AbstractStateMachine::exit();
	react();
}

void AbstractStateMachineDispatcher::runCycle()
{
	AbstractStateMachine::runCycle();
	react();
}

void AbstractStateMachineDispatcher::react()
{

	/**********************************
	 * Gui scope
	 *********************************/
	
	if (ifaceGui.isRaised_off())
	{
		sctQtDebug("emit Off()...");
		emit Off();
	}
	if (ifaceGui.isRaised_on())
	{
		sctQtDebug("emit On()...");
		emit On();
	}
}

void AbstractStateMachineDispatcher::sctQtDebug(const QString &message) const
{
	qDebug() << message;
}


/**********************************
 * Gui scope
 *********************************/


void AbstractStateMachineDispatcher::Clicked( )
{
	sctQtDebug("Clicked()...");
	ifaceGui.raise_clicked();
	runCycle();
}
