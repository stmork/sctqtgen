
#include "AbstractStateMachine.h"
#include <string.h>

/*! \file Implementation of the state machine 'default'
*/

AbstractStateMachine::AbstractStateMachine()
{
	
	
	stateConfVectorPosition = 0;
	
}

AbstractStateMachine::~AbstractStateMachine()
{
}


void AbstractStateMachine::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Default_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
}

void AbstractStateMachine::enter()
{
	/* Default enter sequence for statechart default */
	enseq_main_region_default();
}

void AbstractStateMachine::exit()
{
	/* Default exit sequence for statechart default */
	exseq_main_region();
}

sc_boolean AbstractStateMachine::isActive()
{
	return stateConfVector[0] != Default_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean AbstractStateMachine::isFinal()
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
			react_main_region_State_Off();
			break;
		}
		case main_region_State_On :
		{
			react_main_region_State_On();
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


sc_boolean AbstractStateMachine::isStateActive(DefaultStates state)
{
	switch (state)
	{
		case main_region_State_Off : 
			return (sc_boolean) (stateConfVector[0] == main_region_State_Off
			);
		case main_region_State_On : 
			return (sc_boolean) (stateConfVector[0] == main_region_State_On
			);
		default: return false;
	}
}

AbstractStateMachine::SCI_Gui* AbstractStateMachine::getSCI_Gui()
{
	return &ifaceGui;
}

void AbstractStateMachine::SCI_Gui::raise_clicked()
{
	clicked_raised = true;
}

sc_boolean AbstractStateMachine::SCI_Gui::isRaised_on()
{
	return on_raised;
}

sc_boolean AbstractStateMachine::SCI_Gui::isRaised_off()
{
	return off_raised;
}



// implementations of all internal functions

sc_boolean AbstractStateMachine::check_main_region_State_Off_tr0_tr0()
{
	return ifaceGui.clicked_raised;
}

sc_boolean AbstractStateMachine::check_main_region_State_On_tr0_tr0()
{
	return ifaceGui.clicked_raised;
}

void AbstractStateMachine::effect_main_region_State_Off_tr0()
{
	exseq_main_region_State_Off();
	enseq_main_region_State_On_default();
}

void AbstractStateMachine::effect_main_region_State_On_tr0()
{
	exseq_main_region_State_On();
	enseq_main_region_State_Off_default();
}

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
	stateConfVector[0] = Default_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state State On */
void AbstractStateMachine::exseq_main_region_State_On()
{
	/* Default exit sequence for state State On */
	stateConfVector[0] = Default_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_State_On();
}

/* Default exit sequence for region main region */
void AbstractStateMachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of default.main_region) at position 0... */
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

/* The reactions of state State Off. */
void AbstractStateMachine::react_main_region_State_Off()
{
	/* The reactions of state State Off. */
	if (check_main_region_State_Off_tr0_tr0())
	{ 
		effect_main_region_State_Off_tr0();
	} 
}

/* The reactions of state State On. */
void AbstractStateMachine::react_main_region_State_On()
{
	/* The reactions of state State On. */
	if (check_main_region_State_On_tr0_tr0())
	{ 
		effect_main_region_State_On_tr0();
	} 
}

/* Default react sequence for initial entry  */
void AbstractStateMachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_State_Off_default();
}


