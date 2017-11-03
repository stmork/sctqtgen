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
#define SCVI_MAIN_REGION_WAIT 0

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
			main_region_Do_Something,
			main_region_Wait
		} DelayedExitStates;
		
		//! Inner class for gui interface scope.
		class SCI_Gui
		{
			
			public:
				/*! Raises the in event 'button1' that is defined in the interface scope 'gui'. */
				void raise_button1();
				
				/*! Raises the in event 'button2' that is defined in the interface scope 'gui'. */
				void raise_button2();
				
				/*! Raises the in event 'complete' that is defined in the interface scope 'gui'. */
				void raise_complete();
				
				/*! Checks if the out event 'stateA' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_stateA() const;
				
				/*! Checks if the out event 'doSomething' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_doSomething() const;
				
				/*! Checks if the out event 'stopping' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_stopping() const;
				
				/*! Gets the value of the out event 'stopping' that is defined in the interface scope 'gui'. */
				sc_boolean get_stopping_value() const;
				
				/*! Checks if the out event 'triggerStop' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_triggerStop() const;
				
				/*! Checks if the out event 'stopped' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_stopped() const;
				
				
			protected:
				friend class AbstractDelay;
				sc_boolean button1_raised;
				sc_boolean button2_raised;
				sc_boolean complete_raised;
				sc_boolean stateA_raised;
				sc_boolean doSomething_raised;
				sc_boolean stopping_raised;
				sc_boolean stopping_value;
				sc_boolean triggerStop_raised;
				sc_boolean stopped_raised;
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
		
		sc_boolean check_main_region_StateA_lr1_lr1();
		sc_boolean check_main_region_StateA_tr0_tr0();
		sc_boolean check_main_region_Do_Something_tr0_tr0();
		sc_boolean check_main_region_Do_Something_tr1_tr1();
		sc_boolean check_main_region_Wait_tr0_tr0();
		void effect_main_region_StateA_lr1_lr1();
		void effect_main_region_StateA_tr0();
		void effect_main_region_Do_Something_tr0();
		void effect_main_region_Do_Something_tr1();
		void effect_main_region_Wait_tr0();
		void enact_main_region_StateA();
		void enact_main_region_Do_Something();
		void enact_main_region_Wait();
		void exact_main_region_Do_Something();
		void exact_main_region_Wait();
		void enseq_main_region_StateA_default();
		void enseq_main_region_Do_Something_default();
		void enseq_main_region_Wait_default();
		void enseq_main_region_default();
		void exseq_main_region_StateA();
		void exseq_main_region_Do_Something();
		void exseq_main_region_Wait();
		void exseq_main_region();
		void react_main_region_StateA();
		void react_main_region_Do_Something();
		void react_main_region_Wait();
		void react_main_region__entry_Default();
		void clearInEvents();
		void clearOutEvents();
		
		
};



#endif /* ABSTRACTDELAY_H_ */
