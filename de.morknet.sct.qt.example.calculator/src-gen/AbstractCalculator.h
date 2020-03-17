/* Copyright (C) 2020 - Steffen A. Mork */

#ifndef ABSTRACTCALCULATOR_H_
#define ABSTRACTCALCULATOR_H_


#include "../src/sc_types.h"
#include "../src/StatemachineInterface.h"
#include "../src/TimedStatemachineInterface.h"

/*! \file Header of the state machine 'Calculator'.
*/




/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_ACTIVE 0
#define SCVI_MAIN_REGION__FINAL_ 0


class AbstractCalculator : public TimedStatemachineInterface, public StatemachineInterface
{
	public:
		AbstractCalculator();
		
		virtual ~AbstractCalculator();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Calculator_last_state,
			main_region_active,
			main_region__final_
		} CalculatorStates;
					
		static const sc_integer numStates = 2;
		
		//! Inner class for gui interface scope.
		class SCI_Gui
		{
			public:
				SCI_Gui(AbstractCalculator * parent):
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
					ShowAccu_value(),
					parent(parent)
				{}
				
				/*! Raises the in event 'Button0' that is defined in the interface scope 'gui'. */
				void raise_button0();
				
				
				/*! Raises the in event 'Button1' that is defined in the interface scope 'gui'. */
				void raise_button1();
				
				
				/*! Raises the in event 'Button2' that is defined in the interface scope 'gui'. */
				void raise_button2();
				
				
				/*! Raises the in event 'Button3' that is defined in the interface scope 'gui'. */
				void raise_button3();
				
				
				/*! Raises the in event 'Button4' that is defined in the interface scope 'gui'. */
				void raise_button4();
				
				
				/*! Raises the in event 'Button5' that is defined in the interface scope 'gui'. */
				void raise_button5();
				
				
				/*! Raises the in event 'Button6' that is defined in the interface scope 'gui'. */
				void raise_button6();
				
				
				/*! Raises the in event 'Button7' that is defined in the interface scope 'gui'. */
				void raise_button7();
				
				
				/*! Raises the in event 'Button8' that is defined in the interface scope 'gui'. */
				void raise_button8();
				
				
				/*! Raises the in event 'Button9' that is defined in the interface scope 'gui'. */
				void raise_button9();
				
				
				/*! Raises the in event 'ButtonAdd' that is defined in the interface scope 'gui'. */
				void raise_buttonAdd();
				
				
				/*! Raises the in event 'ButtonSub' that is defined in the interface scope 'gui'. */
				void raise_buttonSub();
				
				
				/*! Raises the in event 'ButtonMult' that is defined in the interface scope 'gui'. */
				void raise_buttonMult();
				
				
				/*! Raises the in event 'ButtonDiv' that is defined in the interface scope 'gui'. */
				void raise_buttonDiv();
				
				
				/*! Raises the in event 'ButtonEquals' that is defined in the interface scope 'gui'. */
				void raise_buttonEquals();
				
				
				/*! Raises the in event 'ButtonClear' that is defined in the interface scope 'gui'. */
				void raise_buttonClear();
				
				
				/*! Checks if the out event 'Exit' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_exit() const;
				
				
				/*! Checks if the out event 'ShowAccu' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_showAccu() const;
				
				/*! Gets the value of the out event 'ShowAccu' that is defined in the interface scope 'gui'. */
				sc_integer get_showAccu_value() const;
				
				
				
			protected:
				friend class AbstractCalculator;
				sc_boolean Button0_raised;
				sc_boolean Button1_raised;
				sc_boolean Button2_raised;
				sc_boolean Button3_raised;
				sc_boolean Button4_raised;
				sc_boolean Button5_raised;
				sc_boolean Button6_raised;
				sc_boolean Button7_raised;
				sc_boolean Button8_raised;
				sc_boolean Button9_raised;
				sc_boolean ButtonAdd_raised;
				sc_boolean ButtonSub_raised;
				sc_boolean ButtonMult_raised;
				sc_boolean ButtonDiv_raised;
				sc_boolean ButtonEquals_raised;
				sc_boolean ButtonClear_raised;
				sc_boolean Exit_raised;
				sc_boolean ShowAccu_raised;
				sc_integer ShowAccu_value;
				AbstractCalculator * parent;
				
				
		};
		
		/*! Returns an instance of the interface class 'SCI_Gui'. */
		SCI_Gui* getSCI_Gui();
		
		//! Inner class for internal interface scope operation callbacks.
		class InternalSCI_OCB
		{
			public:
				virtual ~InternalSCI_OCB() = 0;
				
				virtual void Add() = 0;
				
				virtual void Sub() = 0;
				
				virtual void Mult() = 0;
				
				virtual void Div() = 0;
				
				virtual void Equals() = 0;
				
				virtual void Clear() = 0;
				
				virtual void Digit(sc_integer digit) = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'InternalSCI_OCB'. */
		void setInternalSCI_OCB(InternalSCI_OCB* operationCallback);
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		virtual void init();
		
		virtual void enter();
		
		virtual void exit();
		
		virtual void runCycle();
		
		/*!
		* Checks if the state machine is active (until 2.4.1 this method was used for states).
		* A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		*/
		virtual sc_boolean isActive() const;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		virtual sc_boolean isFinal() const;
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		virtual void setTimer(TimerInterface* timerInterface);
		
		virtual TimerInterface* getTimer();
		
		virtual void raiseTimeEvent(sc_eventid event);
		
		virtual sc_integer getNumberOfParallelTimeEvents();
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(CalculatorStates state) const;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 1;
		
		//! number of time events that can be active at once.
		static const sc_integer parallelTimeEventsCount = 1;
		
		
	protected:
		AbstractCalculator(const AbstractCalculator &rhs);
		AbstractCalculator& operator=(const AbstractCalculator&);
		
		//! Inner class for internal interface scope.
		class InternalSCI
		{
			public:
				InternalSCI(AbstractCalculator * parent):
					parent(parent)
				{}
				
				/*! Gets the value of the variable 'operand' that is defined in the internal scope. */
				sc_integer get_operand() const;
				
				/*! Sets the value of the variable 'operand' that is defined in the internal scope. */
				void set_operand(sc_integer value);
				
				
				/*! Gets the value of the variable 'accu' that is defined in the internal scope. */
				sc_integer get_accu() const;
				
				/*! Sets the value of the variable 'accu' that is defined in the internal scope. */
				void set_accu(sc_integer value);
				
				
				
				
				
				
				
				
				
				
			protected:
				friend class AbstractCalculator;
				sc_integer operand;
				sc_integer accu;
				AbstractCalculator * parent;
				
				
		};
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 1;
		
		TimerInterface* timer;
		sc_boolean timeEvents[timeEventsCount];
		
		
		CalculatorStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		SCI_Gui ifaceGui;
		InternalSCI ifaceInternalSCI;
		InternalSCI_OCB* ifaceInternalSCI_OCB;
		
		// prototypes of all internal functions
		
		void enact_main_region_active();
		void exact_main_region_active();
		void enseq_main_region_active_default();
		void enseq_main_region__final__default();
		void enseq_main_region_default();
		void exseq_main_region_active();
		void exseq_main_region__final_();
		void exseq_main_region();
		void react_main_region__entry_Default();
		sc_boolean react();
		sc_boolean main_region_active_react(const sc_boolean try_transition);
		sc_boolean main_region__final__react(const sc_boolean try_transition);
		void clearInEvents();
		void clearOutEvents();
		
		
		
		
	private:
		
		
};


inline AbstractCalculator::InternalSCI_OCB::~InternalSCI_OCB() {}


#endif /* ABSTRACTCALCULATOR_H_ */
