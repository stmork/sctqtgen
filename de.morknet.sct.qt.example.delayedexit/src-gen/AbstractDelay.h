/* Copyright (C) 2017 - Steffen A. Mork */

#ifndef ABSTRACTDELAY_H_
#define ABSTRACTDELAY_H_

#include "../src/sc_types.h"
#include "../src/StatemachineInterface.h"

/*! \file Header of the state machine 'DelayedExit'.
*/


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_STATEA 0
#define SCVI_MAIN_REGION_DO_SOMETHING 0

class AbstractDelay : public StatemachineInterface
{
	public:
		
		AbstractDelay();
		
		~AbstractDelay();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			DelayedExit_last_state,
			main_region_StateA,
			main_region_Do_Something
		} DelayedExitStates;
		
		//! Inner class for gui interface scope.
		class SCI_Gui
		{
			
			public:
				/*! Raises the in event 'button1' that is defined in the interface scope 'gui'. */
				void raise_button1();
				
				/*! Raises the in event 'button2' that is defined in the interface scope 'gui'. */
				void raise_button2();
				
				/*! Checks if the out event 'stateA' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_stateA() const;
				
				/*! Checks if the out event 'doSomething' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_doSomething() const;
				
				
			protected:
				friend class AbstractDelay;
				sc_boolean button1_raised;
				sc_boolean button2_raised;
				sc_boolean stateA_raised;
				sc_boolean doSomething_raised;
		};
		
		/*! Returns an instance of the interface class 'SCI_Gui'. */
		SCI_Gui* getSCI_Gui();
		
		
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
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(DelayedExitStates state) const;
		
		
	protected:
	
	
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 1;
		
		
		DelayedExitStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		SCI_Gui ifaceGui;
		
		// prototypes of all internal functions
		
		sc_boolean check_main_region_StateA_tr0_tr0();
		sc_boolean check_main_region_Do_Something_tr0_tr0();
		sc_boolean check_main_region_Do_Something_tr1_tr1();
		void effect_main_region_StateA_tr0();
		void effect_main_region_Do_Something_tr0();
		void effect_main_region_Do_Something_tr1();
		void enact_main_region_StateA();
		void enact_main_region_Do_Something();
		void enseq_main_region_StateA_default();
		void enseq_main_region_Do_Something_default();
		void enseq_main_region_default();
		void exseq_main_region_StateA();
		void exseq_main_region_Do_Something();
		void exseq_main_region();
		void react_main_region_StateA();
		void react_main_region_Do_Something();
		void react_main_region__entry_Default();
		void clearInEvents();
		void clearOutEvents();
		
		
};



#endif /* ABSTRACTDELAY_H_ */
