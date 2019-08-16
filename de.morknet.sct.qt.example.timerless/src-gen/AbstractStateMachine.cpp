/* Copyright (C) 2019 - Steffen A. Mork */

#include "AbstractStateMachine.h"

/*! \file Implementation of the state machine 'Timerless'
*/




AbstractStateMachine::AbstractStateMachine()  :
stateConfVectorPosition(0),
ifaceGui()
{
}

AbstractStateMachine::~AbstractStateMachine()
{
}


void AbstractStateMachine::init()
{
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Timerless_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
}

void AbstractStateMachine::enter()
{
	/* Default enter sequence for statechart Timerless */
	enseq_main_region_default();
}

void AbstractStateMachine::exit()
{
	/* Default exit sequence for statechart Timerless */
	exseq_main_region();
}

sc_boolean AbstractStateMachine::isActive() const
{
	return stateConfVector[0] != Timerless_last_state;
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
		case main_region_State_Off :
		{
			main_region_State_Off_react(true);
			break;
		}
		case main_region_State_On :
		{
			main_region_State_On_react(true);
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
	ifaceGui.clicked_raised = false;
}

void AbstractStateMachine::clearOutEvents()
{
	ifaceGui.on_raised = false;
	ifaceGui.off_raised = false;
}


sc_boolean AbstractStateMachine::isStateActive(TimerlessStates state) const
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

AbstractStateMachine::SCI_Gui* AbstractStateMachine::getSCI_Gui()
{
	return &ifaceGui;
}
/* Functions for event clicked in interface SCI_Gui */
void AbstractStateMachine::SCI_Gui::raise_clicked()
{
	clicked_raised = true;
}
/* Functions for event on in interface SCI_Gui */
sc_boolean AbstractStateMachine::SCI_Gui::isRaised_on() const
{
	return on_raised;
}
/* Functions for event off in interface SCI_Gui */
sc_boolean AbstractStateMachine::SCI_Gui::isRaised_off() const
{
	return off_raised;
}

// implementations of all internal functions

/* Entry action for state 'State On'. */
void AbstractStateMachine::enact_main_region_State_On()
{
	/* Entry action for state 'State On'. */
	ifaceGui.on_raised = true;
}

/* Exit action for state 'State On'. */
void AbstractStateMachine::exact_main_region_State_On()
{
	/* Exit action for state 'State On'. */
	ifaceGui.off_raised = true;
}

/* 'default' enter sequence for state State Off */
void AbstractStateMachine::enseq_main_region_State_Off_default()
{
	/* 'default' enter sequence for state State Off */
	stateConfVector[0] = main_region_State_Off;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state State On */
void AbstractStateMachine::enseq_main_region_State_On_default()
{
	/* 'default' enter sequence for state State On */
	enact_main_region_State_On();
	stateConfVector[0] = main_region_State_On;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void AbstractStateMachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state State Off */
void AbstractStateMachine::exseq_main_region_State_Off()
{
	/* Default exit sequence for state State Off */
	stateConfVector[0] = Timerless_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state State On */
void AbstractStateMachine::exseq_main_region_State_On()
{
	/* Default exit sequence for state State On */
	stateConfVector[0] = Timerless_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_State_On();
}

/* Default exit sequence for region main region */
void AbstractStateMachine::exseq_main_region()
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
void AbstractStateMachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_State_Off_default();
}

sc_boolean AbstractStateMachine::react() {
	/* State machine reactions. */
	return false;
}

sc_boolean AbstractStateMachine::main_region_State_Off_react(const sc_boolean try_transition) {
	/* The reactions of state State Off. */
	sc_boolean did_transition = try_transition;
	if (try_transition)
	{ 
		if ((react()) == (false))
		{ 
			if (ifaceGui.clicked_raised)
			{ 
				exseq_main_region_State_Off();
				enseq_main_region_State_On_default();
			}  else
			{
				did_transition = false;
			}
		} 
	} 
	return did_transition;
}

sc_boolean AbstractStateMachine::main_region_State_On_react(const sc_boolean try_transition) {
	/* The reactions of state State On. */
	sc_boolean did_transition = try_transition;
	if (try_transition)
	{ 
		if ((react()) == (false))
		{ 
			if (ifaceGui.clicked_raised)
			{ 
				exseq_main_region_State_On();
				enseq_main_region_State_Off_default();
			}  else
			{
				did_transition = false;
			}
		} 
	} 
	return did_transition;
}



