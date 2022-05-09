/* Copyright (C) 2022 - Steffen A. Mork */

#include "CalculatorStatemachine.h"

/*! \file
Implementation of the state machine 'CalculatorStatemachine'
*/




CalculatorStatemachine::CalculatorStatemachine(QObject *parent) :
	QObject(parent),
	operand(0),
	accu(0),
	timerService(nullptr),
	ifaceGui(nullptr),
	ifaceInternalOperationCallback(nullptr),
	isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = CalculatorStatemachine::State::NO_STATE;
	
	clearInEvents();
}

CalculatorStatemachine::~CalculatorStatemachine()
{
}

CalculatorStatemachine::Gui::Gui(CalculatorStatemachine* parent) :
	Button0_raised(false),
	Button1_raised(false),
	Button2_raised(false),
	Button3_raised(false),
	Button4_raised(false),
	Button5_raised(false),
	Button6_raised(false),
	Button7_raised(false),
	Button8_raised(false),
	Button9_raised(false),
	ButtonAdd_raised(false),
	ButtonSub_raised(false),
	ButtonMult_raised(false),
	ButtonDiv_raised(false),
	ButtonEquals_raised(false),
	ButtonClear_raised(false),
	ShowAccu_value(0),
	parent(parent)
{
}



CalculatorStatemachine::EventInstance* CalculatorStatemachine::getNextEvent()
{
	CalculatorStatemachine::EventInstance* nextEvent = 0;

	if(!incomingEventQueue.empty()) {
		nextEvent = incomingEventQueue.front();
		incomingEventQueue.pop_front();
	}
	
	return nextEvent;
	
}					


void CalculatorStatemachine::dispatchEvent(CalculatorStatemachine::EventInstance * event)
{
	if(event == nullptr) {
		return;
	}
								
	switch(event->eventId)
	{
		
		case CalculatorStatemachine::Event::Gui_Button0:
		{
			ifaceGui.Button0_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button1:
		{
			ifaceGui.Button1_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button2:
		{
			ifaceGui.Button2_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button3:
		{
			ifaceGui.Button3_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button4:
		{
			ifaceGui.Button4_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button5:
		{
			ifaceGui.Button5_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button6:
		{
			ifaceGui.Button6_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button7:
		{
			ifaceGui.Button7_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button8:
		{
			ifaceGui.Button8_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_Button9:
		{
			ifaceGui.Button9_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonAdd:
		{
			ifaceGui.ButtonAdd_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonSub:
		{
			ifaceGui.ButtonSub_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonMult:
		{
			ifaceGui.ButtonMult_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonDiv:
		{
			ifaceGui.ButtonDiv_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonEquals:
		{
			ifaceGui.ButtonEquals_raised = true;
			break;
		}
		case CalculatorStatemachine::Event::Gui_ButtonClear:
		{
			ifaceGui.ButtonClear_raised = true;
			break;
		}
		
		case CalculatorStatemachine::Event::_te0_main_region_active_:
		{
			timeEvents[static_cast<sc::integer>(event->eventId) - static_cast<sc::integer>(CalculatorStatemachine::Event::_te0_main_region_active_)] = true;
			break;
		}
		default:
			break;
	}
	delete event;
}


void CalculatorStatemachine::gui_Button0() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button0));
	runCycle();
}


void CalculatorStatemachine::gui_Button1() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button1));
	runCycle();
}


void CalculatorStatemachine::gui_Button2() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button2));
	runCycle();
}


void CalculatorStatemachine::gui_Button3() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button3));
	runCycle();
}


void CalculatorStatemachine::gui_Button4() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button4));
	runCycle();
}


void CalculatorStatemachine::gui_Button5() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button5));
	runCycle();
}


void CalculatorStatemachine::gui_Button6() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button6));
	runCycle();
}


void CalculatorStatemachine::gui_Button7() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button7));
	runCycle();
}


void CalculatorStatemachine::gui_Button8() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button8));
	runCycle();
}


void CalculatorStatemachine::gui_Button9() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button9));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonAdd() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonAdd));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonSub() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonSub));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonMult() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonMult));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonDiv() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonDiv));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonEquals() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonEquals));
	runCycle();
}


void CalculatorStatemachine::gui_ButtonClear() {
	incomingEventQueue.push_back(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonClear));
	runCycle();
}


/*! Can be used by the client code to trigger a run to completion step without raising an event. */
void CalculatorStatemachine::triggerWithoutEvent() {
	runCycle();
}



bool CalculatorStatemachine::isActive() const
{
	return stateConfVector[0] != CalculatorStatemachine::State::NO_STATE;
}

bool CalculatorStatemachine::isFinal() const
{
	return (stateConfVector[0] == CalculatorStatemachine::State::main_region__final_);
}

bool CalculatorStatemachine::check() const {
	if(timerService == nullptr) {
		return false;
	}
	if (this->ifaceInternalOperationCallback == nullptr) {
		return false;
	}
	return true;
}


void CalculatorStatemachine::setTimerService(sc::timer::TimerServiceInterface* timerService)
{
	this->timerService = timerService;
}

sc::timer::TimerServiceInterface* CalculatorStatemachine::getTimerService()
{
	return timerService;
}

sc::integer CalculatorStatemachine::getNumberOfParallelTimeEvents() {
	return parallelTimeEventsCount;
}

void CalculatorStatemachine::raiseTimeEvent(sc::eventid evid)
{
	if (evid < timeEventsCount)
	{
		incomingEventQueue.push_back(new EventInstance(static_cast<CalculatorStatemachine::Event>(evid + static_cast<sc::integer>(CalculatorStatemachine::Event::_te0_main_region_active_))));
		runCycle();
	}
}


bool CalculatorStatemachine::isStateActive(State state) const
{
	switch (state)
	{
		case CalculatorStatemachine::State::main_region_active :
		{
			return  (stateConfVector[scvi_main_region_active] == CalculatorStatemachine::State::main_region_active);
			break;
		}
		case CalculatorStatemachine::State::main_region__final_ :
		{
			return  (stateConfVector[scvi_main_region__final_] == CalculatorStatemachine::State::main_region__final_);
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
}

CalculatorStatemachine::Gui* CalculatorStatemachine::gui()
{
	return &ifaceGui;
}
void CalculatorStatemachine::setInternalOperationCallback(InternalOperationCallback* operationCallback)
{
	ifaceInternalOperationCallback = operationCallback;
}

// implementations of all internal functions

/* Entry action for state 'active'. */
void CalculatorStatemachine::enact_main_region_active()
{
	/* Entry action for state 'active'. */
	timerService->setTimer(this, 0, (30 * 1000), false);
	accu = 0;
	operand = 0;
}

/* Exit action for state 'active'. */
void CalculatorStatemachine::exact_main_region_active()
{
	/* Exit action for state 'active'. */
	timerService->unsetTimer(this, 0);
}

/* 'default' enter sequence for state active */
void CalculatorStatemachine::enseq_main_region_active_default()
{
	/* 'default' enter sequence for state active */
	enact_main_region_active();
	stateConfVector[0] = CalculatorStatemachine::State::main_region_active;
}

/* Default enter sequence for final state */
void CalculatorStatemachine::enseq_main_region__final__default()
{
	/* Default enter sequence for final state */
	stateConfVector[0] = CalculatorStatemachine::State::main_region__final_;
}

/* 'default' enter sequence for region main region */
void CalculatorStatemachine::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state active */
void CalculatorStatemachine::exseq_main_region_active()
{
	/* Default exit sequence for state active */
	stateConfVector[0] = CalculatorStatemachine::State::NO_STATE;
	exact_main_region_active();
}

/* Default exit sequence for final state. */
void CalculatorStatemachine::exseq_main_region__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = CalculatorStatemachine::State::NO_STATE;
}

/* Default exit sequence for region main region */
void CalculatorStatemachine::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of CalculatorStatemachine.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case CalculatorStatemachine::State::main_region_active :
		{
			exseq_main_region_active();
			break;
		}
		case CalculatorStatemachine::State::main_region__final_ :
		{
			exseq_main_region__final_();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void CalculatorStatemachine::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_active_default();
}

sc::integer CalculatorStatemachine::react(const sc::integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc::integer CalculatorStatemachine::main_region_active_react(const sc::integer transitioned_before) {
	/* The reactions of state active. */
	sc::integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_main_region_active();
			emit gui_Exit();
			timeEvents[0] = false;
			enseq_main_region__final__default();
			transitioned_after = 0;
		}  else
		{
			if (ifaceGui.ButtonEquals_raised)
			{ 
				exseq_main_region_active();
				ifaceInternalOperationCallback->Equals();
				ifaceGui.ShowAccu_value = operand;
				emit gui_ShowAccu(ifaceGui.ShowAccu_value);
				enseq_main_region_active_default();
				react(0);
				transitioned_after = 0;
			} 
		}
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		if (ifaceGui.Button0_raised)
		{ 
			ifaceInternalOperationCallback->Digit(0);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button1_raised)
		{ 
			ifaceInternalOperationCallback->Digit(1);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button2_raised)
		{ 
			ifaceInternalOperationCallback->Digit(2);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button3_raised)
		{ 
			ifaceInternalOperationCallback->Digit(3);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button4_raised)
		{ 
			ifaceInternalOperationCallback->Digit(4);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button5_raised)
		{ 
			ifaceInternalOperationCallback->Digit(5);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button6_raised)
		{ 
			ifaceInternalOperationCallback->Digit(6);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button7_raised)
		{ 
			ifaceInternalOperationCallback->Digit(7);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button8_raised)
		{ 
			ifaceInternalOperationCallback->Digit(8);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button9_raised)
		{ 
			ifaceInternalOperationCallback->Digit(9);
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.ButtonAdd_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Add();
			accu = 0;
		} 
		if (ifaceGui.ButtonSub_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Sub();
			accu = 0;
		} 
		if (ifaceGui.ButtonMult_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Mult();
			accu = 0;
		} 
		if (ifaceGui.ButtonDiv_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Div();
			accu = 0;
		} 
		if (ifaceGui.ButtonClear_raised)
		{ 
			ifaceInternalOperationCallback->Clear();
			accu = 0;
			operand = 0;
			ifaceGui.ShowAccu_value = accu;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer CalculatorStatemachine::main_region__final__react(const sc::integer transitioned_before) {
	/* The reactions of state null. */
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

void CalculatorStatemachine::clearInEvents() {
	ifaceGui.Button0_raised = false;
	ifaceGui.Button1_raised = false;
	ifaceGui.Button2_raised = false;
	ifaceGui.Button3_raised = false;
	ifaceGui.Button4_raised = false;
	ifaceGui.Button5_raised = false;
	ifaceGui.Button6_raised = false;
	ifaceGui.Button7_raised = false;
	ifaceGui.Button8_raised = false;
	ifaceGui.Button9_raised = false;
	ifaceGui.ButtonAdd_raised = false;
	ifaceGui.ButtonSub_raised = false;
	ifaceGui.ButtonMult_raised = false;
	ifaceGui.ButtonDiv_raised = false;
	ifaceGui.ButtonEquals_raised = false;
	ifaceGui.ButtonClear_raised = false;
	timeEvents[0] = false;
}

void CalculatorStatemachine::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case CalculatorStatemachine::State::main_region_active :
		{
			main_region_active_react(-1);
			break;
		}
		case CalculatorStatemachine::State::main_region__final_ :
		{
			main_region__final__react(-1);
			break;
		}
		default: break;
	}
}

void CalculatorStatemachine::runCycle() {
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
		dispatchEvent(getNextEvent());
	} while (((((((((((((((((ifaceGui.Button0_raised) || (ifaceGui.Button1_raised)) || (ifaceGui.Button2_raised)) || (ifaceGui.Button3_raised)) || (ifaceGui.Button4_raised)) || (ifaceGui.Button5_raised)) || (ifaceGui.Button6_raised)) || (ifaceGui.Button7_raised)) || (ifaceGui.Button8_raised)) || (ifaceGui.Button9_raised)) || (ifaceGui.ButtonAdd_raised)) || (ifaceGui.ButtonSub_raised)) || (ifaceGui.ButtonMult_raised)) || (ifaceGui.ButtonDiv_raised)) || (ifaceGui.ButtonEquals_raised)) || (ifaceGui.ButtonClear_raised)) || (timeEvents[0]));
	isExecuting = false;
}

void CalculatorStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart CalculatorStatemachine */
	enseq_main_region_default();
	isExecuting = false;
}

void CalculatorStatemachine::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart CalculatorStatemachine */
	exseq_main_region();
	isExecuting = false;
}



