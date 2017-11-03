/* Copyright (C) 2017 - Steffen A. Mork */

#include "AbstractDelay.h"
#include <string.h>

/*! \file Implementation of the state machine 'DelayedExit'
*/


AbstractDelay::AbstractDelay():
	stateConfVectorPosition(0),
	ifaceGui()
{
}

AbstractDelay::~AbstractDelay()
{
}


void AbstractDelay::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = DelayedExit_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
}

void AbstractDelay::enter()
{
	/* Default enter sequence for statechart DelayedExit */
	enseq_main_region_default();
}

void AbstractDelay::exit()
{
	/* Default exit sequence for statechart DelayedExit */
	exseq_main_region();
}

sc_boolean AbstractDelay::isActive() const
{
	return stateConfVector[0] != DelayedExit_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean AbstractDelay::isFinal() const
{
   return false;}

void AbstractDelay::runCycle()
{
	
	clearOutEvents();
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++)
		{
			
		switch (stateConfVector[stateConfVectorPosition])
		{
		case main_region_StateA :
		{
			react_main_region_StateA();
			break;
		}
		case main_region_Do_Something :
		{
			react_main_region_Do_Something();
			break;
		}
		default:
			break;
		}
	}
	clearInEvents();
}

void AbstractDelay::clearInEvents()
{
	ifaceGui.button1_raised = false;
	ifaceGui.button2_raised = false;
}

void AbstractDelay::clearOutEvents()
{
	ifaceGui.stateA_raised = false;
	ifaceGui.doSomething_raised = false;
}


sc_boolean AbstractDelay::isStateActive(DelayedExitStates state) const
{
	switch (state)
	{
		case main_region_StateA : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_STATEA] == main_region_StateA
			);
		case main_region_Do_Something : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_DO_SOMETHING] == main_region_Do_Something
			);
		default: return false;
	}
}

AbstractDelay::SCI_Gui* AbstractDelay::getSCI_Gui()
{
	return &ifaceGui;
}
/* Functions for event button1 in interface SCI_Gui */
void AbstractDelay::SCI_Gui::raise_button1()
{
	button1_raised = true;
}
/* Functions for event button2 in interface SCI_Gui */
void AbstractDelay::SCI_Gui::raise_button2()
{
	button2_raised = true;
}
/* Functions for event stateA in interface SCI_Gui */
sc_boolean AbstractDelay::SCI_Gui::isRaised_stateA() const
{
	return stateA_raised;
}
/* Functions for event doSomething in interface SCI_Gui */
sc_boolean AbstractDelay::SCI_Gui::isRaised_doSomething() const
{
	return doSomething_raised;
}

// implementations of all internal functions

sc_boolean AbstractDelay::check_main_region_StateA_tr0_tr0()
{
	return ifaceGui.button1_raised || ifaceGui.button2_raised;
}

sc_boolean AbstractDelay::check_main_region_Do_Something_tr0_tr0()
{
	return ifaceGui.button1_raised;
}

sc_boolean AbstractDelay::check_main_region_Do_Something_tr1_tr1()
{
	return ifaceGui.button2_raised;
}

void AbstractDelay::effect_main_region_StateA_tr0()
{
	exseq_main_region_StateA();
	enseq_main_region_Do_Something_default();
}

void AbstractDelay::effect_main_region_Do_Something_tr0()
{
	exseq_main_region_Do_Something();
	enseq_main_region_StateA_default();
}

void AbstractDelay::effect_main_region_Do_Something_tr1()
{
	exseq_main_region_Do_Something();
	enseq_main_region_Do_Something_default();
}

/* Entry action for state 'StateA'. */
void AbstractDelay::enact_main_region_StateA()
{
	/* Entry action for state 'StateA'. */
	ifaceGui.stateA_raised = true;
}

/* Entry action for state 'Do Something'. */
void AbstractDelay::enact_main_region_Do_Something()
{
	/* Entry action for state 'Do Something'. */
	ifaceGui.doSomething_raised = true;
}

/* 'default' enter sequence for state StateA */
void AbstractDelay::enseq_main_region_StateA_default()
{
	/* 'default' enter sequence for state StateA */
	enact_main_region_StateA();
	stateConfVector[0] = main_region_StateA;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Do Something */
void AbstractDelay::enseq_main_region_Do_Something_default()
{
	/* 'default' enter sequence for state Do Something */
	enact_main_region_Do_Something();
	stateConfVector[0] = main_region_Do_Something;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void AbstractDelay::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state StateA */
void AbstractDelay::exseq_main_region_StateA()
{
	/* Default exit sequence for state StateA */
	stateConfVector[0] = DelayedExit_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state Do Something */
void AbstractDelay::exseq_main_region_Do_Something()
{
	/* Default exit sequence for state Do Something */
	stateConfVector[0] = DelayedExit_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void AbstractDelay::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of DelayedExit.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_StateA :
		{
			exseq_main_region_StateA();
			break;
		}
		case main_region_Do_Something :
		{
			exseq_main_region_Do_Something();
			break;
		}
		default: break;
	}
}

/* The reactions of state StateA. */
void AbstractDelay::react_main_region_StateA()
{
	/* The reactions of state StateA. */
	if (check_main_region_StateA_tr0_tr0())
	{ 
		effect_main_region_StateA_tr0();
	} 
}

/* The reactions of state Do Something. */
void AbstractDelay::react_main_region_Do_Something()
{
	/* The reactions of state Do Something. */
	if (check_main_region_Do_Something_tr0_tr0())
	{ 
		effect_main_region_Do_Something_tr0();
	}  else
	{
		if (check_main_region_Do_Something_tr1_tr1())
		{ 
			effect_main_region_Do_Something_tr1();
		} 
	}
}

/* Default react sequence for initial entry  */
void AbstractDelay::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_StateA_default();
}



