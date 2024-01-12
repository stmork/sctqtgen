/* Copyright (C) 2024 - Steffen A. Mork */

#include "DelayedStatemachine.h"

/*! \file
Implementation of the state machine 'Delayed'
*/




DelayedStatemachine::DelayedStatemachine(QObject *parent) noexcept :
	ifaceGui(nullptr),
	isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = DelayedStatemachine::State::NO_STATE;
	
	clearInEvents();
}

DelayedStatemachine::~DelayedStatemachine()
{
}

DelayedStatemachine::Gui::Gui(DelayedStatemachine* parent_) noexcept :
	parent(parent_)
{
}



std::unique_ptr<DelayedStatemachine::EventInstance> DelayedStatemachine::getNextEvent() noexcept
{
	std::unique_ptr<DelayedStatemachine::EventInstance> nextEvent = 0;

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
	
bool DelayedStatemachine::dispatchEvent(std::unique_ptr<DelayedStatemachine::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
	}
								
	switch(event->eventId)
	{
		
		case DelayedStatemachine::Event::Gui_button1:
		{
			ifaceGui.button1_raised = true;
			break;
		}
		case DelayedStatemachine::Event::Gui_button2:
		{
			ifaceGui.button2_raised = true;
			break;
		}
		case DelayedStatemachine::Event::Gui_complete:
		{
			ifaceGui.complete_raised = true;
			break;
		}
		
		default:
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}


/*! Slot for the in event 'button1' that is defined in the interface scope 'gui'. */
void DelayedStatemachine::gui_button1() {
	incomingEventQueue.push_back(std::unique_ptr<DelayedStatemachine::EventInstance>(new DelayedStatemachine::EventInstance(DelayedStatemachine::Event::Gui_button1)))
	;
	runCycle();
}


/*! Slot for the in event 'button2' that is defined in the interface scope 'gui'. */
void DelayedStatemachine::gui_button2() {
	incomingEventQueue.push_back(std::unique_ptr<DelayedStatemachine::EventInstance>(new DelayedStatemachine::EventInstance(DelayedStatemachine::Event::Gui_button2)))
	;
	runCycle();
}


/*! Slot for the in event 'complete' that is defined in the interface scope 'gui'. */
void DelayedStatemachine::gui_complete() {
	incomingEventQueue.push_back(std::unique_ptr<DelayedStatemachine::EventInstance>(new DelayedStatemachine::EventInstance(DelayedStatemachine::Event::Gui_complete)))
	;
	runCycle();
}



bool DelayedStatemachine::isActive() const noexcept
{
	return stateConfVector[0] != DelayedStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool DelayedStatemachine::isFinal() const noexcept
{
	   return false;
}

bool DelayedStatemachine::check() const noexcept{
	return true;
}


bool DelayedStatemachine::isStateActive(State state) const noexcept
{
	switch (state)
	{
		case DelayedStatemachine::State::main_region_StateA :
		{
			return  (stateConfVector[scvi_main_region_StateA] == DelayedStatemachine::State::main_region_StateA);
			break;
		}
		case DelayedStatemachine::State::main_region_Do_Something :
		{
			return  (stateConfVector[scvi_main_region_Do_Something] == DelayedStatemachine::State::main_region_Do_Something);
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_1 :
		{
			return  (stateConfVector[scvi_main_region_Wait_Button_1] == DelayedStatemachine::State::main_region_Wait_Button_1);
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_2 :
		{
			return  (stateConfVector[scvi_main_region_Wait_Button_2] == DelayedStatemachine::State::main_region_Wait_Button_2);
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

DelayedStatemachine::Gui& DelayedStatemachine::gui() noexcept
{
	return ifaceGui;
}

// implementations of all internal functions
/* Entry action for state 'StateA'. */
void DelayedStatemachine::enact_main_region_StateA()
{
	/* Entry action for state 'StateA'. */
	emit gui_stateA();
}

/* Entry action for state 'Do Something'. */
void DelayedStatemachine::enact_main_region_Do_Something()
{
	/* Entry action for state 'Do Something'. */
	emit gui_doSomething();
}

/* Entry action for state 'Wait Button 1'. */
void DelayedStatemachine::enact_main_region_Wait_Button_1()
{
	/* Entry action for state 'Wait Button 1'. */
	emit gui_stopping(true);
}

/* Entry action for state 'Wait Button 2'. */
void DelayedStatemachine::enact_main_region_Wait_Button_2()
{
	/* Entry action for state 'Wait Button 2'. */
	emit gui_stopping(true);
}

/* Exit action for state 'Do Something'. */
void DelayedStatemachine::exact_main_region_Do_Something()
{
	/* Exit action for state 'Do Something'. */
	emit gui_triggerStop();
}

/* Exit action for state 'Wait Button 1'. */
void DelayedStatemachine::exact_main_region_Wait_Button_1()
{
	/* Exit action for state 'Wait Button 1'. */
	emit gui_stopping(false);
}

/* Exit action for state 'Wait Button 2'. */
void DelayedStatemachine::exact_main_region_Wait_Button_2()
{
	/* Exit action for state 'Wait Button 2'. */
	emit gui_stopping(false);
}

/* 'default' enter sequence for state StateA */
void DelayedStatemachine::enseq_main_region_StateA_default()
{
	/* 'default' enter sequence for state StateA */
	enact_main_region_StateA();
	stateConfVector[0] = DelayedStatemachine::State::main_region_StateA;
}

/* 'default' enter sequence for state Do Something */
void DelayedStatemachine::enseq_main_region_Do_Something_default()
{
	/* 'default' enter sequence for state Do Something */
	enact_main_region_Do_Something();
	stateConfVector[0] = DelayedStatemachine::State::main_region_Do_Something;
}

/* 'default' enter sequence for state Wait Button 1 */
void DelayedStatemachine::enseq_main_region_Wait_Button_1_default()
{
	/* 'default' enter sequence for state Wait Button 1 */
	enact_main_region_Wait_Button_1();
	stateConfVector[0] = DelayedStatemachine::State::main_region_Wait_Button_1;
}

/* 'default' enter sequence for state Wait Button 2 */
void DelayedStatemachine::enseq_main_region_Wait_Button_2_default()
{
	/* 'default' enter sequence for state Wait Button 2 */
	enact_main_region_Wait_Button_2();
	stateConfVector[0] = DelayedStatemachine::State::main_region_Wait_Button_2;
}

/* 'default' enter sequence for region main region */
void DelayedStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state StateA */
void DelayedStatemachine::exseq_main_region_StateA()
{
	/* Default exit sequence for state StateA */
	stateConfVector[0] = DelayedStatemachine::State::NO_STATE;
}

/* Default exit sequence for state Do Something */
void DelayedStatemachine::exseq_main_region_Do_Something()
{
	/* Default exit sequence for state Do Something */
	stateConfVector[0] = DelayedStatemachine::State::NO_STATE;
	exact_main_region_Do_Something();
}

/* Default exit sequence for state Wait Button 1 */
void DelayedStatemachine::exseq_main_region_Wait_Button_1()
{
	/* Default exit sequence for state Wait Button 1 */
	stateConfVector[0] = DelayedStatemachine::State::NO_STATE;
	exact_main_region_Wait_Button_1();
}

/* Default exit sequence for state Wait Button 2 */
void DelayedStatemachine::exseq_main_region_Wait_Button_2()
{
	/* Default exit sequence for state Wait Button 2 */
	stateConfVector[0] = DelayedStatemachine::State::NO_STATE;
	exact_main_region_Wait_Button_2();
}

/* Default exit sequence for region main region */
void DelayedStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Delayed.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case DelayedStatemachine::State::main_region_StateA :
		{
			exseq_main_region_StateA();
			break;
		}
		case DelayedStatemachine::State::main_region_Do_Something :
		{
			exseq_main_region_Do_Something();
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_1 :
		{
			exseq_main_region_Wait_Button_1();
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_2 :
		{
			exseq_main_region_Wait_Button_2();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default react sequence for initial entry  */
void DelayedStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_StateA_default();
}

sc::integer DelayedStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer DelayedStatemachine::main_region_StateA_react(const sc::integer transitioned_before) {
	/* The reactions of state StateA. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		if (ifaceGui.button1_raised)
		{ 
			emit gui_stopped();
		} 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer DelayedStatemachine::main_region_Do_Something_react(const sc::integer transitioned_before) {
	/* The reactions of state Do Something. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer DelayedStatemachine::main_region_Wait_Button_1_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait Button 1. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer DelayedStatemachine::main_region_Wait_Button_2_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait Button 2. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void DelayedStatemachine::clearInEvents() noexcept {
	ifaceGui.button1_raised = false;
	ifaceGui.button2_raised = false;
	ifaceGui.complete_raised = false;
}

void DelayedStatemachine::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case DelayedStatemachine::State::main_region_StateA :
		{
			main_region_StateA_react(-1);
			break;
		}
		case DelayedStatemachine::State::main_region_Do_Something :
		{
			main_region_Do_Something_react(-1);
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_1 :
		{
			main_region_Wait_Button_1_react(-1);
			break;
		}
		case DelayedStatemachine::State::main_region_Wait_Button_2 :
		{
			main_region_Wait_Button_2_react(-1);
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

void DelayedStatemachine::runCycle() {
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

void DelayedStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Delayed */
	enseq_main_region_default();
	isExecuting = false;
}

void DelayedStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Delayed */
	exseq_main_region();
	isExecuting = false;
}

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void DelayedStatemachine::triggerWithoutEvent() {
	runCycle();
}

