/* Copyright (C) 2022 - Steffen A. Mork */

#include "HistoryStatemachine.h"

/*! \file Implementation of the state machine 'History'
*/




HistoryStatemachine::HistoryStatemachine(QObject *parent)  :
QObject(parent),
proceed_raised(false),
toggle_raised(false),
outside_raised(false),
ifaceOperationCallback(sc_null),
isExecuting(false)
{
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = History_last_state;
	
	for (sc_ushort i = 0; i < maxHistoryStates; ++i)
		historyVector[i] = History_last_state;
	
	clearInEvents();
}

HistoryStatemachine::~HistoryStatemachine()
{
}


using namespace history_events;

SctEvent* HistoryStatemachine::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void HistoryStatemachine::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case HistoryStatemachineEventName::proceed:
		case HistoryStatemachineEventName::toggle:
		case HistoryStatemachineEventName::outside:
		{
			iface_dispatch_event(event);
			break;
		}
		default:
			break;
	}
	delete event;
}

void HistoryStatemachine::iface_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case HistoryStatemachineEventName::proceed:
		{
			internal_proceed();
			break;
		}
		case HistoryStatemachineEventName::toggle:
		{
			internal_toggle();
			break;
		}
		case HistoryStatemachineEventName::outside:
		{
			internal_outside();
			break;
		}
		default:
			break;
	}
}



sc_boolean HistoryStatemachine::isActive() const
{
	return stateConfVector[0] != History_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean HistoryStatemachine::isFinal() const
{
   return false;}

sc_boolean HistoryStatemachine::check() {
	if (this->ifaceOperationCallback == sc_null) {
		return false;
	}
	return true;
}


sc_boolean HistoryStatemachine::isStateActive(HistoryStates state) const
{
	switch (state)
	{
		case main_region_Start : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START] >= main_region_Start
				&& stateConfVector[SCVI_MAIN_REGION_START] <= main_region_Start_main_StateB_Inner_Right_Cyan);
		case main_region_Start_main_StateA : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEA] >= main_region_Start_main_StateA
				&& stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEA] <= main_region_Start_main_StateA_Inner_Left_Green);
		case main_region_Start_main_StateA_Inner_Left_Red : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_RED] == main_region_Start_main_StateA_Inner_Left_Red
			);
		case main_region_Start_main_StateA_Inner_Left_Blue : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_BLUE] == main_region_Start_main_StateA_Inner_Left_Blue
			);
		case main_region_Start_main_StateA_Inner_Left_Green : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEA_INNER_LEFT_GREEN] == main_region_Start_main_StateA_Inner_Left_Green
			);
		case main_region_Start_main_StateB : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEB] >= main_region_Start_main_StateB
				&& stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEB] <= main_region_Start_main_StateB_Inner_Right_Cyan);
		case main_region_Start_main_StateB_Inner_Right_Magenta : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEB_INNER_RIGHT_MAGENTA] == main_region_Start_main_StateB_Inner_Right_Magenta
			);
		case main_region_Start_main_StateB_Inner_Right_Cyan : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_START_MAIN_STATEB_INNER_RIGHT_CYAN] == main_region_Start_main_StateB_Inner_Right_Cyan
			);
		case main_region_Outside : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_OUTSIDE] == main_region_Outside
			);
		default: return false;
	}
}

/* Functions for event proceed in interface  */
void HistoryStatemachine::proceed()
{
	inEventQueue.push_back(new SctEvent__proceed(HistoryStatemachineEventName::proceed));
	runCycle();
}
void HistoryStatemachine::internal_proceed()
{
	proceed_raised = true;
}
/* Functions for event toggle in interface  */
void HistoryStatemachine::toggle()
{
	inEventQueue.push_back(new SctEvent__toggle(HistoryStatemachineEventName::toggle));
	runCycle();
}
void HistoryStatemachine::internal_toggle()
{
	toggle_raised = true;
}
/* Functions for event outside in interface  */
void HistoryStatemachine::outside()
{
	inEventQueue.push_back(new SctEvent__outside(HistoryStatemachineEventName::outside));
	runCycle();
}
void HistoryStatemachine::internal_outside()
{
	outside_raised = true;
}
void HistoryStatemachine::setOperationCallback(OperationCallback* operationCallback)
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions

/* Entry action for state 'Red'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Red()
{
	/* Entry action for state 'Red'. */
	ifaceOperationCallback->label((sc_string) "red");
}

/* Entry action for state 'Blue'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Blue()
{
	/* Entry action for state 'Blue'. */
	ifaceOperationCallback->label((sc_string) "blue");
}

/* Entry action for state 'Green'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Green()
{
	/* Entry action for state 'Green'. */
	ifaceOperationCallback->label((sc_string) "green");
}

/* Entry action for state 'Magenta'. */
void HistoryStatemachine::enact_main_region_Start_main_StateB_Inner_Right_Magenta()
{
	/* Entry action for state 'Magenta'. */
	ifaceOperationCallback->label((sc_string) "magenta");
}

/* Entry action for state 'Cyan'. */
void HistoryStatemachine::enact_main_region_Start_main_StateB_Inner_Right_Cyan()
{
	/* Entry action for state 'Cyan'. */
	ifaceOperationCallback->label((sc_string) "cyan");
}

/* Entry action for state 'Outside'. */
void HistoryStatemachine::enact_main_region_Outside()
{
	/* Entry action for state 'Outside'. */
	ifaceOperationCallback->label((sc_string) "outside");
}

/* 'default' enter sequence for state Start */
void HistoryStatemachine::enseq_main_region_Start_default()
{
	/* 'default' enter sequence for state Start */
	enseq_main_region_Start_main_default();
}

/* 'default' enter sequence for state StateA */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_default()
{
	/* 'default' enter sequence for state StateA */
	enseq_main_region_Start_main_StateA_Inner_Left_default();
	historyVector[0] = stateConfVector[0];
}

/* 'default' enter sequence for state Red */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_Red_default()
{
	/* 'default' enter sequence for state Red */
	enact_main_region_Start_main_StateA_Inner_Left_Red();
	stateConfVector[0] = main_region_Start_main_StateA_Inner_Left_Red;
	historyVector[1] = stateConfVector[0];
}

/* 'default' enter sequence for state Blue */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_Blue_default()
{
	/* 'default' enter sequence for state Blue */
	enact_main_region_Start_main_StateA_Inner_Left_Blue();
	stateConfVector[0] = main_region_Start_main_StateA_Inner_Left_Blue;
	historyVector[1] = stateConfVector[0];
}

/* 'default' enter sequence for state Green */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_Green_default()
{
	/* 'default' enter sequence for state Green */
	enact_main_region_Start_main_StateA_Inner_Left_Green();
	stateConfVector[0] = main_region_Start_main_StateA_Inner_Left_Green;
	historyVector[1] = stateConfVector[0];
}

/* 'default' enter sequence for state StateB */
void HistoryStatemachine::enseq_main_region_Start_main_StateB_default()
{
	/* 'default' enter sequence for state StateB */
	enseq_main_region_Start_main_StateB_Inner_Right_default();
	historyVector[0] = stateConfVector[0];
}

/* 'default' enter sequence for state Magenta */
void HistoryStatemachine::enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default()
{
	/* 'default' enter sequence for state Magenta */
	enact_main_region_Start_main_StateB_Inner_Right_Magenta();
	stateConfVector[0] = main_region_Start_main_StateB_Inner_Right_Magenta;
	historyVector[2] = stateConfVector[0];
}

/* 'default' enter sequence for state Cyan */
void HistoryStatemachine::enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default()
{
	/* 'default' enter sequence for state Cyan */
	enact_main_region_Start_main_StateB_Inner_Right_Cyan();
	stateConfVector[0] = main_region_Start_main_StateB_Inner_Right_Cyan;
	historyVector[2] = stateConfVector[0];
}

/* 'default' enter sequence for state Outside */
void HistoryStatemachine::enseq_main_region_Outside_default()
{
	/* 'default' enter sequence for state Outside */
	enact_main_region_Outside();
	stateConfVector[0] = main_region_Outside;
}

/* 'default' enter sequence for region main region */
void HistoryStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* 'default' enter sequence for region main */
void HistoryStatemachine::enseq_main_region_Start_main_default()
{
	/* 'default' enter sequence for region main */
	react_main_region_Start_main__entry_Default();
}

/* deep enterSequence with history in child main */
void HistoryStatemachine::dhenseq_main_region_Start_main()
{
	/* deep enterSequence with history in child main */
	/* Handle deep history entry of main */
	switch(historyVector[ 0 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			/* enterSequence with history in child StateA for leaf Red */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			/* enterSequence with history in child StateA for leaf Blue */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			/* enterSequence with history in child StateA for leaf Green */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			/* enterSequence with history in child StateB for leaf Magenta */
			dhenseq_main_region_Start_main_StateB_Inner_Right();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			/* enterSequence with history in child StateB for leaf Cyan */
			dhenseq_main_region_Start_main_StateB_Inner_Right();
			break;
		}
		default: break;
	}
}

/* 'default' enter sequence for region Inner Left */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_default()
{
	/* 'default' enter sequence for region Inner Left */
	react_main_region_Start_main_StateA_Inner_Left__entry_Default();
}

/* deep enterSequence with history in child Inner Left */
void HistoryStatemachine::dhenseq_main_region_Start_main_StateA_Inner_Left()
{
	/* deep enterSequence with history in child Inner Left */
	/* Handle deep history entry of Inner Left */
	switch(historyVector[ 1 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			/* enterSequence with history in child Red for leaf Red */
			enseq_main_region_Start_main_StateA_Inner_Left_Red_default();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			/* enterSequence with history in child Blue for leaf Blue */
			enseq_main_region_Start_main_StateA_Inner_Left_Blue_default();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			/* enterSequence with history in child Green for leaf Green */
			enseq_main_region_Start_main_StateA_Inner_Left_Green_default();
			break;
		}
		default: break;
	}
}

/* 'default' enter sequence for region Inner Right */
void HistoryStatemachine::enseq_main_region_Start_main_StateB_Inner_Right_default()
{
	/* 'default' enter sequence for region Inner Right */
	react_main_region_Start_main_StateB_Inner_Right__entry_Default();
}

/* deep enterSequence with history in child Inner Right */
void HistoryStatemachine::dhenseq_main_region_Start_main_StateB_Inner_Right()
{
	/* deep enterSequence with history in child Inner Right */
	/* Handle deep history entry of Inner Right */
	switch(historyVector[ 2 ])
	{
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			/* enterSequence with history in child Magenta for leaf Magenta */
			enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			/* enterSequence with history in child Cyan for leaf Cyan */
			enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for state Start */
void HistoryStatemachine::exseq_main_region_Start()
{
	/* Default exit sequence for state Start */
	exseq_main_region_Start_main();
}

/* Default exit sequence for state StateA */
void HistoryStatemachine::exseq_main_region_Start_main_StateA()
{
	/* Default exit sequence for state StateA */
	exseq_main_region_Start_main_StateA_Inner_Left();
}

/* Default exit sequence for state Red */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left_Red()
{
	/* Default exit sequence for state Red */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for state Blue */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left_Blue()
{
	/* Default exit sequence for state Blue */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for state Green */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left_Green()
{
	/* Default exit sequence for state Green */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for state StateB */
void HistoryStatemachine::exseq_main_region_Start_main_StateB()
{
	/* Default exit sequence for state StateB */
	exseq_main_region_Start_main_StateB_Inner_Right();
}

/* Default exit sequence for state Magenta */
void HistoryStatemachine::exseq_main_region_Start_main_StateB_Inner_Right_Magenta()
{
	/* Default exit sequence for state Magenta */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for state Cyan */
void HistoryStatemachine::exseq_main_region_Start_main_StateB_Inner_Right_Cyan()
{
	/* Default exit sequence for state Cyan */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for state Outside */
void HistoryStatemachine::exseq_main_region_Outside()
{
	/* Default exit sequence for state Outside */
	stateConfVector[0] = History_last_state;
}

/* Default exit sequence for region main region */
void HistoryStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of History.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		case main_region_Outside :
		{
			exseq_main_region_Outside();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region main */
void HistoryStatemachine::exseq_main_region_Start_main()
{
	/* Default exit sequence for region main */
	/* Handle exit of all possible states (of History.main_region.Start.main) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Inner Left */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left()
{
	/* Default exit sequence for region Inner Left */
	/* Handle exit of all possible states (of History.main_region.Start.main.StateA.Inner_Left) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region Inner Right */
void HistoryStatemachine::exseq_main_region_Start_main_StateB_Inner_Right()
{
	/* Default exit sequence for region Inner Right */
	/* Handle exit of all possible states (of History.main_region.Start.main.StateB.Inner_Right) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void HistoryStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Start_default();
}

/* Default react sequence for initial entry  */
void HistoryStatemachine::react_main_region_Start_main_StateA_Inner_Left__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Start_main_StateA_Inner_Left_Red_default();
}

/* Default react sequence for initial entry  */
void HistoryStatemachine::react_main_region_Start_main_StateB_Inner_Right__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default();
}

/* Default react sequence for initial entry  */
void HistoryStatemachine::react_main_region_Start_main__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Start_main_StateA_default();
}

/* Default react sequence for deep history entry Return of the GYRA knights */
void HistoryStatemachine::react_main_region_Start_main_ReturnoftheGYRAknights()
{
	/* Default react sequence for deep history entry Return of the GYRA knights */
	/* Enter the region with deep history */
	if (historyVector[0] != History_last_state)
	{
		dhenseq_main_region_Start_main();
	} else
	{
		enseq_main_region_Start_main_StateA_default();
	} 
}

sc_integer HistoryStatemachine::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer HistoryStatemachine::main_region_Start_react(const sc_integer transitioned_before) {
	/* The reactions of state Start. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (outside_raised)
		{ 
			exseq_main_region_Start();
			enseq_main_region_Outside_default();
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

sc_integer HistoryStatemachine::main_region_Start_main_StateA_react(const sc_integer transitioned_before) {
	/* The reactions of state StateA. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (toggle_raised)
		{ 
			exseq_main_region_Start_main_StateA();
			enseq_main_region_Start_main_StateB_default();
			main_region_Start_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Red_react(const sc_integer transitioned_before) {
	/* The reactions of state Red. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (proceed_raised)
		{ 
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			enseq_main_region_Start_main_StateA_Inner_Left_Green_default();
			main_region_Start_main_StateA_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Blue_react(const sc_integer transitioned_before) {
	/* The reactions of state Blue. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (proceed_raised)
		{ 
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			enseq_main_region_Start_main_StateA_Inner_Left_Red_default();
			main_region_Start_main_StateA_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Green_react(const sc_integer transitioned_before) {
	/* The reactions of state Green. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (proceed_raised)
		{ 
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			enseq_main_region_Start_main_StateA_Inner_Left_Blue_default();
			main_region_Start_main_StateA_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateB_react(const sc_integer transitioned_before) {
	/* The reactions of state StateB. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (toggle_raised)
		{ 
			exseq_main_region_Start_main_StateB();
			enseq_main_region_Start_main_StateA_default();
			main_region_Start_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateB_Inner_Right_Magenta_react(const sc_integer transitioned_before) {
	/* The reactions of state Magenta. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (proceed_raised)
		{ 
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default();
			main_region_Start_main_StateB_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_main_StateB_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Start_main_StateB_Inner_Right_Cyan_react(const sc_integer transitioned_before) {
	/* The reactions of state Cyan. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (proceed_raised)
		{ 
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default();
			main_region_Start_main_StateB_react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = main_region_Start_main_StateB_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer HistoryStatemachine::main_region_Outside_react(const sc_integer transitioned_before) {
	/* The reactions of state Outside. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (outside_raised)
		{ 
			exseq_main_region_Outside();
			react_main_region_Start_main_ReturnoftheGYRAknights();
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

void HistoryStatemachine::clearInEvents() {
	proceed_raised = false;
	toggle_raised = false;
	outside_raised = false;
}

void HistoryStatemachine::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case main_region_Start_main_StateA_Inner_Left_Red :
		{
			main_region_Start_main_StateA_Inner_Left_Red_react(-1);
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Blue :
		{
			main_region_Start_main_StateA_Inner_Left_Blue_react(-1);
			break;
		}
		case main_region_Start_main_StateA_Inner_Left_Green :
		{
			main_region_Start_main_StateA_Inner_Left_Green_react(-1);
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			main_region_Start_main_StateB_Inner_Right_Magenta_react(-1);
			break;
		}
		case main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			main_region_Start_main_StateB_Inner_Right_Cyan_react(-1);
			break;
		}
		case main_region_Outside :
		{
			main_region_Outside_react(-1);
			break;
		}
		default: break;
	}
}

void HistoryStatemachine::runCycle() {
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
	} while (((proceed_raised) || (toggle_raised)) || (outside_raised));
	isExecuting = false;
}

void HistoryStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart History */
	enseq_main_region_default();
	isExecuting = false;
}

void HistoryStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart History */
	exseq_main_region();
	isExecuting = false;
}



