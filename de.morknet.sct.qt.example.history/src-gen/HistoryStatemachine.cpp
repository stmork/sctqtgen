/* Copyright (C) 2024 - Steffen A. Mork */

#include "HistoryStatemachine.h"

/*! \file
Implementation of the state machine 'History'
*/




HistoryStatemachine::HistoryStatemachine(QObject *parent) noexcept :
	proceed_raised(false),
	toggle_raised(false),
	outside_raised(false),
	ifaceOperationCallback(nullptr),
	isExecuting(false)
{
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = HistoryStatemachine::State::NO_STATE;
	
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxHistoryStates; ++state_vec_pos)
		historyVector[state_vec_pos] = HistoryStatemachine::State::NO_STATE;
	
	clearInEvents();
}

HistoryStatemachine::~HistoryStatemachine()
{
}



std::unique_ptr<HistoryStatemachine::EventInstance> HistoryStatemachine::getNextEvent() noexcept
{
	std::unique_ptr<HistoryStatemachine::EventInstance> nextEvent = 0;

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
	
bool HistoryStatemachine::dispatchEvent(std::unique_ptr<HistoryStatemachine::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
	}
								
	switch(event->eventId)
	{
		case HistoryStatemachine::Event::proceed:
		{
			proceed_raised = true;
			break;
		}
		case HistoryStatemachine::Event::toggle:
		{
			toggle_raised = true;
			break;
		}
		case HistoryStatemachine::Event::outside:
		{
			outside_raised = true;
			break;
		}
		
		
		default:
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}


/*! Slot for the in event 'proceed' that is defined in the default interface scope. */
void HistoryStatemachine::proceed() {
	incomingEventQueue.push_back(std::unique_ptr<HistoryStatemachine::EventInstance>(new HistoryStatemachine::EventInstance(HistoryStatemachine::Event::proceed)))
	;
	runCycle();
}


/*! Slot for the in event 'toggle' that is defined in the default interface scope. */
void HistoryStatemachine::toggle() {
	incomingEventQueue.push_back(std::unique_ptr<HistoryStatemachine::EventInstance>(new HistoryStatemachine::EventInstance(HistoryStatemachine::Event::toggle)))
	;
	runCycle();
}


/*! Slot for the in event 'outside' that is defined in the default interface scope. */
void HistoryStatemachine::outside() {
	incomingEventQueue.push_back(std::unique_ptr<HistoryStatemachine::EventInstance>(new HistoryStatemachine::EventInstance(HistoryStatemachine::Event::outside)))
	;
	runCycle();
}



bool HistoryStatemachine::isActive() const noexcept
{
	return stateConfVector[0] != HistoryStatemachine::State::NO_STATE;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
bool HistoryStatemachine::isFinal() const noexcept
{
	   return false;
}

bool HistoryStatemachine::check() const noexcept{
	if (this->ifaceOperationCallback == nullptr) {
		return false;
	}
	return true;
}


bool HistoryStatemachine::isStateActive(State state) const noexcept
{
	switch (state)
	{
		case HistoryStatemachine::State::main_region_Start :
		{
			return  (stateConfVector[scvi_main_region_Start] >= HistoryStatemachine::State::main_region_Start && stateConfVector[scvi_main_region_Start] <= HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateA] >= HistoryStatemachine::State::main_region_Start_main_StateA && stateConfVector[scvi_main_region_Start_main_StateA] <= HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateA_Inner_Left_Red] == HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateA_Inner_Left_Blue] == HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateA_Inner_Left_Green] == HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateB] >= HistoryStatemachine::State::main_region_Start_main_StateB && stateConfVector[scvi_main_region_Start_main_StateB] <= HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateB_Inner_Right_Magenta] == HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			return  (stateConfVector[scvi_main_region_Start_main_StateB_Inner_Right_Cyan] == HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan);
			break;
		}
		case HistoryStatemachine::State::main_region_Outside :
		{
			return  (stateConfVector[scvi_main_region_Outside] == HistoryStatemachine::State::main_region_Outside);
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

void HistoryStatemachine::setOperationCallback(std::shared_ptr<OperationCallback> operationCallback) noexcept
{
	ifaceOperationCallback = operationCallback;
}

// implementations of all internal functions
/* Entry action for state 'Red'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Red()
{
	/* Entry action for state 'Red'. */
	ifaceOperationCallback->label("red");
}

/* Entry action for state 'Blue'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Blue()
{
	/* Entry action for state 'Blue'. */
	ifaceOperationCallback->label("blue");
}

/* Entry action for state 'Green'. */
void HistoryStatemachine::enact_main_region_Start_main_StateA_Inner_Left_Green()
{
	/* Entry action for state 'Green'. */
	ifaceOperationCallback->label("green");
}

/* Entry action for state 'Magenta'. */
void HistoryStatemachine::enact_main_region_Start_main_StateB_Inner_Right_Magenta()
{
	/* Entry action for state 'Magenta'. */
	ifaceOperationCallback->label("magenta");
}

/* Entry action for state 'Cyan'. */
void HistoryStatemachine::enact_main_region_Start_main_StateB_Inner_Right_Cyan()
{
	/* Entry action for state 'Cyan'. */
	ifaceOperationCallback->label("cyan");
}

/* Entry action for state 'Outside'. */
void HistoryStatemachine::enact_main_region_Outside()
{
	/* Entry action for state 'Outside'. */
	ifaceOperationCallback->label("outside");
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
	stateConfVector[0] = HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red;
	historyVector[1] = stateConfVector[0];
}

/* 'default' enter sequence for state Blue */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_Blue_default()
{
	/* 'default' enter sequence for state Blue */
	enact_main_region_Start_main_StateA_Inner_Left_Blue();
	stateConfVector[0] = HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue;
	historyVector[1] = stateConfVector[0];
}

/* 'default' enter sequence for state Green */
void HistoryStatemachine::enseq_main_region_Start_main_StateA_Inner_Left_Green_default()
{
	/* 'default' enter sequence for state Green */
	enact_main_region_Start_main_StateA_Inner_Left_Green();
	stateConfVector[0] = HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green;
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
	stateConfVector[0] = HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta;
	historyVector[2] = stateConfVector[0];
}

/* 'default' enter sequence for state Cyan */
void HistoryStatemachine::enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default()
{
	/* 'default' enter sequence for state Cyan */
	enact_main_region_Start_main_StateB_Inner_Right_Cyan();
	stateConfVector[0] = HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan;
	historyVector[2] = stateConfVector[0];
}

/* 'default' enter sequence for state Outside */
void HistoryStatemachine::enseq_main_region_Outside_default()
{
	/* 'default' enter sequence for state Outside */
	enact_main_region_Outside();
	stateConfVector[0] = HistoryStatemachine::State::main_region_Outside;
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
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			/* enterSequence with history in child StateA for leaf Red */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			/* enterSequence with history in child StateA for leaf Blue */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			/* enterSequence with history in child StateA for leaf Green */
			dhenseq_main_region_Start_main_StateA_Inner_Left();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			/* enterSequence with history in child StateB for leaf Magenta */
			dhenseq_main_region_Start_main_StateB_Inner_Right();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			/* enterSequence with history in child StateB for leaf Cyan */
			dhenseq_main_region_Start_main_StateB_Inner_Right();
			break;
		}
		default:
			/* do nothing */
			break;
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
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			/* enterSequence with history in child Red for leaf Red */
			enseq_main_region_Start_main_StateA_Inner_Left_Red_default();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			/* enterSequence with history in child Blue for leaf Blue */
			enseq_main_region_Start_main_StateA_Inner_Left_Blue_default();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			/* enterSequence with history in child Green for leaf Green */
			enseq_main_region_Start_main_StateA_Inner_Left_Green_default();
			break;
		}
		default:
			/* do nothing */
			break;
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
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			/* enterSequence with history in child Magenta for leaf Magenta */
			enseq_main_region_Start_main_StateB_Inner_Right_Magenta_default();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			/* enterSequence with history in child Cyan for leaf Cyan */
			enseq_main_region_Start_main_StateB_Inner_Right_Cyan_default();
			break;
		}
		default:
			/* do nothing */
			break;
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
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
}

/* Default exit sequence for state Blue */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left_Blue()
{
	/* Default exit sequence for state Blue */
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
}

/* Default exit sequence for state Green */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left_Green()
{
	/* Default exit sequence for state Green */
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
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
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
}

/* Default exit sequence for state Cyan */
void HistoryStatemachine::exseq_main_region_Start_main_StateB_Inner_Right_Cyan()
{
	/* Default exit sequence for state Cyan */
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
}

/* Default exit sequence for state Outside */
void HistoryStatemachine::exseq_main_region_Outside()
{
	/* Default exit sequence for state Outside */
	stateConfVector[0] = HistoryStatemachine::State::NO_STATE;
}

/* Default exit sequence for region main region */
void HistoryStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of History.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		case HistoryStatemachine::State::main_region_Outside :
		{
			exseq_main_region_Outside();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region main */
void HistoryStatemachine::exseq_main_region_Start_main()
{
	/* Default exit sequence for region main */
	/* Handle exit of all possible states (of History.main_region.Start.main) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region Inner Left */
void HistoryStatemachine::exseq_main_region_Start_main_StateA_Inner_Left()
{
	/* Default exit sequence for region Inner Left */
	/* Handle exit of all possible states (of History.main_region.Start.main.StateA.Inner_Left) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Red();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Blue();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			exseq_main_region_Start_main_StateA_Inner_Left_Green();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region Inner Right */
void HistoryStatemachine::exseq_main_region_Start_main_StateB_Inner_Right()
{
	/* Default exit sequence for region Inner Right */
	/* Handle exit of all possible states (of History.main_region.Start.main.StateB.Inner_Right) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Magenta();
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			exseq_main_region_Start_main_StateB_Inner_Right_Cyan();
			break;
		}
		default:
			/* do nothing */
			break;
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

/* Default react sequence for deep history entry Return of the Qt knights */
void HistoryStatemachine::react_main_region_Start_main_ReturnoftheQtknights()
{
	/* Default react sequence for deep history entry Return of the Qt knights */
	/* Enter the region with deep history */
	if (historyVector[0] != HistoryStatemachine::State::NO_STATE)
	{
		dhenseq_main_region_Start_main();
	} else
	{
		enseq_main_region_Start_main_StateA_default();
	} 
}

sc::integer HistoryStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer HistoryStatemachine::main_region_Start_react(const sc::integer transitioned_before) {
	/* The reactions of state Start. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateA_react(const sc::integer transitioned_before) {
	/* The reactions of state StateA. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Red_react(const sc::integer transitioned_before) {
	/* The reactions of state Red. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Blue_react(const sc::integer transitioned_before) {
	/* The reactions of state Blue. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateA_Inner_Left_Green_react(const sc::integer transitioned_before) {
	/* The reactions of state Green. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_main_StateA_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateB_react(const sc::integer transitioned_before) {
	/* The reactions of state StateB. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateB_Inner_Right_Magenta_react(const sc::integer transitioned_before) {
	/* The reactions of state Magenta. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_main_StateB_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Start_main_StateB_Inner_Right_Cyan_react(const sc::integer transitioned_before) {
	/* The reactions of state Cyan. */
	sc::integer transitioned_after = transitioned_before;
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
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = main_region_Start_main_StateB_react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer HistoryStatemachine::main_region_Outside_react(const sc::integer transitioned_before) {
	/* The reactions of state Outside. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (outside_raised)
		{ 
			exseq_main_region_Outside();
			react_main_region_Start_main_ReturnoftheQtknights();
			react(0);
			transitioned_after = 0;
		} 
	} 
	/* If no transition was taken */
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* then execute local reactions. */
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void HistoryStatemachine::clearInEvents() noexcept {
	proceed_raised = false;
	toggle_raised = false;
	outside_raised = false;
}

void HistoryStatemachine::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Red :
		{
			main_region_Start_main_StateA_Inner_Left_Red_react(-1);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Blue :
		{
			main_region_Start_main_StateA_Inner_Left_Blue_react(-1);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateA_Inner_Left_Green :
		{
			main_region_Start_main_StateA_Inner_Left_Green_react(-1);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Magenta :
		{
			main_region_Start_main_StateB_Inner_Right_Magenta_react(-1);
			break;
		}
		case HistoryStatemachine::State::main_region_Start_main_StateB_Inner_Right_Cyan :
		{
			main_region_Start_main_StateB_Inner_Right_Cyan_react(-1);
			break;
		}
		case HistoryStatemachine::State::main_region_Outside :
		{
			main_region_Outside_react(-1);
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

void HistoryStatemachine::runCycle() {
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

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void HistoryStatemachine::triggerWithoutEvent() {
	runCycle();
}

