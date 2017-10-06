/* Copyright (C) 2017 - Steffen A. Mork */

#include "AbstractCalculator.h"
#include <string.h>

/*! \file Implementation of the state machine 'calculator'
*/


AbstractCalculator::AbstractCalculator():
	timer(null),
	stateConfVectorPosition(0),
	ifaceGui(),
	ifaceInternalSCI(),
	ifaceInternalSCI_OCB(null)
{
}

AbstractCalculator::~AbstractCalculator()
{
}


void AbstractCalculator::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Calculator_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
	/* Default init sequence for statechart calculator */
	ifaceInternalSCI.operand = 0;
	ifaceInternalSCI.accu = 0;
}

void AbstractCalculator::enter()
{
	/* Default enter sequence for statechart calculator */
	enseq_main_region_default();
}

void AbstractCalculator::exit()
{
	/* Default exit sequence for statechart calculator */
	exseq_main_region();
}

sc_boolean AbstractCalculator::isActive() const
{
	return stateConfVector[0] != Calculator_last_state;
}

sc_boolean AbstractCalculator::isFinal() const
{
	return (stateConfVector[0] == main_region__final_);
}

void AbstractCalculator::runCycle()
{
	
	clearOutEvents();
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++)
		{
			
		switch (stateConfVector[stateConfVectorPosition])
		{
		case main_region_active :
		{
			react_main_region_active();
			break;
		}
		case main_region__final_ :
		{
			react_main_region__final_();
			break;
		}
		default:
			break;
		}
	}
	clearInEvents();
}

void AbstractCalculator::clearInEvents()
{
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

void AbstractCalculator::clearOutEvents()
{
	ifaceGui.Exit_raised = false;
	ifaceGui.ShowAccu_raised = false;
}


void AbstractCalculator::setTimer(TimerInterface* timerInterface)
{
	this->timer = timerInterface;
}

TimerInterface* AbstractCalculator::getTimer()
{
	return timer;
}

void AbstractCalculator::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		*(sc_boolean*)evid = true;
	}				
}

sc_boolean AbstractCalculator::isStateActive(CalculatorStates state) const
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

AbstractCalculator::SCI_Gui* AbstractCalculator::getSCI_Gui()
{
	return &ifaceGui;
}
/* Functions for event Button0 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button0()
{
	Button0_raised = true;
}
/* Functions for event Button1 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button1()
{
	Button1_raised = true;
}
/* Functions for event Button2 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button2()
{
	Button2_raised = true;
}
/* Functions for event Button3 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button3()
{
	Button3_raised = true;
}
/* Functions for event Button4 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button4()
{
	Button4_raised = true;
}
/* Functions for event Button5 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button5()
{
	Button5_raised = true;
}
/* Functions for event Button6 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button6()
{
	Button6_raised = true;
}
/* Functions for event Button7 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button7()
{
	Button7_raised = true;
}
/* Functions for event Button8 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button8()
{
	Button8_raised = true;
}
/* Functions for event Button9 in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_button9()
{
	Button9_raised = true;
}
/* Functions for event ButtonAdd in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonAdd()
{
	ButtonAdd_raised = true;
}
/* Functions for event ButtonSub in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonSub()
{
	ButtonSub_raised = true;
}
/* Functions for event ButtonMult in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonMult()
{
	ButtonMult_raised = true;
}
/* Functions for event ButtonDiv in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonDiv()
{
	ButtonDiv_raised = true;
}
/* Functions for event ButtonEquals in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonEquals()
{
	ButtonEquals_raised = true;
}
/* Functions for event ButtonClear in interface SCI_Gui */
void AbstractCalculator::SCI_Gui::raise_buttonClear()
{
	ButtonClear_raised = true;
}
/* Functions for event Exit in interface SCI_Gui */
sc_boolean AbstractCalculator::SCI_Gui::isRaised_exit() const
{
	return Exit_raised;
}
/* Functions for event ShowAccu in interface SCI_Gui */
sc_boolean AbstractCalculator::SCI_Gui::isRaised_showAccu() const
{
	return ShowAccu_raised;
}
sc_integer AbstractCalculator::SCI_Gui::get_showAccu_value() const
{
	return ShowAccu_value;
}
sc_integer AbstractCalculator::InternalSCI::get_operand() const
{
	return operand;
}

void AbstractCalculator::InternalSCI::set_operand(sc_integer value)
{
	operand = value;
}

sc_integer AbstractCalculator::InternalSCI::get_accu() const
{
	return accu;
}

void AbstractCalculator::InternalSCI::set_accu(sc_integer value)
{
	accu = value;
}

void AbstractCalculator::setInternalSCI_OCB(InternalSCI_OCB* operationCallback)
{
	ifaceInternalSCI_OCB = operationCallback;
}

// implementations of all internal functions

sc_boolean AbstractCalculator::check_main_region_active_lr1_lr1()
{
	return ifaceGui.Button0_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr2_lr2()
{
	return ifaceGui.Button1_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr3_lr3()
{
	return ifaceGui.Button2_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr4_lr4()
{
	return ifaceGui.Button3_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr5_lr5()
{
	return ifaceGui.Button4_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr6_lr6()
{
	return ifaceGui.Button5_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr7_lr7()
{
	return ifaceGui.Button6_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr8_lr8()
{
	return ifaceGui.Button7_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr9_lr9()
{
	return ifaceGui.Button8_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr10_lr10()
{
	return ifaceGui.Button9_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr11_lr11()
{
	return ifaceGui.ButtonAdd_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr12_lr12()
{
	return ifaceGui.ButtonSub_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr13_lr13()
{
	return ifaceGui.ButtonMult_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr14_lr14()
{
	return ifaceGui.ButtonDiv_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_lr15_lr15()
{
	return ifaceGui.ButtonClear_raised;
}

sc_boolean AbstractCalculator::check_main_region_active_tr0_tr0()
{
	return timeEvents[0];
}

sc_boolean AbstractCalculator::check_main_region_active_tr1_tr1()
{
	return ifaceGui.ButtonEquals_raised;
}

void AbstractCalculator::effect_main_region_active_lr1_lr1()
{
	ifaceInternalSCI_OCB->Digit(0);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr2_lr2()
{
	ifaceInternalSCI_OCB->Digit(1);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr3_lr3()
{
	ifaceInternalSCI_OCB->Digit(2);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr4_lr4()
{
	ifaceInternalSCI_OCB->Digit(3);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr5_lr5()
{
	ifaceInternalSCI_OCB->Digit(4);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr6_lr6()
{
	ifaceInternalSCI_OCB->Digit(5);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr7_lr7()
{
	ifaceInternalSCI_OCB->Digit(6);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr8_lr8()
{
	ifaceInternalSCI_OCB->Digit(7);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr9_lr9()
{
	ifaceInternalSCI_OCB->Digit(8);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr10_lr10()
{
	ifaceInternalSCI_OCB->Digit(9);
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_lr11_lr11()
{
	ifaceInternalSCI_OCB->Equals();
	ifaceGui.ShowAccu_value = ifaceInternalSCI.operand;
	ifaceGui.ShowAccu_raised = true;
	ifaceInternalSCI_OCB->Add();
	ifaceInternalSCI.accu = 0;
}

void AbstractCalculator::effect_main_region_active_lr12_lr12()
{
	ifaceInternalSCI_OCB->Equals();
	ifaceGui.ShowAccu_value = ifaceInternalSCI.operand;
	ifaceGui.ShowAccu_raised = true;
	ifaceInternalSCI_OCB->Sub();
	ifaceInternalSCI.accu = 0;
}

void AbstractCalculator::effect_main_region_active_lr13_lr13()
{
	ifaceInternalSCI_OCB->Equals();
	ifaceGui.ShowAccu_value = ifaceInternalSCI.operand;
	ifaceGui.ShowAccu_raised = true;
	ifaceInternalSCI_OCB->Mult();
	ifaceInternalSCI.accu = 0;
}

void AbstractCalculator::effect_main_region_active_lr14_lr14()
{
	ifaceInternalSCI_OCB->Equals();
	ifaceGui.ShowAccu_value = ifaceInternalSCI.operand;
	ifaceGui.ShowAccu_raised = true;
	ifaceInternalSCI_OCB->Div();
	ifaceInternalSCI.accu = 0;
}

void AbstractCalculator::effect_main_region_active_lr15_lr15()
{
	ifaceInternalSCI_OCB->Clear();
	ifaceInternalSCI.accu = 0;
	ifaceInternalSCI.operand = 0;
	ifaceGui.ShowAccu_value = ifaceInternalSCI.accu;
	ifaceGui.ShowAccu_raised = true;
}

void AbstractCalculator::effect_main_region_active_tr0()
{
	exseq_main_region_active();
	ifaceGui.Exit_raised = true;
	enseq_main_region__final__default();
}

void AbstractCalculator::effect_main_region_active_tr1()
{
	exseq_main_region_active();
	ifaceInternalSCI_OCB->Equals();
	ifaceGui.ShowAccu_value = ifaceInternalSCI.operand;
	ifaceGui.ShowAccu_raised = true;
	enseq_main_region_active_default();
}

/* Entry action for state 'active'. */
void AbstractCalculator::enact_main_region_active()
{
	/* Entry action for state 'active'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[0]), 30 * 1000, false);
	ifaceInternalSCI.accu = 0;
	ifaceInternalSCI.operand = 0;
}

/* Exit action for state 'active'. */
void AbstractCalculator::exact_main_region_active()
{
	/* Exit action for state 'active'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* 'default' enter sequence for state active */
void AbstractCalculator::enseq_main_region_active_default()
{
	/* 'default' enter sequence for state active */
	enact_main_region_active();
	stateConfVector[0] = main_region_active;
	stateConfVectorPosition = 0;
}

/* Default enter sequence for state null */
void AbstractCalculator::enseq_main_region__final__default()
{
	/* Default enter sequence for state null */
	stateConfVector[0] = main_region__final_;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void AbstractCalculator::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state active */
void AbstractCalculator::exseq_main_region_active()
{
	/* Default exit sequence for state active */
	stateConfVector[0] = Calculator_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_active();
}

/* Default exit sequence for final state. */
void AbstractCalculator::exseq_main_region__final_()
{
	/* Default exit sequence for final state. */
	stateConfVector[0] = Calculator_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void AbstractCalculator::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of calculator.main_region) at position 0... */
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

/* The reactions of state active. */
void AbstractCalculator::react_main_region_active()
{
	/* The reactions of state active. */
	if (check_main_region_active_tr0_tr0())
	{ 
		effect_main_region_active_tr0();
	}  else
	{
		if (check_main_region_active_tr1_tr1())
		{ 
			effect_main_region_active_tr1();
		}  else
		{
			if (check_main_region_active_lr1_lr1())
			{ 
				effect_main_region_active_lr1_lr1();
			} 
			if (check_main_region_active_lr2_lr2())
			{ 
				effect_main_region_active_lr2_lr2();
			} 
			if (check_main_region_active_lr3_lr3())
			{ 
				effect_main_region_active_lr3_lr3();
			} 
			if (check_main_region_active_lr4_lr4())
			{ 
				effect_main_region_active_lr4_lr4();
			} 
			if (check_main_region_active_lr5_lr5())
			{ 
				effect_main_region_active_lr5_lr5();
			} 
			if (check_main_region_active_lr6_lr6())
			{ 
				effect_main_region_active_lr6_lr6();
			} 
			if (check_main_region_active_lr7_lr7())
			{ 
				effect_main_region_active_lr7_lr7();
			} 
			if (check_main_region_active_lr8_lr8())
			{ 
				effect_main_region_active_lr8_lr8();
			} 
			if (check_main_region_active_lr9_lr9())
			{ 
				effect_main_region_active_lr9_lr9();
			} 
			if (check_main_region_active_lr10_lr10())
			{ 
				effect_main_region_active_lr10_lr10();
			} 
			if (check_main_region_active_lr11_lr11())
			{ 
				effect_main_region_active_lr11_lr11();
			} 
			if (check_main_region_active_lr12_lr12())
			{ 
				effect_main_region_active_lr12_lr12();
			} 
			if (check_main_region_active_lr13_lr13())
			{ 
				effect_main_region_active_lr13_lr13();
			} 
			if (check_main_region_active_lr14_lr14())
			{ 
				effect_main_region_active_lr14_lr14();
			} 
			if (check_main_region_active_lr15_lr15())
			{ 
				effect_main_region_active_lr15_lr15();
			} 
		}
	}
}

/* The reactions of state null. */
void AbstractCalculator::react_main_region__final_()
{
}

/* Default react sequence for initial entry  */
void AbstractCalculator::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_active_default();
}



