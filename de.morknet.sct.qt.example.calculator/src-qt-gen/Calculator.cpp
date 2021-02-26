/* Copyright (C) 2021 - Steffen A. Mork */

#include "Calculator.h"

/*! \file Implementation of the state machine 'Calculator'
*/




Calculator::Calculator(QObject *parent)  :
QObject(parent),
operand(0),
accu(0),
timerService(sc_null),
ifaceGui(sc_null),
ifaceInternalOperationCallback(sc_null),
isExecuting(false)
{
	this->ifaceGui.parent = this;
	for (sc_ushort i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Calculator_last_state;
	
	clearInEvents();
}

Calculator::~Calculator()
{
}

Calculator::Gui::Gui(Calculator* parent) :
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
Exit_raised(false),
ShowAccu_raised(false),
ShowAccu_value(0),
parent(parent)
{
}


using namespace calculator_events;

SctEvent* Calculator::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void Calculator::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case Gui_Button0:
		case Gui_Button1:
		case Gui_Button2:
		case Gui_Button3:
		case Gui_Button4:
		case Gui_Button5:
		case Gui_Button6:
		case Gui_Button7:
		case Gui_Button8:
		case Gui_Button9:
		case Gui_ButtonAdd:
		case Gui_ButtonSub:
		case Gui_ButtonMult:
		case Gui_ButtonDiv:
		case Gui_ButtonEquals:
		case Gui_ButtonClear:
		{
			ifaceGui.dispatch_event(event);
			break;
		}
		case Calculator_main_region_active_time_event_0:
		{
			timeEvents[0] = true;
			break;
		}
		default:
			break;
	}
}

void Calculator::Gui::dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case Gui_Button0:
		{
			internal_raiseButton0();
			break;
		}
		case Gui_Button1:
		{
			internal_raiseButton1();
			break;
		}
		case Gui_Button2:
		{
			internal_raiseButton2();
			break;
		}
		case Gui_Button3:
		{
			internal_raiseButton3();
			break;
		}
		case Gui_Button4:
		{
			internal_raiseButton4();
			break;
		}
		case Gui_Button5:
		{
			internal_raiseButton5();
			break;
		}
		case Gui_Button6:
		{
			internal_raiseButton6();
			break;
		}
		case Gui_Button7:
		{
			internal_raiseButton7();
			break;
		}
		case Gui_Button8:
		{
			internal_raiseButton8();
			break;
		}
		case Gui_Button9:
		{
			internal_raiseButton9();
			break;
		}
		case Gui_ButtonAdd:
		{
			internal_raiseButtonAdd();
			break;
		}
		case Gui_ButtonSub:
		{
			internal_raiseButtonSub();
			break;
		}
		case Gui_ButtonMult:
		{
			internal_raiseButtonMult();
			break;
		}
		case Gui_ButtonDiv:
		{
			internal_raiseButtonDiv();
			break;
		}
		case Gui_ButtonEquals:
		{
			internal_raiseButtonEquals();
			break;
		}
		case Gui_ButtonClear:
		{
			internal_raiseButtonClear();
			break;
		}
		default:
			break;
	}
}
void Calculator::internal_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		default:
			break;
	}
}

CalculatorEventName Calculator::getTimedEventName(sc_eventid evid)
{
	if (evid == (sc_eventid)(&timeEvents[0])) {
		return Calculator_main_region_active_time_event_0;
	}
	return invalid_event;
}



sc_boolean Calculator::isActive() const
{
	return stateConfVector[0] != Calculator_last_state;
}

sc_boolean Calculator::isFinal() const
{
	return (stateConfVector[0] == main_region__final_);
}

sc_boolean Calculator::check() {
	if(timerService == sc_null) {
		return false;
	}
	if (this->ifaceInternalOperationCallback == sc_null) {
		return false;
	}
	return true;
}


void Calculator::setTimerService(sc::timer::TimerServiceInterface* timerService)
{
	this->timerService = timerService;
}

sc::timer::TimerServiceInterface* Calculator::getTimerService()
{
	return timerService;
}

sc_integer Calculator::getNumberOfParallelTimeEvents() {
	return parallelTimeEventsCount;
}

void Calculator::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		inEventQueue.push_back(new TimedSctEvent(getTimedEventName(evid)));
		runCycle();
	}
}


sc_boolean Calculator::isStateActive(CalculatorStates state) const
{
	switch (state)
	{
		case main_region_active : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION_ACTIVE] == main_region_active
			);
		case main_region__final_ : 
			return (sc_boolean) (stateConfVector[SCVI_MAIN_REGION__FINAL_] == main_region__final_
			);
		default: return false;
	}
}

Calculator::Gui* Calculator::gui()
{
	return &ifaceGui;
}
/* Functions for event Button0 in interface Gui */
void Calculator::Gui::raiseButton0()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button0(Gui_Button0));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton0()
{
	Button0_raised = true;
}
/* Functions for event Button1 in interface Gui */
void Calculator::Gui::raiseButton1()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button1(Gui_Button1));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton1()
{
	Button1_raised = true;
}
/* Functions for event Button2 in interface Gui */
void Calculator::Gui::raiseButton2()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button2(Gui_Button2));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton2()
{
	Button2_raised = true;
}
/* Functions for event Button3 in interface Gui */
void Calculator::Gui::raiseButton3()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button3(Gui_Button3));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton3()
{
	Button3_raised = true;
}
/* Functions for event Button4 in interface Gui */
void Calculator::Gui::raiseButton4()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button4(Gui_Button4));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton4()
{
	Button4_raised = true;
}
/* Functions for event Button5 in interface Gui */
void Calculator::Gui::raiseButton5()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button5(Gui_Button5));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton5()
{
	Button5_raised = true;
}
/* Functions for event Button6 in interface Gui */
void Calculator::Gui::raiseButton6()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button6(Gui_Button6));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton6()
{
	Button6_raised = true;
}
/* Functions for event Button7 in interface Gui */
void Calculator::Gui::raiseButton7()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button7(Gui_Button7));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton7()
{
	Button7_raised = true;
}
/* Functions for event Button8 in interface Gui */
void Calculator::Gui::raiseButton8()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button8(Gui_Button8));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton8()
{
	Button8_raised = true;
}
/* Functions for event Button9 in interface Gui */
void Calculator::Gui::raiseButton9()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_Button9(Gui_Button9));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButton9()
{
	Button9_raised = true;
}
/* Functions for event ButtonAdd in interface Gui */
void Calculator::Gui::raiseButtonAdd()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonAdd(Gui_ButtonAdd));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonAdd()
{
	ButtonAdd_raised = true;
}
/* Functions for event ButtonSub in interface Gui */
void Calculator::Gui::raiseButtonSub()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonSub(Gui_ButtonSub));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonSub()
{
	ButtonSub_raised = true;
}
/* Functions for event ButtonMult in interface Gui */
void Calculator::Gui::raiseButtonMult()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonMult(Gui_ButtonMult));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonMult()
{
	ButtonMult_raised = true;
}
/* Functions for event ButtonDiv in interface Gui */
void Calculator::Gui::raiseButtonDiv()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonDiv(Gui_ButtonDiv));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonDiv()
{
	ButtonDiv_raised = true;
}
/* Functions for event ButtonEquals in interface Gui */
void Calculator::Gui::raiseButtonEquals()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonEquals(Gui_ButtonEquals));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonEquals()
{
	ButtonEquals_raised = true;
}
/* Functions for event ButtonClear in interface Gui */
void Calculator::Gui::raiseButtonClear()
{
	parent->inEventQueue.push_back(new SctEvent_Gui_ButtonClear(Gui_ButtonClear));
	parent->runCycle();
}
void Calculator::Gui::internal_raiseButtonClear()
{
	ButtonClear_raised = true;
}
/* Functions for event Exit in interface Gui */
sc::rx::Observable<void>* Calculator::Gui::getExit()
{
	return &(this->Exit_observable);
}
/* Functions for event ShowAccu in interface Gui */
sc::rx::Observable<sc_integer>* Calculator::Gui::getShowAccu()
{
	return &(this->ShowAccu_observable);
}
sc_integer Calculator::getOperand() const
{
	return operand;
}

void Calculator::setOperand(sc_integer value)
{
	this->operand = value;
}

sc_integer Calculator::getAccu() const
{
	return accu;
}

void Calculator::setAccu(sc_integer value)
{
	this->accu = value;
}

void Calculator::setInternalOperationCallback(InternalOperationCallback* operationCallback)
{
	ifaceInternalOperationCallback = operationCallback;
}

// implementations of all internal functions

/* Entry action for state 'active'. */
void Calculator::enact_main_region_active()
{
	/* Entry action for state 'active'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[0]), (30 * 1000), false);
	accu = 0;
	operand = 0;
}

/* Exit action for state 'active'. */
void Calculator::exact_main_region_active()
{
	/* Exit action for state 'active'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* 'default' enter sequence for state active */
void Calculator::enseq_main_region_active_default()
{
	/* 'default' enter sequence for state active */
	enact_main_region_active();
	stateConfVector[0] = main_region_active;
}

/* Default enter sequence for state null */
void Calculator::enseq_main_region__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[0] = main_region__final_;
}

/* 'default' enter sequence for region main region */
void Calculator::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state active */
void Calculator::exseq_main_region_active()
{
	/* Default exit sequence for state active */
	stateConfVector[0] = Calculator_last_state;
	exact_main_region_active();
}

/* Default exit sequence for final state. */
void Calculator::exseq_main_region__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = Calculator_last_state;
}

/* Default exit sequence for region main region */
void Calculator::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Calculator.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_active :
		{
			exseq_main_region_active();
			break;
		}
		case main_region__final_ :
		{
			exseq_main_region__final_();
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
void Calculator::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_active_default();
}

sc_integer Calculator::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer Calculator::main_region_active_react(const sc_integer transitioned_before) {
	/* The reactions of state active. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_main_region_active();
			ifaceGui.Exit_raised = true;
			emit gui_Exit();
			enseq_main_region__final__default();
			transitioned_after = 0;
		}  else
		{
			if (ifaceGui.ButtonEquals_raised)
			{ 
				exseq_main_region_active();
				ifaceInternalOperationCallback->Equals();
				ifaceGui.ShowAccu_value = operand;
				ifaceGui.ShowAccu_raised = true;
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
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button1_raised)
		{ 
			ifaceInternalOperationCallback->Digit(1);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button2_raised)
		{ 
			ifaceInternalOperationCallback->Digit(2);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button3_raised)
		{ 
			ifaceInternalOperationCallback->Digit(3);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button4_raised)
		{ 
			ifaceInternalOperationCallback->Digit(4);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button5_raised)
		{ 
			ifaceInternalOperationCallback->Digit(5);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button6_raised)
		{ 
			ifaceInternalOperationCallback->Digit(6);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button7_raised)
		{ 
			ifaceInternalOperationCallback->Digit(7);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button8_raised)
		{ 
			ifaceInternalOperationCallback->Digit(8);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.Button9_raised)
		{ 
			ifaceInternalOperationCallback->Digit(9);
			ifaceGui.ShowAccu_value = accu;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		if (ifaceGui.ButtonAdd_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Add();
			accu = 0;
		} 
		if (ifaceGui.ButtonSub_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Sub();
			accu = 0;
		} 
		if (ifaceGui.ButtonMult_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
			ifaceInternalOperationCallback->Mult();
			accu = 0;
		} 
		if (ifaceGui.ButtonDiv_raised)
		{ 
			ifaceInternalOperationCallback->Equals();
			ifaceGui.ShowAccu_value = operand;
			ifaceGui.ShowAccu_raised = true;
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
			ifaceGui.ShowAccu_raised = true;
			emit gui_ShowAccu(ifaceGui.ShowAccu_value);
		} 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer Calculator::main_region__final__react(const sc_integer transitioned_before) {
	/* The reactions of state null. */
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

void Calculator::clearInEvents() {
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

void Calculator::microStep() {
	switch(stateConfVector[ 0 ])
	{
		case main_region_active :
		{
			main_region_active_react(-1);
			break;
		}
		case main_region__final_ :
		{
			main_region__final__react(-1);
			break;
		}
		default: break;
	}
}

void Calculator::runCycle() {
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
	} while (((((((((((((((((ifaceGui.Button0_raised) || (ifaceGui.Button1_raised)) || (ifaceGui.Button2_raised)) || (ifaceGui.Button3_raised)) || (ifaceGui.Button4_raised)) || (ifaceGui.Button5_raised)) || (ifaceGui.Button6_raised)) || (ifaceGui.Button7_raised)) || (ifaceGui.Button8_raised)) || (ifaceGui.Button9_raised)) || (ifaceGui.ButtonAdd_raised)) || (ifaceGui.ButtonSub_raised)) || (ifaceGui.ButtonMult_raised)) || (ifaceGui.ButtonDiv_raised)) || (ifaceGui.ButtonEquals_raised)) || (ifaceGui.ButtonClear_raised)) || (timeEvents[0]));
	isExecuting = false;
}

void Calculator::enter() {
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

void Calculator::exit() {
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




/*! Slot for in event gui.Button0 */
void Calculator::gui_Button0(){
	ifaceGui.raise_button0();
}

/*! Slot for in event gui.Button1 */
void Calculator::gui_Button1(){
	ifaceGui.raise_button1();
}

/*! Slot for in event gui.Button2 */
void Calculator::gui_Button2(){
	ifaceGui.raise_button2();
}

/*! Slot for in event gui.Button3 */
void Calculator::gui_Button3(){
	ifaceGui.raise_button3();
}

/*! Slot for in event gui.Button4 */
void Calculator::gui_Button4(){
	ifaceGui.raise_button4();
}

/*! Slot for in event gui.Button5 */
void Calculator::gui_Button5(){
	ifaceGui.raise_button5();
}

/*! Slot for in event gui.Button6 */
void Calculator::gui_Button6(){
	ifaceGui.raise_button6();
}

/*! Slot for in event gui.Button7 */
void Calculator::gui_Button7(){
	ifaceGui.raise_button7();
}

/*! Slot for in event gui.Button8 */
void Calculator::gui_Button8(){
	ifaceGui.raise_button8();
}

/*! Slot for in event gui.Button9 */
void Calculator::gui_Button9(){
	ifaceGui.raise_button9();
}

/*! Slot for in event gui.ButtonAdd */
void Calculator::gui_ButtonAdd(){
	ifaceGui.raise_buttonAdd();
}

/*! Slot for in event gui.ButtonSub */
void Calculator::gui_ButtonSub(){
	ifaceGui.raise_buttonSub();
}

/*! Slot for in event gui.ButtonMult */
void Calculator::gui_ButtonMult(){
	ifaceGui.raise_buttonMult();
}

/*! Slot for in event gui.ButtonDiv */
void Calculator::gui_ButtonDiv(){
	ifaceGui.raise_buttonDiv();
}

/*! Slot for in event gui.ButtonEquals */
void Calculator::gui_ButtonEquals(){
	ifaceGui.raise_buttonEquals();
}

/*! Slot for in event gui.ButtonClear */
void Calculator::gui_ButtonClear(){
	ifaceGui.raise_buttonClear();
}


