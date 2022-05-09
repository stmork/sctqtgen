/* Copyright (C) 2022 - Steffen A. Mork */

#include "TimerlessStatemachine.h"

/*! \file
Implementation of the state machine 'TimerlessStatemachine'
*/




TimerlessStatemachine::TimerlessStatemachine(QObject *parent) :
	QObject(parent),
	ifaceGui(nullptr),
	isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = TimerlessStatemachine::State::NO_STATE;
	
	clearInEvents();
}

TimerlessStatemachine::~TimerlessStatemachine()
{
}

TimerlessStatemachine::Gui::Gui(TimerlessStatemachine* parent) :
	clicked_raised(false),
	parent(parent)
{
}



TimerlessStatemachine::EventInstance* TimerlessStatemachine::getNextEvent()
{
	TimerlessStatemachine::EventInstance* nextEvent = 0;

	if(!incomingEventQueue.empty()) {
		nextEvent = incomingEventQueue.front();
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


void TimerlessStatemachine::dispatchEvent(TimerlessStatemachine::EventInstance * event)
{
	if(event == nullptr) {
		return;
	}
								
	switch(event->eventId)
	{
		
		case TimerlessStatemachine::Event::Gui_clicked:
		{
			ifaceGui.clicked_raised = true;
			break;
		}
		
		default:
			break;
	}
	delete event;
}


void TimerlessStatemachine::gui_clicked() {
	incomingEventQueue.push_back(new TimerlessStatemachine::EventInstance(TimerlessStatemachine::Event::Gui_clicked));
	runCycle();
}


/*! Can be used by the client code to trigger a run to completion step without raising an event. */
void TimerlessStatemachine::triggerWithoutEvent() {
	runCycle();
}



bool TimerlessStatemachine::isActive() const
{
	return stateConfVector[0] != TimerlessStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool TimerlessStatemachine::isFinal() const
{
   return false;}

bool TimerlessStatemachine::check() const {
	return true;
}


bool TimerlessStatemachine::isStateActive(State state) const
{
	switch (state)
	{
		case TimerlessStatemachine::State::main_region_State_Off :
		{
			return  (stateConfVector[scvi_main_region_State_Off] == TimerlessStatemachine::State::main_region_State_Off);
			break;
		}
		case TimerlessStatemachine::State::main_region_State_On :
		{
			return  (stateConfVector[scvi_main_region_State_On] == TimerlessStatemachine::State::main_region_State_On);
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
}

TimerlessStatemachine::Gui* TimerlessStatemachine::gui()
{
	return &ifaceGui;
}

// implementations of all internal functions

/* Entry action for state 'State On'. */
void TimerlessStatemachine::enact_main_region_State_On()
{
	/* Entry action for state 'State On'. */
	emit gui_on();
}

/* Exit action for state 'State On'. */
void TimerlessStatemachine::exact_main_region_State_On()
{
	/* Exit action for state 'State On'. */
	emit gui_off();
}

/* 'default' enter sequence for state State Off */
void TimerlessStatemachine::enseq_main_region_State_Off_default()
{
	/* 'default' enter sequence for state State Off */
	stateConfVector[0] = TimerlessStatemachine::State::main_region_State_Off;
}

/* 'default' enter sequence for state State On */
void TimerlessStatemachine::enseq_main_region_State_On_default()
{
	/* 'default' enter sequence for state State On */
	enact_main_region_State_On();
	stateConfVector[0] = TimerlessStatemachine::State::main_region_State_On;
}

/* 'default' enter sequence for region main region */
void TimerlessStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state State Off */
void TimerlessStatemachine::exseq_main_region_State_Off()
{
	/* Default exit sequence for state State Off */
	stateConfVector[0] = TimerlessStatemachine::State::NO_STATE;
}

/* Default exit sequence for state State On */
void TimerlessStatemachine::exseq_main_region_State_On()
{
	/* Default exit sequence for state State On */
	stateConfVector[0] = TimerlessStatemachine::State::NO_STATE;
	exact_main_region_State_On();
}

/* Default exit sequence for region main region */
void TimerlessStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of TimerlessStatemachine.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case TimerlessStatemachine::State::main_region_State_Off :
		{
			exseq_main_region_State_Off();
			break;
		}
		case TimerlessStatemachine::State::main_region_State_On :
		{
			exseq_main_region_State_On();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void TimerlessStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_State_Off_default();
}

sc::integer TimerlessStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer TimerlessStatemachine::main_region_State_Off_react(const sc::integer transitioned_before) {
	/* The reactions of state State Off. */
	sc::integer transitioned_after = transitioned_before;
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

sc::integer TimerlessStatemachine::main_region_State_On_react(const sc::integer transitioned_before) {
	/* The reactions of state State On. */
	sc::integer transitioned_after = transitioned_before;
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

void TimerlessStatemachine::clearInEvents() {
	ifaceGui.clicked_raised = false;
}

void TimerlessStatemachine::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case TimerlessStatemachine::State::main_region_State_Off :
		{
			main_region_State_Off_react(-1);
			break;
		}
		case TimerlessStatemachine::State::main_region_State_On :
		{
			main_region_State_On_react(-1);
			break;
		}
		default: break;
	}
}

void TimerlessStatemachine::runCycle() {
	/* Performs a 'run to completion' step. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	dispatchEvent(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
		dispatchEvent(getNextEvent());
	} while (ifaceGui.clicked_raised);
	isExecuting = false;
}

void TimerlessStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart TimerlessStatemachine */
	enseq_main_region_default();
	isExecuting = false;
}

void TimerlessStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart TimerlessStatemachine */
	exseq_main_region();
	isExecuting = false;
}



