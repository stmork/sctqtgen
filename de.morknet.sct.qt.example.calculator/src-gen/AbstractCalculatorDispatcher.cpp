/*
 * Copyright (C) 2016 - Steffen A. Mork
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
	qDebug("# Button0()...");
	ifaceGui.raise_button0();
	runCycle();
}

void AbstractCalculatorDispatcher::Button1( )
{
	qDebug("# Button1()...");
	ifaceGui.raise_button1();
	runCycle();
}

void AbstractCalculatorDispatcher::Button2( )
{
	qDebug("# Button2()...");
	ifaceGui.raise_button2();
	runCycle();
}

void AbstractCalculatorDispatcher::Button3( )
{
	qDebug("# Button3()...");
	ifaceGui.raise_button3();
	runCycle();
}

void AbstractCalculatorDispatcher::Button4( )
{
	qDebug("# Button4()...");
	ifaceGui.raise_button4();
	runCycle();
}

void AbstractCalculatorDispatcher::Button5( )
{
	qDebug("# Button5()...");
	ifaceGui.raise_button5();
	runCycle();
}

void AbstractCalculatorDispatcher::Button6( )
{
	qDebug("# Button6()...");
	ifaceGui.raise_button6();
	runCycle();
}

void AbstractCalculatorDispatcher::Button7( )
{
	qDebug("# Button7()...");
	ifaceGui.raise_button7();
	runCycle();
}

void AbstractCalculatorDispatcher::Button8( )
{
	qDebug("# Button8()...");
	ifaceGui.raise_button8();
	runCycle();
}

void AbstractCalculatorDispatcher::Button9( )
{
	qDebug("# Button9()...");
	ifaceGui.raise_button9();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonAdd( )
{
	qDebug("# ButtonAdd()...");
	ifaceGui.raise_buttonAdd();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonClear( )
{
	qDebug("# ButtonClear()...");
	ifaceGui.raise_buttonClear();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonDiv( )
{
	qDebug("# ButtonDiv()...");
	ifaceGui.raise_buttonDiv();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonEquals( )
{
	qDebug("# ButtonEquals()...");
	ifaceGui.raise_buttonEquals();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonMult( )
{
	qDebug("# ButtonMult()...");
	ifaceGui.raise_buttonMult();
	runCycle();
}

void AbstractCalculatorDispatcher::ButtonSub( )
{
	qDebug("# ButtonSub()...");
	ifaceGui.raise_buttonSub();
	runCycle();
}
