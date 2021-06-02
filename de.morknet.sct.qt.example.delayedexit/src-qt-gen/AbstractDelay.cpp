/* Copyright (C) 2020 - Steffen A. Mork */

#include "AbstractDelay.h"

/*! \file Implementation of the state machine 'DelayedExit'
*/




AbstractDelay::AbstractDelay(QObject *parent)  :
QObject(parent),
ifaceGui(sc_null),
isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = DelayedExit_last_state;
	
	clearInEvents();
}

AbstractDelay::~AbstractDelay()
{
}

AbstractDelay::Gui::Gui(AbstractDelay* parent) :
button1_raised(false),
button2_raised(false),
complete_raised(false),
parent(parent)
{
}


using namespace delayedexit_events;

SctEvent* AbstractDelay::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void AbstractDelay::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case AbstractDelayEventName::Gui_button1:
		case AbstractDelayEventName::Gui_button2:
		case AbstractDelayEventName::Gui_complete:
		{
			ifaceGui.dispatch_event(event);
			break;
		}
		default:
			break;
	}
	delete event;
}

void AbstractDelay::Gui::dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case AbstractDelayEventName::Gui_button1:
		{
			internal_gui_button1();
			break;
		}
		case AbstractDelayEventName::Gui_button2:
		{
			internal_gui_button2();
			break;
		}
		case AbstractDelayEventName::Gui_complete:
		{
			internal_gui_complete();
			break;
		}
		default:
			break;
	}
}



sc_boolean AbstractDelay::isActive() const
{
	return stateConfVector[0] != DelayedExit_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean AbstractDelay::isFinal() const
{
   return false;}

sc_boolean AbstractDelay::check() {
	return true;
}


sc_boolean AbstractDelay::isStateActive(DelayedExitStates state) const
{
	switch (state)
	{
		case main_region_StateA : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_STATEA] == main_region_StateA
			);
		case main_region_Do_Something : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_DO_SOMETHING] == main_region_Do_Something
			);
		case main_region_Wait_Button_1 : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_WAIT_BUTTON_1] == main_region_Wait_Button_1
			);
		case main_region_Wait_Button_2 : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_WAIT_BUTTON_2] == main_region_Wait_Button_2
			);
		default: return false;
	}
}

AbstractDelay::Gui* AbstractDelay::gui()
{
	return &ifaceGui;
}
/* Functions for event button1 in interface Gui */
void AbstractDelay::gui_button1()
{
	inEventQueue.push_back(new SctEvent_Gui_button1(AbstractDelayEventName::Gui_button1));
	runCycle();
}
void AbstractDelay::Gui::internal_gui_button1()
{
	button1_raised = true;
}
/* Functions for event button2 in interface Gui */
void AbstractDelay::gui_button2()
{
	inEventQueue.push_back(new SctEvent_Gui_button2(AbstractDelayEventName::Gui_button2));
	runCycle();
}
void AbstractDelay::Gui::internal_gui_button2()
{
	button2_raised = true;
}
/* Functions for event complete in interface Gui */
void AbstractDelay::gui_complete()
{
	inEventQueue.push_back(new SctEvent_Gui_complete(AbstractDelayEventName::Gui_complete));
	runCycle();
}
void AbstractDelay::Gui::internal_gui_complete()
{
	complete_raised = true;
}
/* Functions for event stateA in interface Gui */
/* Functions for event doSomething in interface Gui */
/* Functions for event stopping in interface Gui */
/* Functions for event triggerStop in interface Gui */
/* Functions for event stopped in interface Gui */

// implementations of all internal functions

/* Entry action for state 'StateA'. */
void AbstractDelay::enact_main_region_StateA()
{
	/* Entry action for state 'StateA'. */
	emit gui_stateA();
}

/* Entry action for state 'Do Something'. */
void AbstractDelay::enact_main_region_Do_Something()
{
	/* Entry action for state 'Do Something'. */
	emit gui_doSomething();
}

/* Entry action for state 'Wait Button 1'. */
void AbstractDelay::enact_main_region_Wait_Button_1()
{
	/* Entry action for state 'Wait Button 1'. */
	emit gui_stopping(true);
}

/* Entry action for state 'Wait Button 2'. */
void AbstractDelay::enact_main_region_Wait_Button_2()
{
	/* Entry action for state 'Wait Button 2'. */
	emit gui_stopping(true);
}

/* Exit action for state 'Do Something'. */
void AbstractDelay::exact_main_region_Do_Something()
{
	/* Exit action for state 'Do Something'. */
	emit gui_triggerStop();
}

/* Exit action for state 'Wait Button 1'. */
void AbstractDelay::exact_main_region_Wait_Button_1()
{
	/* Exit action for state 'Wait Button 1'. */
	emit gui_stopping(false);
}

/* Exit action for state 'Wait Button 2'. */
void AbstractDelay::exact_main_region_Wait_Button_2()
{
	/* Exit action for state 'Wait Button 2'. */
	emit gui_stopping(false);
}

/* 'default' enter sequence for state StateA */
void AbstractDelay::enseq_main_region_StateA_default()
{
	/* 'default' enter sequence for state StateA */
	enact_main_region_StateA();
	stateConfVector[0] = main_region_StateA;
}

/* 'default' enter sequence for state Do Something */
void AbstractDelay::enseq_main_region_Do_Something_default()
{
	/* 'default' enter sequence for state Do Something */
	enact_main_region_Do_Something();
	stateConfVector[0] = main_region_Do_Something;
}

/* 'default' enter sequence for state Wait Button 1 */
void AbstractDelay::enseq_main_region_Wait_Button_1_default()
{
	/* 'default' enter sequence for state Wait Button 1 */
	enact_main_region_Wait_Button_1();
	stateConfVector[0] = main_region_Wait_Button_1;
}

/* 'default' enter sequence for state Wait Button 2 */
void AbstractDelay::enseq_main_region_Wait_Button_2_default()
{
	/* 'default' enter sequence for state Wait Button 2 */
	enact_main_region_Wait_Button_2();
	stateConfVector[0] = main_region_Wait_Button_2;
}

/* 'default' enter sequence for region main region */
void AbstractDelay::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state StateA */
void AbstractDelay::exseq_main_region_StateA()
{
	/* Default exit sequence for state StateA */
	stateConfVector[0] = DelayedExit_last_state;
}

/* Default exit sequence for state Do Something */
void AbstractDelay::exseq_main_region_Do_Something()
{
	/* Default exit sequence for state Do Something */
	stateConfVector[0] = DelayedExit_last_state;
	exact_main_region_Do_Something();
}

/* Default exit sequence for state Wait Button 1 */
void AbstractDelay::exseq_main_region_Wait_Button_1()
{
	/* Default exit sequence for state Wait Button 1 */
	stateConfVector[0] = DelayedExit_last_state;
	exact_main_region_Wait_Button_1();
}

/* Default exit sequence for state Wait Button 2 */
void AbstractDelay::exseq_main_region_Wait_Button_2()
{
	/* Default exit sequence for state Wait Button 2 */
	stateConfVector[0] = DelayedExit_last_state;
	exact_main_region_Wait_Button_2();
}

/* Default exit sequence for region main region */
void AbstractDelay::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of DelayedExit.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_StateA :
		{
			exseq_main_region_StateA();
			break;
		}
		case main_region_Do_Something :
		{
			exseq_main_region_Do_Something();
			break;
		}
		case main_region_Wait_Button_1 :
		{
			exseq_main_region_Wait_Button_1();
			break;
		}
		case main_region_Wait_Button_2 :
		{
			exseq_main_region_Wait_Button_2();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void AbstractDelay::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_StateA_default();
}

sc_integer AbstractDelay::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer AbstractDelay::main_region_StateA_react(const sc_integer transitioned_before) {
	/* The reactions of state StateA. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if ((ifaceGui.button1_raised) || (ifaceGui.button2_raised))
		{ 
			exseq_main_region_StateA();
			enseq_main_region_Do_Something_default();
			react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		if (ifaceGui.button1_raised)
		{ 
			emit gui_stopped();
		} 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer AbstractDelay::main_region_Do_Something_react(const sc_integer transitioned_before) {
	/* The reactions of state Do Something. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.button2_raised)
		{ 
			exseq_main_region_Do_Something();
			enseq_main_region_Wait_Button_2_default();
			react(0);
			transitioned_after = 0;
		}  else
		{
			if (ifaceGui.button1_raised)
			{ 
				exseq_main_region_Do_Something();
				enseq_main_region_Wait_Button_1_default();
				react(0);
				transitioned_after = 0;
			} 
		}
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer AbstractDelay::main_region_Wait_Button_1_react(const sc_integer transitioned_before) {
	/* The reactions of state Wait Button 1. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.complete_raised)
		{ 
			exseq_main_region_Wait_Button_1();
			enseq_main_region_StateA_default();
			react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer AbstractDelay::main_region_Wait_Button_2_react(const sc_integer transitioned_before) {
	/* The reactions of state Wait Button 2. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.complete_raised)
		{ 
			exseq_main_region_Wait_Button_2();
			enseq_main_region_Do_Something_default();
			react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void AbstractDelay::clearInEvents() {
	ifaceGui.button1_raised = false;
	ifaceGui.button2_raised = false;
	ifaceGui.complete_raised = false;
}

void AbstractDelay::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case main_region_StateA :
		{
			main_region_StateA_react(-1);
			break;
		}
		case main_region_Do_Something :
		{
			main_region_Do_Something_react(-1);
			break;
		}
		case main_region_Wait_Button_1 :
		{
			main_region_Wait_Button_1_react(-1);
			break;
		}
		case main_region_Wait_Button_2 :
		{
			main_region_Wait_Button_2_react(-1);
			break;
		}
		default: break;
	}
}

void AbstractDelay::runCycle() {
	/* Performs a 'run to completion' step. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	dispatch_event(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
		dispatch_event(getNextEvent());
	} while (((ifaceGui.button1_raised) || (ifaceGui.button2_raised)) || (ifaceGui.complete_raised));
	isExecuting = false;
}

void AbstractDelay::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart DelayedExit */
	enseq_main_region_default();
	isExecuting = false;
}

void AbstractDelay::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart DelayedExit */
	exseq_main_region();
	isExecuting = false;
}



