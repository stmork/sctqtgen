/* Copyright (C) 2022 - Steffen A. Mork */

#include "TriggerStatemachine.h"

/*! \file
Implementation of the state machine 'TriggerStatemachine'
*/




TriggerStatemachine::TriggerStatemachine(QObject *parent) :
	QObject(parent),
	timerService(nullptr),
	ifaceGui(nullptr),
	isExecuting(false),
	stateConfVectorPosition(0),
	trigger_raised(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = TriggerStatemachine::State::NO_STATE;
	
	clearInEvents();
	clearInternalEvents();
}

TriggerStatemachine::~TriggerStatemachine()
{
}

TriggerStatemachine::Gui::Gui(TriggerStatemachine* parent) :
	counter(0),
	pressed_raised(false),
	parent(parent)
{
}



TriggerStatemachine::EventInstance* TriggerStatemachine::getNextEvent()
{
	TriggerStatemachine::EventInstance* nextEvent = 0;

	if(!internalEventQueue.empty()) {
		nextEvent = internalEventQueue.front();
		internalEventQueue.pop_front();
	}
	else if(!incomingEventQueue.empty()) {
		nextEvent = incomingEventQueue.front();
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


void TriggerStatemachine::dispatchEvent(TriggerStatemachine::EventInstance * event)
{
	if(event == nullptr) {
		return;
	}
								
	switch(event->eventId)
	{
		case TriggerStatemachine::Event::Internal_trigger:
		{
			trigger_raised = true;
			break;
		}
		
		case TriggerStatemachine::Event::Gui_pressed:
		{
			ifaceGui.pressed_raised = true;
			break;
		}
		
		case TriggerStatemachine::Event::_te0_main_region_Lanes_r1_A_:
		case TriggerStatemachine::Event::_te1_main_region_Lanes_r2_B_:
		case TriggerStatemachine::Event::_te2_main_region_Lanes_r3_C_:
		{
			timeEvents[static_cast<sc::integer>(event->eventId) - static_cast<sc::integer>(TriggerStatemachine::Event::_te0_main_region_Lanes_r1_A_)] = true;
			break;
		}
		default:
			break;
	}
	delete event;
}


void TriggerStatemachine::gui_pressed() {
	incomingEventQueue.push_back(new TriggerStatemachine::EventInstance(TriggerStatemachine::Event::Gui_pressed));
	runCycle();
}


/*! Can be used by the client code to trigger a run to completion step without raising an event. */
void TriggerStatemachine::triggerWithoutEvent() {
	runCycle();
}



bool TriggerStatemachine::isActive() const
{
	return stateConfVector[0] != TriggerStatemachine::State::NO_STATE||stateConfVector[1] != TriggerStatemachine::State::NO_STATE||stateConfVector[2] != TriggerStatemachine::State::NO_STATE||stateConfVector[3] != TriggerStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool TriggerStatemachine::isFinal() const
{
   return false;}

bool TriggerStatemachine::check() const {
	if(timerService == nullptr) {
		return false;
	}
	return true;
}


void TriggerStatemachine::setTimerService(sc::timer::TimerServiceInterface* timerService)
{
	this->timerService = timerService;
}

sc::timer::TimerServiceInterface* TriggerStatemachine::getTimerService()
{
	return timerService;
}

sc::integer TriggerStatemachine::getNumberOfParallelTimeEvents() {
	return parallelTimeEventsCount;
}

void TriggerStatemachine::raiseTimeEvent(sc::eventid evid)
{
	if (evid < timeEventsCount)
	{
		incomingEventQueue.push_back(new EventInstance(static_cast<TriggerStatemachine::Event>(evid + static_cast<sc::integer>(TriggerStatemachine::Event::_te0_main_region_Lanes_r1_A_))));
		runCycle();
	}
}


bool TriggerStatemachine::isStateActive(State state) const
{
	switch (state)
	{
		case TriggerStatemachine::State::main_region_Wait :
		{
			return  (stateConfVector[scvi_main_region_Wait] == TriggerStatemachine::State::main_region_Wait);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes :
		{
			return  (stateConfVector[scvi_main_region_Lanes] >= TriggerStatemachine::State::main_region_Lanes && stateConfVector[scvi_main_region_Lanes] <= TriggerStatemachine::State::main_region_Lanes_guard_wait);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1_A :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r1_A] == TriggerStatemachine::State::main_region_Lanes_r1_A);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1__final_ :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r1__final_] == TriggerStatemachine::State::main_region_Lanes_r1__final_);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r2_B :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r2_B] == TriggerStatemachine::State::main_region_Lanes_r2_B);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r2__final_ :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r2__final_] == TriggerStatemachine::State::main_region_Lanes_r2__final_);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r3_C :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r3_C] == TriggerStatemachine::State::main_region_Lanes_r3_C);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r3__final_ :
		{
			return  (stateConfVector[scvi_main_region_Lanes_r3__final_] == TriggerStatemachine::State::main_region_Lanes_r3__final_);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_guard_wait :
		{
			return  (stateConfVector[scvi_main_region_Lanes_guard_wait] == TriggerStatemachine::State::main_region_Lanes_guard_wait);
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
}

TriggerStatemachine::Gui* TriggerStatemachine::gui()
{
	return &ifaceGui;
}
sc::integer TriggerStatemachine::Gui::getCounter() const
{
	return counter;
}

void TriggerStatemachine::Gui::setCounter(sc::integer value)
{
	this->counter = value;
}


// implementations of all internal functions

/* Entry action for state 'Wait'. */
void TriggerStatemachine::enact_main_region_Wait()
{
	/* Entry action for state 'Wait'. */
	emit gui_wait();
	emit gui_update();
}

/* Entry action for state 'Lanes'. */
void TriggerStatemachine::enact_main_region_Lanes()
{
	/* Entry action for state 'Lanes'. */
	ifaceGui.counter = 0;
	emit gui_update();
	emit gui_lanes();
}

/* Entry action for state 'A'. */
void TriggerStatemachine::enact_main_region_Lanes_r1_A()
{
	/* Entry action for state 'A'. */
	timerService->setTimer(this, 0, 200, false);
}

/* Entry action for state 'B'. */
void TriggerStatemachine::enact_main_region_Lanes_r2_B()
{
	/* Entry action for state 'B'. */
	timerService->setTimer(this, 1, (1 * 1000), false);
}

/* Entry action for state 'C'. */
void TriggerStatemachine::enact_main_region_Lanes_r3_C()
{
	/* Entry action for state 'C'. */
	timerService->setTimer(this, 2, 1500, false);
}

/* Exit action for state 'A'. */
void TriggerStatemachine::exact_main_region_Lanes_r1_A()
{
	/* Exit action for state 'A'. */
	timerService->unsetTimer(this, 0);
}

/* Exit action for state 'B'. */
void TriggerStatemachine::exact_main_region_Lanes_r2_B()
{
	/* Exit action for state 'B'. */
	timerService->unsetTimer(this, 1);
}

/* Exit action for state 'C'. */
void TriggerStatemachine::exact_main_region_Lanes_r3_C()
{
	/* Exit action for state 'C'. */
	timerService->unsetTimer(this, 2);
}

/* 'default' enter sequence for state Wait */
void TriggerStatemachine::enseq_main_region_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Wait();
	stateConfVector[0] = TriggerStatemachine::State::main_region_Wait;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Lanes */
void TriggerStatemachine::enseq_main_region_Lanes_default()
{
	/* 'default' enter sequence for state Lanes */
	enact_main_region_Lanes();
	enseq_main_region_Lanes_r1_default();
	enseq_main_region_Lanes_r2_default();
	enseq_main_region_Lanes_r3_default();
	enseq_main_region_Lanes_guard_default();
}

/* 'default' enter sequence for state A */
void TriggerStatemachine::enseq_main_region_Lanes_r1_A_default()
{
	/* 'default' enter sequence for state A */
	enact_main_region_Lanes_r1_A();
	stateConfVector[0] = TriggerStatemachine::State::main_region_Lanes_r1_A;
	stateConfVectorPosition = 0;
}

/* Default enter sequence for final state */
void TriggerStatemachine::enseq_main_region_Lanes_r1__final__default()
{
	/* Default enter sequence for final state */
	stateConfVector[0] = TriggerStatemachine::State::main_region_Lanes_r1__final_;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state B */
void TriggerStatemachine::enseq_main_region_Lanes_r2_B_default()
{
	/* 'default' enter sequence for state B */
	enact_main_region_Lanes_r2_B();
	stateConfVector[1] = TriggerStatemachine::State::main_region_Lanes_r2_B;
	stateConfVectorPosition = 1;
}

/* Default enter sequence for final state */
void TriggerStatemachine::enseq_main_region_Lanes_r2__final__default()
{
	/* Default enter sequence for final state */
	stateConfVector[1] = TriggerStatemachine::State::main_region_Lanes_r2__final_;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state C */
void TriggerStatemachine::enseq_main_region_Lanes_r3_C_default()
{
	/* 'default' enter sequence for state C */
	enact_main_region_Lanes_r3_C();
	stateConfVector[2] = TriggerStatemachine::State::main_region_Lanes_r3_C;
	stateConfVectorPosition = 2;
}

/* Default enter sequence for final state */
void TriggerStatemachine::enseq_main_region_Lanes_r3__final__default()
{
	/* Default enter sequence for final state */
	stateConfVector[2] = TriggerStatemachine::State::main_region_Lanes_r3__final_;
	stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait */
void TriggerStatemachine::enseq_main_region_Lanes_guard_wait_default()
{
	/* 'default' enter sequence for state wait */
	stateConfVector[3] = TriggerStatemachine::State::main_region_Lanes_guard_wait;
	stateConfVectorPosition = 3;
}

/* 'default' enter sequence for region main region */
void TriggerStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* 'default' enter sequence for region r1 */
void TriggerStatemachine::enseq_main_region_Lanes_r1_default()
{
	/* 'default' enter sequence for region r1 */
	react_main_region_Lanes_r1__entry_Default();
}

/* 'default' enter sequence for region r2 */
void TriggerStatemachine::enseq_main_region_Lanes_r2_default()
{
	/* 'default' enter sequence for region r2 */
	react_main_region_Lanes_r2__entry_Default();
}

/* 'default' enter sequence for region r3 */
void TriggerStatemachine::enseq_main_region_Lanes_r3_default()
{
	/* 'default' enter sequence for region r3 */
	react_main_region_Lanes_r3__entry_Default();
}

/* 'default' enter sequence for region guard */
void TriggerStatemachine::enseq_main_region_Lanes_guard_default()
{
	/* 'default' enter sequence for region guard */
	react_main_region_Lanes_guard__entry_Default();
}

/* Default exit sequence for state Wait */
void TriggerStatemachine::exseq_main_region_Wait()
{
	/* Default exit sequence for state Wait */
	stateConfVector[0] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Lanes */
void TriggerStatemachine::exseq_main_region_Lanes()
{
	/* Default exit sequence for state Lanes */
	exseq_main_region_Lanes_r1();
	exseq_main_region_Lanes_r2();
	exseq_main_region_Lanes_r3();
	exseq_main_region_Lanes_guard();
}

/* Default exit sequence for state A */
void TriggerStatemachine::exseq_main_region_Lanes_r1_A()
{
	/* Default exit sequence for state A */
	stateConfVector[0] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
	exact_main_region_Lanes_r1_A();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r1__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state B */
void TriggerStatemachine::exseq_main_region_Lanes_r2_B()
{
	/* Default exit sequence for state B */
	stateConfVector[1] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 1;
	exact_main_region_Lanes_r2_B();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r2__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[1] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for state C */
void TriggerStatemachine::exseq_main_region_Lanes_r3_C()
{
	/* Default exit sequence for state C */
	stateConfVector[2] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 2;
	exact_main_region_Lanes_r3_C();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r3__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[2] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait */
void TriggerStatemachine::exseq_main_region_Lanes_guard_wait()
{
	/* Default exit sequence for state wait */
	stateConfVector[3] = TriggerStatemachine::State::NO_STATE;
	stateConfVectorPosition = 3;
}

/* Default exit sequence for region main region */
void TriggerStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of TriggerStatemachine.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case TriggerStatemachine::State::main_region_Wait :
		{
			exseq_main_region_Wait();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1_A :
		{
			exseq_main_region_Lanes_r1_A();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1__final_ :
		{
			exseq_main_region_Lanes_r1__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of TriggerStatemachine.main_region) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_r2_B :
		{
			exseq_main_region_Lanes_r2_B();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r2__final_ :
		{
			exseq_main_region_Lanes_r2__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of TriggerStatemachine.main_region) at position 2... */
	switch(stateConfVector[ 2 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_r3_C :
		{
			exseq_main_region_Lanes_r3_C();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r3__final_ :
		{
			exseq_main_region_Lanes_r3__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of TriggerStatemachine.main_region) at position 3... */
	switch(stateConfVector[ 3 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_guard_wait :
		{
			exseq_main_region_Lanes_guard_wait();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
void TriggerStatemachine::exseq_main_region_Lanes_r1()
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of TriggerStatemachine.main_region.Lanes.r1) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_r1_A :
		{
			exseq_main_region_Lanes_r1_A();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1__final_ :
		{
			exseq_main_region_Lanes_r1__final_();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r2 */
void TriggerStatemachine::exseq_main_region_Lanes_r2()
{
	/* Default exit sequence for region r2 */
	/* Handle exit of all possible states (of TriggerStatemachine.main_region.Lanes.r2) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_r2_B :
		{
			exseq_main_region_Lanes_r2_B();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r2__final_ :
		{
			exseq_main_region_Lanes_r2__final_();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r3 */
void TriggerStatemachine::exseq_main_region_Lanes_r3()
{
	/* Default exit sequence for region r3 */
	/* Handle exit of all possible states (of TriggerStatemachine.main_region.Lanes.r3) at position 2... */
	switch(stateConfVector[ 2 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_r3_C :
		{
			exseq_main_region_Lanes_r3_C();
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r3__final_ :
		{
			exseq_main_region_Lanes_r3__final_();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region guard */
void TriggerStatemachine::exseq_main_region_Lanes_guard()
{
	/* Default exit sequence for region guard */
	/* Handle exit of all possible states (of TriggerStatemachine.main_region.Lanes.guard) at position 3... */
	switch(stateConfVector[ 3 ])
	{
		case TriggerStatemachine::State::main_region_Lanes_guard_wait :
		{
			exseq_main_region_Lanes_guard_wait();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void TriggerStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Wait_default();
}

/* Default react sequence for initial entry  */
void TriggerStatemachine::react_main_region_Lanes_r1__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r1_A_default();
}

/* Default react sequence for initial entry  */
void TriggerStatemachine::react_main_region_Lanes_r2__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r2_B_default();
}

/* Default react sequence for initial entry  */
void TriggerStatemachine::react_main_region_Lanes_r3__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r3_C_default();
}

/* Default react sequence for initial entry  */
void TriggerStatemachine::react_main_region_Lanes_guard__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_guard_wait_default();
}

sc::integer TriggerStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer TriggerStatemachine::main_region_Wait_react(const sc::integer transitioned_before) {
	/* The reactions of state Wait. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (ifaceGui.pressed_raised)
		{ 
			exseq_main_region_Wait();
			enseq_main_region_Lanes_default();
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

sc::integer TriggerStatemachine::main_region_Lanes_react(const sc::integer transitioned_before) {
	/* The reactions of state Lanes. */
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

sc::integer TriggerStatemachine::main_region_Lanes_r1_A_react(const sc::integer transitioned_before) {
	/* The reactions of state A. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_main_region_Lanes_r1_A();
			ifaceGui.counter += 1;
			internalEventQueue.push_back(new TriggerStatemachine::EventInstance(TriggerStatemachine::Event::Internal_trigger));
			timeEvents[0] = false;
			enseq_main_region_Lanes_r1__final__default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_r1__final__react(const sc::integer transitioned_before) {
	/* The reactions of state null. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_r2_B_react(const sc::integer transitioned_before) {
	/* The reactions of state B. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (timeEvents[1])
		{ 
			exseq_main_region_Lanes_r2_B();
			ifaceGui.counter += 1;
			internalEventQueue.push_back(new TriggerStatemachine::EventInstance(TriggerStatemachine::Event::Internal_trigger));
			timeEvents[1] = false;
			enseq_main_region_Lanes_r2__final__default();
			transitioned_after = 1;
		} 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_r2__final__react(const sc::integer transitioned_before) {
	/* The reactions of state null. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_r3_C_react(const sc::integer transitioned_before) {
	/* The reactions of state C. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (2))
	{ 
		if (timeEvents[2])
		{ 
			exseq_main_region_Lanes_r3_C();
			ifaceGui.counter += 1;
			internalEventQueue.push_back(new TriggerStatemachine::EventInstance(TriggerStatemachine::Event::Internal_trigger));
			timeEvents[2] = false;
			enseq_main_region_Lanes_r3__final__default();
			transitioned_after = 2;
		} 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_r3__final__react(const sc::integer transitioned_before) {
	/* The reactions of state null. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (2))
	{ 
	} 
	return transitioned_after;
}

sc::integer TriggerStatemachine::main_region_Lanes_guard_wait_react(const sc::integer transitioned_before) {
	/* The reactions of state wait. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (3))
	{ 
		if (((trigger_raised)) && (((ifaceGui.counter) == (3))))
		{ 
			exseq_main_region_Lanes();
			enseq_main_region_Wait_default();
			react(0);
			transitioned_after = 3;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		emit gui_update();
		transitioned_after = main_region_Lanes_react(transitioned_before);
	} 
	return transitioned_after;
}

void TriggerStatemachine::clearInEvents() {
	ifaceGui.pressed_raised = false;
	timeEvents[0] = false;
	timeEvents[1] = false;
	timeEvents[2] = false;
}

void TriggerStatemachine::clearInternalEvents() {
	trigger_raised = false;
}

void TriggerStatemachine::microStep() {
	sc::integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case TriggerStatemachine::State::main_region_Wait :
		{
			transitioned = main_region_Wait_react(transitioned);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1_A :
		{
			transitioned = main_region_Lanes_r1_A_react(transitioned);
			break;
		}
		case TriggerStatemachine::State::main_region_Lanes_r1__final_ :
		{
			transitioned = main_region_Lanes_r1__final__react(transitioned);
			break;
		}
		default: break;
	}
	if ((stateConfVectorPosition) < (1))
	{ 
		switch(stateConfVector[ 1 ])
		{
			case TriggerStatemachine::State::main_region_Lanes_r2_B :
			{
				transitioned = main_region_Lanes_r2_B_react(transitioned);
				break;
			}
			case TriggerStatemachine::State::main_region_Lanes_r2__final_ :
			{
				transitioned = main_region_Lanes_r2__final__react(transitioned);
				break;
			}
			default: break;
		}
	} 
	if ((stateConfVectorPosition) < (2))
	{ 
		switch(stateConfVector[ 2 ])
		{
			case TriggerStatemachine::State::main_region_Lanes_r3_C :
			{
				transitioned = main_region_Lanes_r3_C_react(transitioned);
				break;
			}
			case TriggerStatemachine::State::main_region_Lanes_r3__final_ :
			{
				transitioned = main_region_Lanes_r3__final__react(transitioned);
				break;
			}
			default: break;
		}
	} 
	if ((stateConfVectorPosition) < (3))
	{ 
		switch(stateConfVector[ 3 ])
		{
			case TriggerStatemachine::State::main_region_Lanes_guard_wait :
			{
				main_region_Lanes_guard_wait_react(transitioned);
				break;
			}
			default: break;
		}
	} 
}

void TriggerStatemachine::runCycle() {
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
		clearInternalEvents();
		dispatchEvent(getNextEvent());
	} while (((((ifaceGui.pressed_raised) || (trigger_raised)) || (timeEvents[0])) || (timeEvents[1])) || (timeEvents[2]));
	isExecuting = false;
}

void TriggerStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart TriggerStatemachine */
	enseq_main_region_default();
	isExecuting = false;
}

void TriggerStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart TriggerStatemachine */
	exseq_main_region();
	isExecuting = false;
}



