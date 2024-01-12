/* Copyright (C) 2024 - Steffen A. Mork */

#include "TimerlessStatemachine.h"

/*! \file
Implementation of the state machine 'Timerless'
*/




TimerlessStatemachine::TimerlessStatemachine(QObject *parent) noexcept :
	ifaceGui(nullptr),
	isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = TimerlessStatemachine::State::NO_STATE;
	
	clearInEvents();
}

TimerlessStatemachine::~TimerlessStatemachine()
{
}

TimerlessStatemachine::Gui::Gui(TimerlessStatemachine* parent_) noexcept :
	parent(parent_)
{
}



std::unique_ptr<TimerlessStatemachine::EventInstance> TimerlessStatemachine::getNextEvent() noexcept
{
	std::unique_ptr<TimerlessStatemachine::EventInstance> nextEvent = 0;

	if(!incomingEventQueue.empty()) {
		nextEvent = std::move(incomingEventQueue.front());
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


template<typename EWV, typename EV>
std::unique_ptr<EWV> cast_event_pointer_type (std::unique_ptr<EV>&& event){
    return std::unique_ptr<EWV>{static_cast<EWV*>(event.release())};
}
	
bool TimerlessStatemachine::dispatchEvent(std::unique_ptr<TimerlessStatemachine::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
	}
								
	switch(event->eventId)
	{
		
		case TimerlessStatemachine::Event::Gui_clicked:
		{
			ifaceGui.clicked_raised = true;
			break;
		}
		
		default:
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}


/*! Slot for the in event 'clicked' that is defined in the interface scope 'gui'. */
void TimerlessStatemachine::gui_clicked() {
	incomingEventQueue.push_back(std::unique_ptr<TimerlessStatemachine::EventInstance>(new TimerlessStatemachine::EventInstance(TimerlessStatemachine::Event::Gui_clicked)))
	;
	runCycle();
}



bool TimerlessStatemachine::isActive() const noexcept
{
	return stateConfVector[0] != TimerlessStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool TimerlessStatemachine::isFinal() const noexcept
{
	   return false;
}

bool TimerlessStatemachine::check() const noexcept{
	return true;
}


bool TimerlessStatemachine::isStateActive(State state) const noexcept
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
			/* State is not active*/
			return false;
			break;
		}
	}
}

TimerlessStatemachine::Gui& TimerlessStatemachine::gui() noexcept
{
	return ifaceGui;
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
	/* Handle exit of all possible states (of Timerless.main_region) at position 0... */
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
		default:
			/* do nothing */
			break;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void TimerlessStatemachine::clearInEvents() noexcept {
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
		default:
			/* do nothing */
			break;
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
	} while (dispatchEvent(getNextEvent()));
	isExecuting = false;
}

void TimerlessStatemachine::enter() {
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

void TimerlessStatemachine::exit() {
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

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void TimerlessStatemachine::triggerWithoutEvent() {
	runCycle();
}

