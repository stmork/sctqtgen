/* Copyright (C) 2021 - Steffen A. Mork */

#include "AbstractTimerLess.h"

/*! \file Implementation of the state machine 'Timerless'
*/




AbstractTimerLess::AbstractTimerLess(QObject *parent)  :
QObject(parent),
ifaceGui(sc_null),
isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Timerless_last_state;
	
	clearInEvents();
}

AbstractTimerLess::~AbstractTimerLess()
{
}

AbstractTimerLess::Gui::Gui(AbstractTimerLess* parent) :
clicked_raised(false),
parent(parent)
{
}


using namespace timerless_events;

SctEvent* AbstractTimerLess::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void AbstractTimerLess::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case AbstractTimerLessEventName::Gui_clicked:
		{
			ifaceGui.dispatch_event(event);
			break;
		}
		default:
			break;
	}
	delete event;
}

void AbstractTimerLess::Gui::dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case AbstractTimerLessEventName::Gui_clicked:
		{
			internal_gui_clicked();
			break;
		}
		default:
			break;
	}
}



sc_boolean AbstractTimerLess::isActive() const
{
	return stateConfVector[0] != Timerless_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean AbstractTimerLess::isFinal() const
{
   return false;}

sc_boolean AbstractTimerLess::check() {
	return true;
}


sc_boolean AbstractTimerLess::isStateActive(TimerlessStates state) const
{
	switch (state)
	{
		case main_region_State_Off : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_STATE_OFF] == main_region_State_Off
			);
		case main_region_State_On : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_STATE_ON] == main_region_State_On
			);
		default: return false;
	}
}

AbstractTimerLess::Gui* AbstractTimerLess::gui()
{
	return &ifaceGui;
}
/* Functions for event clicked in interface Gui */
void AbstractTimerLess::gui_clicked()
{
	inEventQueue.push_back(new SctEvent_Gui_clicked(AbstractTimerLessEventName::Gui_clicked));
	runCycle();
}
void AbstractTimerLess::Gui::internal_gui_clicked()
{
	clicked_raised = true;
}
/* Functions for event on in interface Gui */
/* Functions for event off in interface Gui */

// implementations of all internal functions

/* Entry action for state 'State On'. */
void AbstractTimerLess::enact_main_region_State_On()
{
	/* Entry action for state 'State On'. */
	emit gui_on();
}

/* Exit action for state 'State On'. */
void AbstractTimerLess::exact_main_region_State_On()
{
	/* Exit action for state 'State On'. */
	emit gui_off();
}

/* 'default' enter sequence for state State Off */
void AbstractTimerLess::enseq_main_region_State_Off_default()
{
	/* 'default' enter sequence for state State Off */
	stateConfVector[0] = main_region_State_Off;
}

/* 'default' enter sequence for state State On */
void AbstractTimerLess::enseq_main_region_State_On_default()
{
	/* 'default' enter sequence for state State On */
	enact_main_region_State_On();
	stateConfVector[0] = main_region_State_On;
}

/* 'default' enter sequence for region main region */
void AbstractTimerLess::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state State Off */
void AbstractTimerLess::exseq_main_region_State_Off()
{
	/* Default exit sequence for state State Off */
	stateConfVector[0] = Timerless_last_state;
}

/* Default exit sequence for state State On */
void AbstractTimerLess::exseq_main_region_State_On()
{
	/* Default exit sequence for state State On */
	stateConfVector[0] = Timerless_last_state;
	exact_main_region_State_On();
}

/* Default exit sequence for region main region */
void AbstractTimerLess::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Timerless.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_State_Off :
		{
			exseq_main_region_State_Off();
			break;
		}
		case main_region_State_On :
		{
			exseq_main_region_State_On();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void AbstractTimerLess::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_State_Off_default();
}

sc_integer AbstractTimerLess::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer AbstractTimerLess::main_region_State_Off_react(const sc_integer transitioned_before) {
	/* The reactions of state State Off. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.clicked_raised)
		{ 
			exseq_main_region_State_Off();
			enseq_main_region_State_On_default();
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

sc_integer AbstractTimerLess::main_region_State_On_react(const sc_integer transitioned_before) {
	/* The reactions of state State On. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.clicked_raised)
		{ 
			exseq_main_region_State_On();
			enseq_main_region_State_Off_default();
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

void AbstractTimerLess::clearInEvents() {
	ifaceGui.clicked_raised = false;
}

void AbstractTimerLess::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case main_region_State_Off :
		{
			main_region_State_Off_react(-1);
			break;
		}
		case main_region_State_On :
		{
			main_region_State_On_react(-1);
			break;
		}
		default: break;
	}
}

void AbstractTimerLess::runCycle() {
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
	} while (ifaceGui.clicked_raised);
	isExecuting = false;
}

void AbstractTimerLess::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Timerless */
	enseq_main_region_default();
	isExecuting = false;
}

void AbstractTimerLess::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Timerless */
	exseq_main_region();
	isExecuting = false;
}



