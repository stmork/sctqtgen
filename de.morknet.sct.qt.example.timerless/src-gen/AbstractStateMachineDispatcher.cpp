/*
 * Copyright (C) 2020 - Steffen A. Mork
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
AbstractStateMachineDispatcher::AbstractStateMachineDispatcher(QObject * parent) :
	QObject(parent)
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

void AbstractStateMachineDispatcher::start(void)
{
	// Do some custom initialization.
	initializeValues();

	AbstractStateMachine::clearOutEvents();
	AbstractStateMachine::enter();
	react();
}

void AbstractStateMachineDispatcher::stop(void)
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

void AbstractStateMachineDispatcher::react(void)
{

	/**********************************
	 * Gui scope
	 *********************************/
	
	if (ifaceGui.isRaised_off())
	{
		sctQtDebug("emit off()...");
		emit off();
	}
	if (ifaceGui.isRaised_on())
	{
		sctQtDebug("emit on()...");
		emit on();
	}
}

void AbstractStateMachineDispatcher::sctQtDebug(const QString & message) const
{
	qDebug() << message;
}


/**********************************
 * Gui scope
 *********************************/


void AbstractStateMachineDispatcher::clicked( )
{
	sctQtDebug("clicked()...");
	ifaceGui.raise_clicked();
	runCycle();
}
