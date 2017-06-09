/* Copyright (C) 2017 - Steffen A. Mork */

#ifndef ABSTRACTSTATEMACHINE_H_
#define ABSTRACTSTATEMACHINE_H_

#include "../src/sc_types.h"
#include "StatemachineInterface.h"

/*! \file Header of the state machine 'default'.
*/

class AbstractStateMachine : public StatemachineInterface
{
	
	public:
		
		AbstractStateMachine();
		
		~AbstractStateMachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			main_region_State_Off,
			main_region_State_On,
			Default_last_state
		} DefaultStates;
		
		//! Inner class for gui interface scope.
		class SCI_Gui
		{
			
			public:
				/*! Raises the in event 'clicked' that is defined in the interface scope 'gui'. */
				void raise_clicked();
				
				/*! Checks if the out event 'on' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_on();
				
				/*! Checks if the out event 'off' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_off();
				
				
			protected:
				friend class AbstractStateMachine;
				sc_boolean clicked_raised;
				sc_boolean on_raised;
				sc_boolean off_raised;
		};
				
		
		/*! Returns an instance of the interface class 'SCI_Gui'. */
		SCI_Gui* getSCI_Gui();
		
		
		void init();
		
		void enter();
		
		void exit();
		
		void runCycle();
		
		/*!
		* Checks if the state machine is active (until 2.4.1 this method was used for states).
		* A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		*/
		sc_boolean isActive();
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		sc_boolean isFinal();
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(DefaultStates state);
	
	protected:
	
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 1;
		
		
		DefaultStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		SCI_Gui ifaceGui;
		
		// prototypes of all internal functions
		
		sc_boolean check_main_region_State_Off_tr0_tr0();
		sc_boolean check_main_region_State_On_tr0_tr0();
		void effect_main_region_State_Off_tr0();
		void effect_main_region_State_On_tr0();
		void enact_main_region_State_On();
		void exact_main_region_State_On();
		void enseq_main_region_State_Off_default();
		void enseq_main_region_State_On_default();
		void enseq_main_region_default();
		void exseq_main_region_State_Off();
		void exseq_main_region_State_On();
		void exseq_main_region();
		void react_main_region_State_Off();
		void react_main_region_State_On();
		void react_main_region__entry_Default();
		void clearInEvents();
		void clearOutEvents();
		
};
#endif /* ABSTRACTSTATEMACHINE_H_ */
