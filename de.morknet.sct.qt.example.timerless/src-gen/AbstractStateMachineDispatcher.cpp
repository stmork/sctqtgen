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
	init();
}

/**
 * The destructor calls the statemachines exit() method,
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

	clearOutEvents();
	enter();
	react();
}

void AbstractStateMachineDispatcher::stop()
{
	clearOutEvents();
	exit();
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
		emit Off();
	}
	if (ifaceGui.isRaised_on())
	{
		emit On();
	}
}


/**********************************
 * Gui scope
 *********************************/


void AbstractStateMachineDispatcher::Clicked( )
{
	qDebug("# Clicked()...");
	ifaceGui.raise_clicked();
	runCycle();
}
