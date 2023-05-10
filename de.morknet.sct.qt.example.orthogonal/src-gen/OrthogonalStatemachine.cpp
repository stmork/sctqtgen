/* Copyright (C) 2023 - Steffen A. Mork */

#include "OrthogonalStatemachine.h"

/*! \file
Implementation of the state machine 'Orthogonal'
*/




OrthogonalStatemachine::OrthogonalStatemachine(QObject *parent) noexcept :
	left(0),
	right(0),
	trigger_raised(false),
	ifaceOperationCallback(nullptr),
	isExecuting(false),
	stateConfVectorPosition(0)
{
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = OrthogonalStatemachine::State::NO_STATE;
	
	clearInEvents();
}

OrthogonalStatemachine::~OrthogonalStatemachine()
{
}



std::unique_ptr<OrthogonalStatemachine::EventInstance> OrthogonalStatemachine::getNextEvent() noexcept
{
	std::unique_ptr<OrthogonalStatemachine::EventInstance> nextEvent = 0;

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
	
bool OrthogonalStatemachine::dispatchEvent(std::unique_ptr<OrthogonalStatemachine::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
	}
								
	switch(event->eventId)
	{
		case OrthogonalStatemachine::Event::trigger:
		{
			trigger_raised = true;
			break;
		}
		
		
		default:
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}


void OrthogonalStatemachine::trigger() {
	incomingEventQueue.push_back(std::unique_ptr<OrthogonalStatemachine::EventInstance>(new OrthogonalStatemachine::EventInstance(OrthogonalStatemachine::Event::trigger)))
	;
	runCycle();
}



bool OrthogonalStatemachine::isActive() const noexcept
{
	return stateConfVector[0] != OrthogonalStatemachine::State::NO_STATE||stateConfVector[1] != OrthogonalStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool OrthogonalStatemachine::isFinal() const noexcept
{
	   return false;
}

bool OrthogonalStatemachine::check() const noexcept{
	if (this->ifaceOperationCallback == nullptr) {
		return false;
	}
	return true;
}


bool OrthogonalStatemachine::isStateActive(State state) const noexcept
{
	switch (state)
	{
		case OrthogonalStatemachine::State::Left_State :
		{
			return  (stateConfVector[scvi_Left_State] == OrthogonalStatemachine::State::Left_State);
			break;
		}
		case OrthogonalStatemachine::State::Right_State :
		{
			return  (stateConfVector[scvi_Right_State] == OrthogonalStatemachine::State::Right_State);
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

sc::integer OrthogonalStatemachine::getLeft() const noexcept
{
	return left;
}

void OrthogonalStatemachine::setLeft(sc::integer left_) noexcept
{
	this->left = left_;
}

sc::integer OrthogonalStatemachine::getRight() const noexcept
{
	return right;
}

void OrthogonalStatemachine::setRight(sc::integer right_) noexcept
{
	this->right = right_;
}

void OrthogonalStatemachine::setOperationCallback(std::shared_ptr<OperationCallback> operationCallback) noexcept
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions
/* 'default' enter sequence for state State */
void OrthogonalStatemachine::enseq_Left_State_default()
{
	/* 'default' enter sequence for state State */
	stateConfVector[0] = OrthogonalStatemachine::State::Left_State;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state State */
void OrthogonalStatemachine::enseq_Right_State_default()
{
	/* 'default' enter sequence for state State */
	stateConfVector[1] = OrthogonalStatemachine::State::Right_State;
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
	stateConfVector[0] = OrthogonalStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state State */
void OrthogonalStatemachine::exseq_Right_State()
{
	/* Default exit sequence for state State */
	stateConfVector[1] = OrthogonalStatemachine::State::NO_STATE;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for region Left */
void OrthogonalStatemachine::exseq_Left()
{
	/* Default exit sequence for region Left */
	/* Handle exit of all possible states (of Orthogonal.Left) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case OrthogonalStatemachine::State::Left_State :
		{
			exseq_Left_State();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region Right */
void OrthogonalStatemachine::exseq_Right()
{
	/* Default exit sequence for region Right */
	/* Handle exit of all possible states (of Orthogonal.Right) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case OrthogonalStatemachine::State::Right_State :
		{
			exseq_Right_State();
			break;
		}
		default:
			/* do nothing */
			break;
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

sc::integer OrthogonalStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer OrthogonalStatemachine::Left_State_react(const sc::integer transitioned_before) {
	/* The reactions of state State. */
	sc::integer transitioned_after = transitioned_before;
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

sc::integer OrthogonalStatemachine::Right_State_react(const sc::integer transitioned_before) {
	/* The reactions of state State. */
	sc::integer transitioned_after = transitioned_before;
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
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* If no transition was taken then execute local reactions */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void OrthogonalStatemachine::clearInEvents() noexcept {
	trigger_raised = false;
}

void OrthogonalStatemachine::microStep() {
	sc::integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case OrthogonalStatemachine::State::Left_State :
		{
			transitioned = Left_State_react(transitioned);
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
			case OrthogonalStatemachine::State::Right_State :
			{
				Right_State_react(transitioned);
				break;
			}
			default:
				/* do nothing */
				break;
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
	dispatchEvent(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
	} while (dispatchEvent(getNextEvent()));
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

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void OrthogonalStatemachine::triggerWithoutEvent() {
	runCycle();
}

