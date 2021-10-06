/* Copyright (C) GIRA Giersiepen GmbH & Co. KG */

#include "OrthogonalStatemachine.h"

/*! \file Implementation of the state machine 'Orthogonal'
*/




OrthogonalStatemachine::OrthogonalStatemachine(QObject *parent)  :
QObject(parent),
left(0),
right(0),
trigger_raised(false),
ifaceOperationCallback(sc_null),
isExecuting(false),
stateConfVectorPosition(0)
{
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Orthogonal_last_state;
	
	clearInEvents();
}

OrthogonalStatemachine::~OrthogonalStatemachine()
{
}


using namespace orthogonal_events;

SctEvent* OrthogonalStatemachine::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void OrthogonalStatemachine::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case OrthogonalStatemachineEventName::trigger:
		{
			iface_dispatch_event(event);
			break;
		}
		default:
			break;
	}
	delete event;
}

void OrthogonalStatemachine::iface_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case OrthogonalStatemachineEventName::trigger:
		{
			internal_trigger();
			break;
		}
		default:
			break;
	}
}



sc_boolean OrthogonalStatemachine::isActive() const
{
	return stateConfVector[0] != Orthogonal_last_state||stateConfVector[1] != Orthogonal_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean OrthogonalStatemachine::isFinal() const
{
   return false;}

sc_boolean OrthogonalStatemachine::check() {
	if (this->ifaceOperationCallback == sc_null) {
		return false;
	}
	return true;
}


sc_boolean OrthogonalStatemachine::isStateActive(OrthogonalStates state) const
{
	switch (state)
	{
		case Left_State : 
			return (sc_boolean) (stateConfVector[SCVI_LEFT_STATE] == Left_State
			);
		case Right_State : 
			return (sc_boolean) (stateConfVector[SCVI_RIGHT_STATE] == Right_State
			);
		default: return false;
	}
}

/* Functions for event trigger in interface  */
void OrthogonalStatemachine::trigger()
{
	inEventQueue.push_back(new SctEvent__trigger(OrthogonalStatemachineEventName::trigger));
	runCycle();
}
void OrthogonalStatemachine::internal_trigger()
{
	trigger_raised = true;
}
sc_integer OrthogonalStatemachine::getLeft() const
{
	return left;
}

void OrthogonalStatemachine::setLeft(sc_integer value)
{
	this->left = value;
}

sc_integer OrthogonalStatemachine::getRight() const
{
	return right;
}

void OrthogonalStatemachine::setRight(sc_integer value)
{
	this->right = value;
}

void OrthogonalStatemachine::setOperationCallback(OperationCallback* operationCallback)
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions

/* 'default' enter sequence for state State */
void OrthogonalStatemachine::enseq_Left_State_default()
{
	/* 'default' enter sequence for state State */
	stateConfVector[0] = Left_State;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state State */
void OrthogonalStatemachine::enseq_Right_State_default()
{
	/* 'default' enter sequence for state State */
	stateConfVector[1] = Right_State;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for region Left */
void OrthogonalStatemachine::enseq_Left_default()
{
	/* 'default' enter sequence for region Left */
	react_Left__entry_Default();
}

/* 'default' enter sequence for region Right */
void OrthogonalStatemachine::enseq_Right_default()
{
	/* 'default' enter sequence for region Right */
	react_Right__entry_Default();
}

/* Default exit sequence for state State */
void OrthogonalStatemachine::exseq_Left_State()
{
	/* Default exit sequence for state State */
	stateConfVector[0] = Orthogonal_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state State */
void OrthogonalStatemachine::exseq_Right_State()
{
	/* Default exit sequence for state State */
	stateConfVector[1] = Orthogonal_last_state;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for region Left */
void OrthogonalStatemachine::exseq_Left()
{
	/* Default exit sequence for region Left */
	/* Handle exit of all possible states (of Orthogonal.Left) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case Left_State :
		{
			exseq_Left_State();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Right */
void OrthogonalStatemachine::exseq_Right()
{
	/* Default exit sequence for region Right */
	/* Handle exit of all possible states (of Orthogonal.Right) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case Right_State :
		{
			exseq_Right_State();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void OrthogonalStatemachine::react_Left__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_Left_State_default();
}

/* Default react sequence for initial entry  */
void OrthogonalStatemachine::react_Right__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_Right_State_default();
}

sc_integer OrthogonalStatemachine::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer OrthogonalStatemachine::Left_State_react(const sc_integer transitioned_before) {
	/* The reactions of state State. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (((trigger_raised)) && ((ifaceOperationCallback->isLeft())))
		{ 
			exseq_Left_State();
			left++;
			ifaceOperationCallback->label();
			enseq_Left_State_default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc_integer OrthogonalStatemachine::Right_State_react(const sc_integer transitioned_before) {
	/* The reactions of state State. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (((trigger_raised)) && ((ifaceOperationCallback->isRight())))
		{ 
			exseq_Right_State();
			right++;
			ifaceOperationCallback->label();
			enseq_Right_State_default();
			react(0);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void OrthogonalStatemachine::clearInEvents() {
	trigger_raised = false;
}

void OrthogonalStatemachine::microStep() {
	sc_integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case Left_State :
		{
			transitioned = Left_State_react(transitioned);
			break;
		}
		default: break;
	}
	if ((stateConfVectorPosition) < (1))
	{ 
		switch(stateConfVector[ 1 ])
		{
			case Right_State :
			{
				transitioned = Right_State_react(transitioned);
				break;
			}
			default: break;
		}
	} 
}

void OrthogonalStatemachine::runCycle() {
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
	} while (trigger_raised);
	isExecuting = false;
}

void OrthogonalStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Orthogonal */
	enseq_Left_default();
	enseq_Right_default();
	isExecuting = false;
}

void OrthogonalStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Orthogonal */
	exseq_Left();
	exseq_Right();
	isExecuting = false;
}



