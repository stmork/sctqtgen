/* Copyright (C) 2023 - Steffen A. Mork */

#include "CalculatorStatemachine.h"

/*! \file
Implementation of the state machine 'Calculator'
*/




CalculatorStatemachine::CalculatorStatemachine(QObject *parent) noexcept :
	operand(0),
	accu(0),
	timerService(nullptr),
	ifaceGui(nullptr),
	ifaceInternalOperationCallback(nullptr),
	isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc::ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = CalculatorStatemachine::State::NO_STATE;
	
	clearInEvents();
}

CalculatorStatemachine::~CalculatorStatemachine()
{
}

CalculatorStatemachine::Gui::Gui(CalculatorStatemachine* parent_) noexcept :
	parent(parent_)
{
}



std::unique_ptr<CalculatorStatemachine::EventInstance> CalculatorStatemachine::getNextEvent() noexcept
{
	std::unique_ptr<CalculatorStatemachine::EventInstance> nextEvent = 0;

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
	
bool CalculatorStatemachine::dispatchEvent(std::unique_ptr<CalculatorStatemachine::EventInstance> event) noexcept
{
	if(event == nullptr) {
		return false;
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
			//pointer got out of scope
			return false;
	}
	//pointer got out of scope
	return true;
}


void CalculatorStatemachine::gui_Button0() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button0)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button1() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button1)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button2() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button2)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button3() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button3)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button4() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button4)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button5() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button5)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button6() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button6)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button7() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button7)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button8() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button8)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_Button9() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_Button9)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonAdd() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonAdd)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonSub() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonSub)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonMult() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonMult)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonDiv() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonDiv)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonEquals() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonEquals)))
	;
	runCycle();
}


void CalculatorStatemachine::gui_ButtonClear() {
	incomingEventQueue.push_back(std::unique_ptr<CalculatorStatemachine::EventInstance>(new CalculatorStatemachine::EventInstance(CalculatorStatemachine::Event::Gui_ButtonClear)))
	;
	runCycle();
}



bool CalculatorStatemachine::isActive() const noexcept
{
	return stateConfVector[0] != CalculatorStatemachine::State::NO_STATE;
}

bool CalculatorStatemachine::isFinal() const noexcept
{
		return (stateConfVector[0] == CalculatorStatemachine::State::main_region__final_);
}

bool CalculatorStatemachine::check() const noexcept{
	if(timerService == nullptr) {
		return false;
	}
	if (this->ifaceInternalOperationCallback == nullptr) {
		return false;
	}
	return true;
}


void CalculatorStatemachine::setTimerService(std::shared_ptr<sc::timer::TimerServiceInterface> timerService_) noexcept
{
	this->timerService = timerService_;
}

std::shared_ptr<sc::timer::TimerServiceInterface> CalculatorStatemachine::getTimerService() noexcept
{
	return timerService;
}

sc::integer CalculatorStatemachine::getNumberOfParallelTimeEvents() noexcept {
	return parallelTimeEventsCount;
}

void CalculatorStatemachine::raiseTimeEvent(sc::eventid evid)
{
	if (evid < timeEventsCount)
	{
		incomingEventQueue.push_back(std::unique_ptr< EventInstance>(new EventInstance(static_cast<CalculatorStatemachine::Event>(evid + static_cast<sc::integer>(CalculatorStatemachine::Event::_te0_main_region_active_)))));
		runCycle();
	}
}


bool CalculatorStatemachine::isStateActive(State state) const noexcept
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
			/* State is not active*/
			return false;
			break;
		}
	}
}

CalculatorStatemachine::Gui& CalculatorStatemachine::gui() noexcept
{
	return ifaceGui;
}
void CalculatorStatemachine::setInternalOperationCallback(std::shared_ptr<InternalOperationCallback> operationCallback) noexcept
{
	ifaceInternalOperationCallback = operationCallback;
}

// implementations of all internal functions
/* Entry action for state 'active'. */
void CalculatorStatemachine::enact_main_region_active()
{
	/* Entry action for state 'active'. */
	timerService->setTimer(shared_from_this(), 0, (30 * 1000), false);
	accu = 0;
	operand = 0;
}

/* Exit action for state 'active'. */
void CalculatorStatemachine::exact_main_region_active()
{
	/* Exit action for state 'active'. */
	timerService->unsetTimer(shared_from_this(), 0);
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
	/* Handle exit of all possible states (of Calculator.main_region) at position 0... */
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
		default:
			/* do nothing */
			break;
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
				emit gui_ShowAccu(operand);
				enseq_main_region_active_default();
				react(0);
				transitioned_after = 0;
			} 
		}
	} 
	if ((transitioned_after) == (transitioned_before))
	{ 
		/* If no transition was taken then execute local reactions */
		if (ifaceGui.Button0_raised)
		{ 
			ifaceInternalOperationCallback->Digit(0);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button1_raised)
		{ 
			ifaceInternalOperationCallback->Digit(1);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button2_raised)
		{ 
			ifaceInternalOperationCallback->Digit(2);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button3_raised)
		{ 
			ifaceInternalOperationCallback->Digit(3);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button4_raised)
		{ 
			ifaceInternalOperationCallback->Digit(4);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button5_raised)
		{ 
			ifaceInternalOperationCallback->Digit(5);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button6_raised)
		{ 
			ifaceInternalOperationCallback->Digit(6);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button7_raised)
		{ 
			ifaceInternalOperationCallback->Digit(7);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button8_raised)
		{ 
			ifaceInternalOperationCallback->Digit(8);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.Button9_raised)
		{ 
			ifaceInternalOperationCallback->Digit(9);
			emit gui_ShowAccu(accu);
		} 
		if (ifaceGui.ButtonAdd_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			emit gui_ShowAccu(operand);
			ifaceInternalOperationCallback->Add();
			accu = 0;
		} 
		if (ifaceGui.ButtonSub_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			emit gui_ShowAccu(operand);
			ifaceInternalOperationCallback->Sub();
			accu = 0;
		} 
		if (ifaceGui.ButtonMult_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			emit gui_ShowAccu(operand);
			ifaceInternalOperationCallback->Mult();
			accu = 0;
		} 
		if (ifaceGui.ButtonDiv_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			emit gui_ShowAccu(operand);
			ifaceInternalOperationCallback->Div();
			accu = 0;
		} 
		if (ifaceGui.ButtonClear_raised)
		{ 
			ifaceInternalOperationCallback->Clear();
			accu = 0;
			operand = 0;
			emit gui_ShowAccu(accu);
		} 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc::integer CalculatorStatemachine::main_region__final__react(const sc::integer transitioned_before) {
	/* The reactions of state null. */
	return react(transitioned_before);
}

void CalculatorStatemachine::clearInEvents() noexcept {
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
		default:
			/* do nothing */
			break;
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
	} while (dispatchEvent(getNextEvent()));
	isExecuting = false;
}

void CalculatorStatemachine::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Calculator */
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
	/* Default exit sequence for statechart Calculator */
	exseq_main_region();
	isExecuting = false;
}

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void CalculatorStatemachine::triggerWithoutEvent() {
	runCycle();
}

