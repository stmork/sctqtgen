/* Copyright (C) 2022 - Steffen A. Mork */

#include "SynchronizationStatemachine.h"

/*! \file
Implementation of the state machine 'Synchronization'
*/




SynchronizationStatemachine::SynchronizationStatemachine(QObject *parent) :
	QObject(parent),
	ifaceOperationCallback(nullptr),
	isExecuting(false),
	stateConfVectorPosition(0),
	start_raised(false),
	triggerLeft_raised(false),
	triggerRight_raised(false)
{
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = SynchronizationStatemachine::State::NO_STATE;
	
	clearInEvents();
}

SynchronizationStatemachine::~SynchronizationStatemachine()
{
}



SynchronizationStatemachine::EventInstance* SynchronizationStatemachine::getNextEvent()
{
	SynchronizationStatemachine::EventInstance* nextEvent = 0;

	if(!incomingEventQueue.empty()) {
		nextEvent = incomingEventQueue.front();
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


void SynchronizationStatemachine::dispatchEvent(SynchronizationStatemachine::EventInstance * event)
{
	if(event == nullptr) {
		return;
	}
								
	switch(event->eventId)
	{
		case SynchronizationStatemachine::Event::start:
		{
			start_raised = true;
			break;
		}
		case SynchronizationStatemachine::Event::triggerLeft:
		{
			triggerLeft_raised = true;
			break;
		}
		case SynchronizationStatemachine::Event::triggerRight:
		{
			triggerRight_raised = true;
			break;
		}
		
		
		default:
			/* do nothing */
			break;
	}
	delete event;
}


void SynchronizationStatemachine::start() {
	incomingEventQueue.push_back(new SynchronizationStatemachine::EventInstance(SynchronizationStatemachine::Event::start));
	runCycle();
}


void SynchronizationStatemachine::triggerLeft() {
	incomingEventQueue.push_back(new SynchronizationStatemachine::EventInstance(SynchronizationStatemachine::Event::triggerLeft));
	runCycle();
}


void SynchronizationStatemachine::triggerRight() {
	incomingEventQueue.push_back(new SynchronizationStatemachine::EventInstance(SynchronizationStatemachine::Event::triggerRight));
	runCycle();
}



bool SynchronizationStatemachine::isActive() const
{
	return stateConfVector[0] != SynchronizationStatemachine::State::NO_STATE||stateConfVector[1] != SynchronizationStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool SynchronizationStatemachine::isFinal() const
{
   return false;}

bool SynchronizationStatemachine::check() const {
	if (this->ifaceOperationCallback == nullptr) {
		return false;
	}
	return true;
}


bool SynchronizationStatemachine::isStateActive(State state) const
{
	switch (state)
	{
		case SynchronizationStatemachine::State::main_region_Split :
		{
			return  (stateConfVector[scvi_main_region_Split] >= SynchronizationStatemachine::State::main_region_Split && stateConfVector[scvi_main_region_Split] <= SynchronizationStatemachine::State::main_region_Split_right_Wait);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_left_Action :
		{
			return  (stateConfVector[scvi_main_region_Split_left_Action] == SynchronizationStatemachine::State::main_region_Split_left_Action);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_left_Wait :
		{
			return  (stateConfVector[scvi_main_region_Split_left_Wait] == SynchronizationStatemachine::State::main_region_Split_left_Wait);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_right_Action :
		{
			return  (stateConfVector[scvi_main_region_Split_right_Action] == SynchronizationStatemachine::State::main_region_Split_right_Action);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_right_Wait :
		{
			return  (stateConfVector[scvi_main_region_Split_right_Wait] == SynchronizationStatemachine::State::main_region_Split_right_Wait);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Wait :
		{
			return  (stateConfVector[scvi_main_region_Wait] == SynchronizationStatemachine::State::main_region_Wait);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Completed :
		{
			return  (stateConfVector[scvi_main_region_Completed] == SynchronizationStatemachine::State::main_region_Completed);
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

void SynchronizationStatemachine::setOperationCallback(OperationCallback* operationCallback)
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions
/* Entry action for state 'Split'. */
void SynchronizationStatemachine::enact_main_region_Split()
{
	/* Entry action for state 'Split'. */
	ifaceOperationCallback->started();
}

/* Entry action for state 'Action'. */
void SynchronizationStatemachine::enact_main_region_Split_left_Action()
{
	/* Entry action for state 'Action'. */
	ifaceOperationCallback->left();
}

/* Entry action for state 'Wait'. */
void SynchronizationStatemachine::enact_main_region_Split_left_Wait()
{
	/* Entry action for state 'Wait'. */
	ifaceOperationCallback->leftClicked();
}

/* Entry action for state 'Action'. */
void SynchronizationStatemachine::enact_main_region_Split_right_Action()
{
	/* Entry action for state 'Action'. */
	ifaceOperationCallback->right();
}

/* Entry action for state 'Wait'. */
void SynchronizationStatemachine::enact_main_region_Split_right_Wait()
{
	/* Entry action for state 'Wait'. */
	ifaceOperationCallback->rightClicked();
}

/* Entry action for state 'Wait'. */
void SynchronizationStatemachine::enact_main_region_Wait()
{
	/* Entry action for state 'Wait'. */
	ifaceOperationCallback->waiting();
}

/* Entry action for state 'Completed'. */
void SynchronizationStatemachine::enact_main_region_Completed()
{
	/* Entry action for state 'Completed'. */
	ifaceOperationCallback->completed();
}

/* 'default' enter sequence for state Action */
void SynchronizationStatemachine::enseq_main_region_Split_left_Action_default()
{
	/* 'default' enter sequence for state Action */
	enact_main_region_Split_left_Action();
	stateConfVector[0] = SynchronizationStatemachine::State::main_region_Split_left_Action;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Wait */
void SynchronizationStatemachine::enseq_main_region_Split_left_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Split_left_Wait();
	stateConfVector[0] = SynchronizationStatemachine::State::main_region_Split_left_Wait;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Action */
void SynchronizationStatemachine::enseq_main_region_Split_right_Action_default()
{
	/* 'default' enter sequence for state Action */
	enact_main_region_Split_right_Action();
	stateConfVector[1] = SynchronizationStatemachine::State::main_region_Split_right_Action;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state Wait */
void SynchronizationStatemachine::enseq_main_region_Split_right_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Split_right_Wait();
	stateConfVector[1] = SynchronizationStatemachine::State::main_region_Split_right_Wait;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state Wait */
void SynchronizationStatemachine::enseq_main_region_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Wait();
	stateConfVector[0] = SynchronizationStatemachine::State::main_region_Wait;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Completed */
void SynchronizationStatemachine::enseq_main_region_Completed_default()
{
	/* 'default' enter sequence for state Completed */
	enact_main_region_Completed();
	stateConfVector[0] = SynchronizationStatemachine::State::main_region_Completed;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void SynchronizationStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state Split */
void SynchronizationStatemachine::exseq_main_region_Split()
{
	/* Default exit sequence for state Split */
	exseq_main_region_Split_left();
	exseq_main_region_Split_right();
}

/* Default exit sequence for state Action */
void SynchronizationStatemachine::exseq_main_region_Split_left_Action()
{
	/* Default exit sequence for state Action */
	stateConfVector[0] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Wait */
void SynchronizationStatemachine::exseq_main_region_Split_left_Wait()
{
	/* Default exit sequence for state Wait */
	stateConfVector[0] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Action */
void SynchronizationStatemachine::exseq_main_region_Split_right_Action()
{
	/* Default exit sequence for state Action */
	stateConfVector[1] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for state Wait */
void SynchronizationStatemachine::exseq_main_region_Split_right_Wait()
{
	/* Default exit sequence for state Wait */
	stateConfVector[1] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for state Wait */
void SynchronizationStatemachine::exseq_main_region_Wait()
{
	/* Default exit sequence for state Wait */
	stateConfVector[0] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Completed */
void SynchronizationStatemachine::exseq_main_region_Completed()
{
	/* Default exit sequence for state Completed */
	stateConfVector[0] = SynchronizationStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void SynchronizationStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Synchronization.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case SynchronizationStatemachine::State::main_region_Split_left_Action :
		{
			exseq_main_region_Split_left_Action();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_left_Wait :
		{
			exseq_main_region_Split_left_Wait();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Wait :
		{
			exseq_main_region_Wait();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Completed :
		{
			exseq_main_region_Completed();
			break;
		}
		default:
			/* do nothing */
			break;
	}
	/* Handle exit of all possible states (of Synchronization.main_region) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case SynchronizationStatemachine::State::main_region_Split_right_Action :
		{
			exseq_main_region_Split_right_Action();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_right_Wait :
		{
			exseq_main_region_Split_right_Wait();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region left */
void SynchronizationStatemachine::exseq_main_region_Split_left()
{
	/* Default exit sequence for region left */
	/* Handle exit of all possible states (of Synchronization.main_region.Split.left) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case SynchronizationStatemachine::State::main_region_Split_left_Action :
		{
			exseq_main_region_Split_left_Action();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_left_Wait :
		{
			exseq_main_region_Split_left_Wait();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region right */
void SynchronizationStatemachine::exseq_main_region_Split_right()
{
	/* Default exit sequence for region right */
	/* Handle exit of all possible states (of Synchronization.main_region.Split.right) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case SynchronizationStatemachine::State::main_region_Split_right_Action :
		{
			exseq_main_region_Split_right_Action();
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_right_Wait :
		{
			exseq_main_region_Split_right_Wait();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default react sequence for initial entry  */
void SynchronizationStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Wait_default();
}

/* The reactions of state null. */
void SynchronizationStatemachine::react_main_region__sync0()
{
	/* The reactions of state null. */
	enact_main_region_Split();
	enseq_main_region_Split_left_Action_default();
	enseq_main_region_Split_right_Action_default();
}

/* The reactions of state null. */
void SynchronizationStatemachine::react_main_region__sync1()
{
	/* The reactions of state null. */
	enseq_main_region_Completed_default();
}

sc::integer SynchronizationStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer SynchronizationStatemachine::main_region_Split_react(const sc::integer transitioned_before) {
	/* The reactions of state Split. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer SynchronizationStatemachine::main_region_Split_left_Action_react(const sc::integer transitioned_before) {
	/* The reactions of state Action. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (triggerLeft_raised)
		{ 
			exseq_main_region_Split_left_Action();
			enseq_main_region_Split_left_Wait_default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc::integer SynchronizationStatemachine::main_region_Split_left_Wait_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (isStateActive(SynchronizationStatemachine::State::main_region_Split_right_Wait))
		{ 
			exseq_main_region_Split();
			react_main_region__sync1();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc::integer SynchronizationStatemachine::main_region_Split_right_Action_react(const sc::integer transitioned_before) {
	/* The reactions of state Action. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (triggerRight_raised)
		{ 
			exseq_main_region_Split_right_Action();
			enseq_main_region_Split_right_Wait_default();
			main_region_Split_react(0);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Split_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer SynchronizationStatemachine::main_region_Split_right_Wait_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (isStateActive(SynchronizationStatemachine::State::main_region_Split_left_Wait))
		{ 
			exseq_main_region_Split();
			react_main_region__sync1();
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Split_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer SynchronizationStatemachine::main_region_Wait_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (start_raised)
		{ 
			exseq_main_region_Wait();
			react_main_region__sync0();
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

sc::integer SynchronizationStatemachine::main_region_Completed_react(const sc::integer transitioned_before) {
	/* The reactions of state Completed. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (start_raised)
		{ 
			exseq_main_region_Completed();
			enseq_main_region_Wait_default();
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

void SynchronizationStatemachine::clearInEvents() {
	start_raised = false;
	triggerLeft_raised = false;
	triggerRight_raised = false;
}

void SynchronizationStatemachine::microStep() {
	sc::integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case SynchronizationStatemachine::State::main_region_Split_left_Action :
		{
			transitioned = main_region_Split_left_Action_react(transitioned);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Split_left_Wait :
		{
			transitioned = main_region_Split_left_Wait_react(transitioned);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Wait :
		{
			transitioned = main_region_Wait_react(transitioned);
			break;
		}
		case SynchronizationStatemachine::State::main_region_Completed :
		{
			transitioned = main_region_Completed_react(transitioned);
			break;
		}
		default:
			/* do nothing */
			break;
	}
	if ((stateConfVectorPosition) < (1))
	{ 
		switch(stateConfVector[ 1 ])
		{
			case SynchronizationStatemachine::State::main_region_Split_right_Action :
			{
				main_region_Split_right_Action_react(transitioned);
				break;
			}
			case SynchronizationStatemachine::State::main_region_Split_right_Wait :
			{
				main_region_Split_right_Wait_react(transitioned);
				break;
			}
			default:
				/* do nothing */
				break;
		}
	} 
}

void SynchronizationStatemachine::runCycle() {
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
	} while (((start_raised) || (triggerLeft_raised)) || (triggerRight_raised));
	isExecuting = false;
}

void SynchronizationStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Synchronization */
	enseq_main_region_default();
	isExecuting = false;
}

void SynchronizationStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Synchronization */
	exseq_main_region();
	isExecuting = false;
}

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void SynchronizationStatemachine::triggerWithoutEvent() {
	runCycle();
}

