/* Copyright (C) 2021 - Steffen A. Mork */

#include "TriggerStatemachine.h"

/*! \file Implementation of the state machine 'Trigger'
*/




TriggerStatemachine::TriggerStatemachine(QObject *parent)  :
QObject(parent),
trigger_raised(false),
timerService(sc_null),
ifaceGui(sc_null),
isExecuting(false),
stateConfVectorPosition(0)
{
	this->ifaceGui.parent = this;
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Trigger_last_state;
	
	clearInEvents();
	clearInternalEvents();
}

TriggerStatemachine::~TriggerStatemachine()
{
}

TriggerStatemachine::Gui::Gui(TriggerStatemachine* parent) :
pressed_raised(false),
counter(0),
parent(parent)
{
}


using namespace trigger_events;

SctEvent* TriggerStatemachine::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!internalEventQueue.empty()) {
		nextEvent = internalEventQueue.front();
		internalEventQueue.pop_front();
	}
	else if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void TriggerStatemachine::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case TriggerStatemachineEventName::Gui_pressed:
		{
			ifaceGui.dispatch_event(event);
			break;
		}
		case TriggerStatemachineEventName::Internal_trigger:
		{
			internal_dispatch_event(event);
			break;
		}
		case TriggerStatemachineEventName::Trigger_main_region_Lanes_r1_A_time_event_0:
		{
			timeEvents[0] = true;
			break;
		}
		case TriggerStatemachineEventName::Trigger_main_region_Lanes_r2_B_time_event_0:
		{
			timeEvents[1] = true;
			break;
		}
		case TriggerStatemachineEventName::Trigger_main_region_Lanes_r3_C_time_event_0:
		{
			timeEvents[2] = true;
			break;
		}
		default:
			break;
	}
	delete event;
}

void TriggerStatemachine::Gui::dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case TriggerStatemachineEventName::Gui_pressed:
		{
			internal_gui_pressed();
			break;
		}
		default:
			break;
	}
}
void TriggerStatemachine::internal_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case TriggerStatemachineEventName::Internal_trigger:
		{
			internal_trigger();
			break;
		}
		default:
			break;
	}
}

TriggerStatemachineEventName TriggerStatemachine::getTimedEventName(sc_eventid evid)
{
	if (evid == (sc_eventid)(&timeEvents[0])) {
		return Trigger_main_region_Lanes_r1_A_time_event_0;
	}
	if (evid == (sc_eventid)(&timeEvents[1])) {
		return Trigger_main_region_Lanes_r2_B_time_event_0;
	}
	if (evid == (sc_eventid)(&timeEvents[2])) {
		return Trigger_main_region_Lanes_r3_C_time_event_0;
	}
	return invalid_event;
}



sc_boolean TriggerStatemachine::isActive() const
{
	return stateConfVector[0] != Trigger_last_state||stateConfVector[1] != Trigger_last_state||stateConfVector[2] != Trigger_last_state||stateConfVector[3] != Trigger_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean TriggerStatemachine::isFinal() const
{
   return false;}

sc_boolean TriggerStatemachine::check() {
	if(timerService == sc_null) {
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

sc_integer TriggerStatemachine::getNumberOfParallelTimeEvents() {
	return parallelTimeEventsCount;
}

void TriggerStatemachine::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		inEventQueue.push_back(new TimedSctEvent(getTimedEventName(evid)));
		runCycle();
	}
}


sc_boolean TriggerStatemachine::isStateActive(TriggerStates state) const
{
	switch (state)
	{
		case main_region_Wait : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_WAIT] == main_region_Wait
			);
		case main_region_Lanes : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES] >= main_region_Lanes
				&& stateConfVector[SCVI_MAIN_REGION_LANES] <= main_region_Lanes_guard_wait);
		case main_region_Lanes_r1_A : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R1_A] == main_region_Lanes_r1_A
			);
		case main_region_Lanes_r1__final_ : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R1__FINAL_] == main_region_Lanes_r1__final_
			);
		case main_region_Lanes_r2_B : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R2_B] == main_region_Lanes_r2_B
			);
		case main_region_Lanes_r2__final_ : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R2__FINAL_] == main_region_Lanes_r2__final_
			);
		case main_region_Lanes_r3_C : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R3_C] == main_region_Lanes_r3_C
			);
		case main_region_Lanes_r3__final_ : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_R3__FINAL_] == main_region_Lanes_r3__final_
			);
		case main_region_Lanes_guard_wait : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_LANES_GUARD_WAIT] == main_region_Lanes_guard_wait
			);
		default: return false;
	}
}

TriggerStatemachine::Gui* TriggerStatemachine::gui()
{
	return &ifaceGui;
}
/* Functions for event pressed in interface Gui */
void TriggerStatemachine::gui_pressed()
{
	inEventQueue.push_back(new SctEvent_Gui_pressed(TriggerStatemachineEventName::Gui_pressed));
	runCycle();
}
void TriggerStatemachine::Gui::internal_gui_pressed()
{
	pressed_raised = true;
}
/* Functions for event update in interface Gui */
/* Functions for event wait in interface Gui */
/* Functions for event lanes in interface Gui */
sc_integer TriggerStatemachine::Gui::getCounter() const
{
	return counter;
}

void TriggerStatemachine::Gui::setCounter(sc_integer value)
{
	this->counter = value;
}

/* Functions for event trigger in interface Internal */
void TriggerStatemachine::trigger()
{
	internalEventQueue.push_back(new SctEvent_Internal_trigger(TriggerStatemachineEventName::Internal_trigger));
	runCycle();
}
void TriggerStatemachine::internal_trigger()
{
	trigger_raised = true;
}
sc_boolean TriggerStatemachine::isRaisedTrigger() const
{
	return trigger_raised;
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
	timerService->setTimer(this, (sc_eventid)(&timeEvents[0]), 200, false);
}

/* Entry action for state 'B'. */
void TriggerStatemachine::enact_main_region_Lanes_r2_B()
{
	/* Entry action for state 'B'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[1]), (1 * 1000), false);
}

/* Entry action for state 'C'. */
void TriggerStatemachine::enact_main_region_Lanes_r3_C()
{
	/* Entry action for state 'C'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[2]), 1500, false);
}

/* Exit action for state 'A'. */
void TriggerStatemachine::exact_main_region_Lanes_r1_A()
{
	/* Exit action for state 'A'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* Exit action for state 'B'. */
void TriggerStatemachine::exact_main_region_Lanes_r2_B()
{
	/* Exit action for state 'B'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[1]));
}

/* Exit action for state 'C'. */
void TriggerStatemachine::exact_main_region_Lanes_r3_C()
{
	/* Exit action for state 'C'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[2]));
}

/* 'default' enter sequence for state Wait */
void TriggerStatemachine::enseq_main_region_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Wait();
	stateConfVector[0] = main_region_Wait;
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
	stateConfVector[0] = main_region_Lanes_r1_A;
	stateConfVectorPosition = 0;
}

/* Default enter sequence for state null */
void TriggerStatemachine::enseq_main_region_Lanes_r1__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[0] = main_region_Lanes_r1__final_;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state B */
void TriggerStatemachine::enseq_main_region_Lanes_r2_B_default()
{
	/* 'default' enter sequence for state B */
	enact_main_region_Lanes_r2_B();
	stateConfVector[1] = main_region_Lanes_r2_B;
	stateConfVectorPosition = 1;
}

/* Default enter sequence for state null */
void TriggerStatemachine::enseq_main_region_Lanes_r2__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[1] = main_region_Lanes_r2__final_;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state C */
void TriggerStatemachine::enseq_main_region_Lanes_r3_C_default()
{
	/* 'default' enter sequence for state C */
	enact_main_region_Lanes_r3_C();
	stateConfVector[2] = main_region_Lanes_r3_C;
	stateConfVectorPosition = 2;
}

/* Default enter sequence for state null */
void TriggerStatemachine::enseq_main_region_Lanes_r3__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[2] = main_region_Lanes_r3__final_;
	stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait */
void TriggerStatemachine::enseq_main_region_Lanes_guard_wait_default()
{
	/* 'default' enter sequence for state wait */
	stateConfVector[3] = main_region_Lanes_guard_wait;
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
	stateConfVector[0] = Trigger_last_state;
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
	stateConfVector[0] = Trigger_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_Lanes_r1_A();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r1__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = Trigger_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state B */
void TriggerStatemachine::exseq_main_region_Lanes_r2_B()
{
	/* Default exit sequence for state B */
	stateConfVector[1] = Trigger_last_state;
	stateConfVectorPosition = 1;
	exact_main_region_Lanes_r2_B();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r2__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[1] = Trigger_last_state;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for state C */
void TriggerStatemachine::exseq_main_region_Lanes_r3_C()
{
	/* Default exit sequence for state C */
	stateConfVector[2] = Trigger_last_state;
	stateConfVectorPosition = 2;
	exact_main_region_Lanes_r3_C();
}

/* Default exit sequence for final state. */
void TriggerStatemachine::exseq_main_region_Lanes_r3__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[2] = Trigger_last_state;
	stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait */
void TriggerStatemachine::exseq_main_region_Lanes_guard_wait()
{
	/* Default exit sequence for state wait */
	stateConfVector[3] = Trigger_last_state;
	stateConfVectorPosition = 3;
}

/* Default exit sequence for region main region */
void TriggerStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Trigger.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Wait :
		{
			exseq_main_region_Wait();
			break;
		}
		case main_region_Lanes_r1_A :
		{
			exseq_main_region_Lanes_r1_A();
			break;
		}
		case main_region_Lanes_r1__final_ :
		{
			exseq_main_region_Lanes_r1__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of Trigger.main_region) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case main_region_Lanes_r2_B :
		{
			exseq_main_region_Lanes_r2_B();
			break;
		}
		case main_region_Lanes_r2__final_ :
		{
			exseq_main_region_Lanes_r2__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of Trigger.main_region) at position 2... */
	switch(stateConfVector[ 2 ])
	{
		case main_region_Lanes_r3_C :
		{
			exseq_main_region_Lanes_r3_C();
			break;
		}
		case main_region_Lanes_r3__final_ :
		{
			exseq_main_region_Lanes_r3__final_();
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of Trigger.main_region) at position 3... */
	switch(stateConfVector[ 3 ])
	{
		case main_region_Lanes_guard_wait :
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
	/* Handle exit of all possible states (of Trigger.main_region.Lanes.r1) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Lanes_r1_A :
		{
			exseq_main_region_Lanes_r1_A();
			break;
		}
		case main_region_Lanes_r1__final_ :
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
	/* Handle exit of all possible states (of Trigger.main_region.Lanes.r2) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case main_region_Lanes_r2_B :
		{
			exseq_main_region_Lanes_r2_B();
			break;
		}
		case main_region_Lanes_r2__final_ :
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
	/* Handle exit of all possible states (of Trigger.main_region.Lanes.r3) at position 2... */
	switch(stateConfVector[ 2 ])
	{
		case main_region_Lanes_r3_C :
		{
			exseq_main_region_Lanes_r3_C();
			break;
		}
		case main_region_Lanes_r3__final_ :
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
	/* Handle exit of all possible states (of Trigger.main_region.Lanes.guard) at position 3... */
	switch(stateConfVector[ 3 ])
	{
		case main_region_Lanes_guard_wait :
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

sc_integer TriggerStatemachine::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer TriggerStatemachine::main_region_Wait_react(const sc_integer transitioned_before) {
	/* The reactions of state Wait. */
	sc_integer transitioned_after = transitioned_before;
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

sc_integer TriggerStatemachine::main_region_Lanes_react(const sc_integer transitioned_before) {
	/* The reactions of state Lanes. */
	sc_integer transitioned_after = transitioned_before;
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

sc_integer TriggerStatemachine::main_region_Lanes_r1_A_react(const sc_integer transitioned_before) {
	/* The reactions of state A. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_main_region_Lanes_r1_A();
			ifaceGui.counter += 1;
			trigger_raised = true;
			;
			enseq_main_region_Lanes_r1__final__default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_r1__final__react(const sc_integer transitioned_before) {
	/* The reactions of state null. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_r2_B_react(const sc_integer transitioned_before) {
	/* The reactions of state B. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (timeEvents[1])
		{ 
			exseq_main_region_Lanes_r2_B();
			ifaceGui.counter += 1;
			trigger_raised = true;
			;
			enseq_main_region_Lanes_r2__final__default();
			transitioned_after = 1;
		} 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_r2__final__react(const sc_integer transitioned_before) {
	/* The reactions of state null. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_r3_C_react(const sc_integer transitioned_before) {
	/* The reactions of state C. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (2))
	{ 
		if (timeEvents[2])
		{ 
			exseq_main_region_Lanes_r3_C();
			ifaceGui.counter += 1;
			trigger_raised = true;
			;
			enseq_main_region_Lanes_r3__final__default();
			transitioned_after = 2;
		} 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_r3__final__react(const sc_integer transitioned_before) {
	/* The reactions of state null. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (2))
	{ 
	} 
	return transitioned_after;
}

sc_integer TriggerStatemachine::main_region_Lanes_guard_wait_react(const sc_integer transitioned_before) {
	/* The reactions of state wait. */
	sc_integer transitioned_after = transitioned_before;
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
	sc_integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case main_region_Wait :
		{
			transitioned = main_region_Wait_react(transitioned);
			break;
		}
		case main_region_Lanes_r1_A :
		{
			transitioned = main_region_Lanes_r1_A_react(transitioned);
			break;
		}
		case main_region_Lanes_r1__final_ :
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
			case main_region_Lanes_r2_B :
			{
				transitioned = main_region_Lanes_r2_B_react(transitioned);
				break;
			}
			case main_region_Lanes_r2__final_ :
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
			case main_region_Lanes_r3_C :
			{
				transitioned = main_region_Lanes_r3_C_react(transitioned);
				break;
			}
			case main_region_Lanes_r3__final_ :
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
			case main_region_Lanes_guard_wait :
			{
				transitioned = main_region_Lanes_guard_wait_react(transitioned);
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
	dispatch_event(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
		clearInternalEvents();
		dispatch_event(getNextEvent());
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
	/* Default enter sequence for statechart Trigger */
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
	/* Default exit sequence for statechart Trigger */
	exseq_main_region();
	isExecuting = false;
}



