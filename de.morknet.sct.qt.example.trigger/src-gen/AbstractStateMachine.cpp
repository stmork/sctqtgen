/* Copyright (C) 2017 - Steffen A. Mork */

#include "AbstractStateMachine.h"
#include <string.h>

/*! \file Implementation of the state machine 'trigger'
*/


AbstractStateMachine::AbstractStateMachine():
	timer(null),
	stateConfVectorPosition(0),
	ifaceGui(),
	ifaceInternalSCI()
{
}

AbstractStateMachine::~AbstractStateMachine()
{
}


void AbstractStateMachine::init()
{
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Trigger_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
	/* Default init sequence for statechart trigger */
	ifaceGui.counter = 0;
}

void AbstractStateMachine::enter()
{
	/* Default enter sequence for statechart trigger */
	enseq_main_region_default();
}

void AbstractStateMachine::exit()
{
	/* Default exit sequence for statechart trigger */
	exseq_main_region();
}

sc_boolean AbstractStateMachine::isActive() const
{
	return stateConfVector[0] != Trigger_last_state||stateConfVector[1] != Trigger_last_state||stateConfVector[2] != Trigger_last_state||stateConfVector[3] != Trigger_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean AbstractStateMachine::isFinal() const
{
   return false;}

void AbstractStateMachine::runCycle()
{
	
	clearOutEvents();
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++)
		{
			
		switch (stateConfVector[stateConfVectorPosition])
		{
		case main_region_Wait :
		{
			react_main_region_Wait();
			break;
		}
		case main_region_Lanes_r1_A :
		{
			react_main_region_Lanes_r1_A();
			break;
		}
		case main_region_Lanes_r1__final_ :
		{
			react_main_region_Lanes_r1__final_();
			break;
		}
		case main_region_Lanes_r2_B :
		{
			react_main_region_Lanes_r2_B();
			break;
		}
		case main_region_Lanes_r2__final_ :
		{
			react_main_region_Lanes_r2__final_();
			break;
		}
		case main_region_Lanes_r3_C :
		{
			react_main_region_Lanes_r3_C();
			break;
		}
		case main_region_Lanes_r3__final_ :
		{
			react_main_region_Lanes_r3__final_();
			break;
		}
		case main_region_Lanes_guard_wait :
		{
			react_main_region_Lanes_guard_wait();
			break;
		}
		default:
			break;
		}
	}
	clearInEvents();
}

void AbstractStateMachine::clearInEvents()
{
	ifaceGui.pressed_raised = false;
	ifaceInternalSCI.trigger_raised = false; 
	timeEvents[0] = false; 
	timeEvents[1] = false; 
	timeEvents[2] = false; 
}

void AbstractStateMachine::clearOutEvents()
{
	ifaceGui.update_raised = false;
	ifaceGui.wait_raised = false;
	ifaceGui.lanes_raised = false;
}


void AbstractStateMachine::setTimer(TimerInterface* timerInterface)
{
	this->timer = timerInterface;
}

TimerInterface* AbstractStateMachine::getTimer()
{
	return timer;
}

void AbstractStateMachine::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		*(sc_boolean*)evid = true;
	}				
}

sc_boolean AbstractStateMachine::isStateActive(TriggerStates state) const
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

AbstractStateMachine::SCI_Gui* AbstractStateMachine::getSCI_Gui()
{
	return &ifaceGui;
}
/* Functions for event pressed in interface SCI_Gui */
void AbstractStateMachine::SCI_Gui::raise_pressed()
{
	pressed_raised = true;
}
/* Functions for event update in interface SCI_Gui */
sc_boolean AbstractStateMachine::SCI_Gui::isRaised_update() const
{
	return update_raised;
}
/* Functions for event wait in interface SCI_Gui */
sc_boolean AbstractStateMachine::SCI_Gui::isRaised_wait() const
{
	return wait_raised;
}
/* Functions for event lanes in interface SCI_Gui */
sc_boolean AbstractStateMachine::SCI_Gui::isRaised_lanes() const
{
	return lanes_raised;
}
sc_integer AbstractStateMachine::SCI_Gui::get_counter() const
{
	return counter;
}

void AbstractStateMachine::SCI_Gui::set_counter(sc_integer value)
{
	counter = value;
}

/* Functions for event trigger in interface InternalSCI */
void AbstractStateMachine::InternalSCI::raise_trigger()
{
	trigger_raised = true;
}
sc_boolean AbstractStateMachine::InternalSCI::isRaised_trigger() const
{
	return trigger_raised;
}

// implementations of all internal functions

sc_boolean AbstractStateMachine::check_main_region_Wait_tr0_tr0()
{
	return ifaceGui.pressed_raised;
}

sc_boolean AbstractStateMachine::check_main_region_Lanes_r1_A_tr0_tr0()
{
	return timeEvents[0];
}

sc_boolean AbstractStateMachine::check_main_region_Lanes_r2_B_tr0_tr0()
{
	return timeEvents[1];
}

sc_boolean AbstractStateMachine::check_main_region_Lanes_r3_C_tr0_tr0()
{
	return timeEvents[2];
}

sc_boolean AbstractStateMachine::check_main_region_Lanes_guard_wait_lr0_lr0()
{
	return true;
}

sc_boolean AbstractStateMachine::check_main_region_Lanes_guard_wait_tr0_tr0()
{
	return (ifaceInternalSCI.trigger_raised) && (ifaceGui.counter == 3);
}

void AbstractStateMachine::effect_main_region_Wait_tr0()
{
	exseq_main_region_Wait();
	enseq_main_region_Lanes_default();
}

void AbstractStateMachine::effect_main_region_Lanes_r1_A_tr0()
{
	exseq_main_region_Lanes_r1_A();
	ifaceGui.counter += 1;
	ifaceInternalSCI.trigger_raised = true;
	enseq_main_region_Lanes_r1__final__default();
}

void AbstractStateMachine::effect_main_region_Lanes_r2_B_tr0()
{
	exseq_main_region_Lanes_r2_B();
	ifaceGui.counter += 1;
	ifaceInternalSCI.trigger_raised = true;
	enseq_main_region_Lanes_r2__final__default();
}

void AbstractStateMachine::effect_main_region_Lanes_r3_C_tr0()
{
	exseq_main_region_Lanes_r3_C();
	ifaceGui.counter += 1;
	ifaceInternalSCI.trigger_raised = true;
	enseq_main_region_Lanes_r3__final__default();
}

void AbstractStateMachine::effect_main_region_Lanes_guard_wait_lr0_lr0()
{
	ifaceGui.update_raised = true;
}

void AbstractStateMachine::effect_main_region_Lanes_guard_wait_tr0()
{
	exseq_main_region_Lanes();
	enseq_main_region_Wait_default();
}

/* Entry action for state 'Wait'. */
void AbstractStateMachine::enact_main_region_Wait()
{
	/* Entry action for state 'Wait'. */
	ifaceGui.wait_raised = true;
	ifaceGui.update_raised = true;
}

/* Entry action for state 'Lanes'. */
void AbstractStateMachine::enact_main_region_Lanes()
{
	/* Entry action for state 'Lanes'. */
	ifaceGui.counter = 0;
	ifaceGui.update_raised = true;
	ifaceGui.lanes_raised = true;
}

/* Entry action for state 'A'. */
void AbstractStateMachine::enact_main_region_Lanes_r1_A()
{
	/* Entry action for state 'A'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[0]), 200, false);
}

/* Entry action for state 'B'. */
void AbstractStateMachine::enact_main_region_Lanes_r2_B()
{
	/* Entry action for state 'B'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[1]), 1 * 1000, false);
}

/* Entry action for state 'C'. */
void AbstractStateMachine::enact_main_region_Lanes_r3_C()
{
	/* Entry action for state 'C'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[2]), 1500, false);
}

/* Exit action for state 'A'. */
void AbstractStateMachine::exact_main_region_Lanes_r1_A()
{
	/* Exit action for state 'A'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* Exit action for state 'B'. */
void AbstractStateMachine::exact_main_region_Lanes_r2_B()
{
	/* Exit action for state 'B'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[1]));
}

/* Exit action for state 'C'. */
void AbstractStateMachine::exact_main_region_Lanes_r3_C()
{
	/* Exit action for state 'C'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[2]));
}

/* 'default' enter sequence for state Wait */
void AbstractStateMachine::enseq_main_region_Wait_default()
{
	/* 'default' enter sequence for state Wait */
	enact_main_region_Wait();
	stateConfVector[0] = main_region_Wait;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Lanes */
void AbstractStateMachine::enseq_main_region_Lanes_default()
{
	/* 'default' enter sequence for state Lanes */
	enact_main_region_Lanes();
	enseq_main_region_Lanes_r1_default();
	enseq_main_region_Lanes_r2_default();
	enseq_main_region_Lanes_r3_default();
	enseq_main_region_Lanes_guard_default();
}

/* 'default' enter sequence for state A */
void AbstractStateMachine::enseq_main_region_Lanes_r1_A_default()
{
	/* 'default' enter sequence for state A */
	enact_main_region_Lanes_r1_A();
	stateConfVector[0] = main_region_Lanes_r1_A;
	stateConfVectorPosition = 0;
}

/* Default enter sequence for state null */
void AbstractStateMachine::enseq_main_region_Lanes_r1__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[0] = main_region_Lanes_r1__final_;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state B */
void AbstractStateMachine::enseq_main_region_Lanes_r2_B_default()
{
	/* 'default' enter sequence for state B */
	enact_main_region_Lanes_r2_B();
	stateConfVector[1] = main_region_Lanes_r2_B;
	stateConfVectorPosition = 1;
}

/* Default enter sequence for state null */
void AbstractStateMachine::enseq_main_region_Lanes_r2__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[1] = main_region_Lanes_r2__final_;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state C */
void AbstractStateMachine::enseq_main_region_Lanes_r3_C_default()
{
	/* 'default' enter sequence for state C */
	enact_main_region_Lanes_r3_C();
	stateConfVector[2] = main_region_Lanes_r3_C;
	stateConfVectorPosition = 2;
}

/* Default enter sequence for state null */
void AbstractStateMachine::enseq_main_region_Lanes_r3__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[2] = main_region_Lanes_r3__final_;
	stateConfVectorPosition = 2;
}

/* 'default' enter sequence for state wait */
void AbstractStateMachine::enseq_main_region_Lanes_guard_wait_default()
{
	/* 'default' enter sequence for state wait */
	stateConfVector[3] = main_region_Lanes_guard_wait;
	stateConfVectorPosition = 3;
}

/* 'default' enter sequence for region main region */
void AbstractStateMachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* 'default' enter sequence for region r1 */
void AbstractStateMachine::enseq_main_region_Lanes_r1_default()
{
	/* 'default' enter sequence for region r1 */
	react_main_region_Lanes_r1__entry_Default();
}

/* 'default' enter sequence for region r2 */
void AbstractStateMachine::enseq_main_region_Lanes_r2_default()
{
	/* 'default' enter sequence for region r2 */
	react_main_region_Lanes_r2__entry_Default();
}

/* 'default' enter sequence for region r3 */
void AbstractStateMachine::enseq_main_region_Lanes_r3_default()
{
	/* 'default' enter sequence for region r3 */
	react_main_region_Lanes_r3__entry_Default();
}

/* 'default' enter sequence for region guard */
void AbstractStateMachine::enseq_main_region_Lanes_guard_default()
{
	/* 'default' enter sequence for region guard */
	react_main_region_Lanes_guard__entry_Default();
}

/* Default exit sequence for state Wait */
void AbstractStateMachine::exseq_main_region_Wait()
{
	/* Default exit sequence for state Wait */
	stateConfVector[0] = Trigger_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Lanes */
void AbstractStateMachine::exseq_main_region_Lanes()
{
	/* Default exit sequence for state Lanes */
	exseq_main_region_Lanes_r1();
	exseq_main_region_Lanes_r2();
	exseq_main_region_Lanes_r3();
	exseq_main_region_Lanes_guard();
}

/* Default exit sequence for state A */
void AbstractStateMachine::exseq_main_region_Lanes_r1_A()
{
	/* Default exit sequence for state A */
	stateConfVector[0] = Trigger_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_Lanes_r1_A();
}

/* Default exit sequence for final state. */
void AbstractStateMachine::exseq_main_region_Lanes_r1__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = Trigger_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state B */
void AbstractStateMachine::exseq_main_region_Lanes_r2_B()
{
	/* Default exit sequence for state B */
	stateConfVector[1] = Trigger_last_state;
	stateConfVectorPosition = 1;
	exact_main_region_Lanes_r2_B();
}

/* Default exit sequence for final state. */
void AbstractStateMachine::exseq_main_region_Lanes_r2__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[1] = Trigger_last_state;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for state C */
void AbstractStateMachine::exseq_main_region_Lanes_r3_C()
{
	/* Default exit sequence for state C */
	stateConfVector[2] = Trigger_last_state;
	stateConfVectorPosition = 2;
	exact_main_region_Lanes_r3_C();
}

/* Default exit sequence for final state. */
void AbstractStateMachine::exseq_main_region_Lanes_r3__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[2] = Trigger_last_state;
	stateConfVectorPosition = 2;
}

/* Default exit sequence for state wait */
void AbstractStateMachine::exseq_main_region_Lanes_guard_wait()
{
	/* Default exit sequence for state wait */
	stateConfVector[3] = Trigger_last_state;
	stateConfVectorPosition = 3;
}

/* Default exit sequence for region main region */
void AbstractStateMachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of trigger.main_region) at position 0... */
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
	/* Handle exit of all possible states (of trigger.main_region) at position 1... */
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
	/* Handle exit of all possible states (of trigger.main_region) at position 2... */
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
	/* Handle exit of all possible states (of trigger.main_region) at position 3... */
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
void AbstractStateMachine::exseq_main_region_Lanes_r1()
{
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of trigger.main_region.Lanes.r1) at position 0... */
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
void AbstractStateMachine::exseq_main_region_Lanes_r2()
{
	/* Default exit sequence for region r2 */
	/* Handle exit of all possible states (of trigger.main_region.Lanes.r2) at position 1... */
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
void AbstractStateMachine::exseq_main_region_Lanes_r3()
{
	/* Default exit sequence for region r3 */
	/* Handle exit of all possible states (of trigger.main_region.Lanes.r3) at position 2... */
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
void AbstractStateMachine::exseq_main_region_Lanes_guard()
{
	/* Default exit sequence for region guard */
	/* Handle exit of all possible states (of trigger.main_region.Lanes.guard) at position 3... */
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

/* The reactions of state Wait. */
void AbstractStateMachine::react_main_region_Wait()
{
	/* The reactions of state Wait. */
	if (check_main_region_Wait_tr0_tr0())
	{ 
		effect_main_region_Wait_tr0();
	} 
}

/* The reactions of state A. */
void AbstractStateMachine::react_main_region_Lanes_r1_A()
{
	/* The reactions of state A. */
	if (check_main_region_Lanes_r1_A_tr0_tr0())
	{ 
		effect_main_region_Lanes_r1_A_tr0();
	} 
}

/* The reactions of state null. */
void AbstractStateMachine::react_main_region_Lanes_r1__final_()
{
}

/* The reactions of state B. */
void AbstractStateMachine::react_main_region_Lanes_r2_B()
{
	/* The reactions of state B. */
	if (check_main_region_Lanes_r2_B_tr0_tr0())
	{ 
		effect_main_region_Lanes_r2_B_tr0();
	} 
}

/* The reactions of state null. */
void AbstractStateMachine::react_main_region_Lanes_r2__final_()
{
}

/* The reactions of state C. */
void AbstractStateMachine::react_main_region_Lanes_r3_C()
{
	/* The reactions of state C. */
	if (check_main_region_Lanes_r3_C_tr0_tr0())
	{ 
		effect_main_region_Lanes_r3_C_tr0();
	} 
}

/* The reactions of state null. */
void AbstractStateMachine::react_main_region_Lanes_r3__final_()
{
}

/* The reactions of state wait. */
void AbstractStateMachine::react_main_region_Lanes_guard_wait()
{
	/* The reactions of state wait. */
	if (check_main_region_Lanes_guard_wait_tr0_tr0())
	{ 
		effect_main_region_Lanes_guard_wait_tr0();
	}  else
	{
		effect_main_region_Lanes_guard_wait_lr0_lr0();
	}
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Wait_default();
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region_Lanes_r1__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r1_A_default();
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region_Lanes_r2__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r2_B_default();
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region_Lanes_r3__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_r3_C_default();
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region_Lanes_guard__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Lanes_guard_wait_default();
}



