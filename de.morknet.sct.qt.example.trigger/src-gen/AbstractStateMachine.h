/* Copyright (C) 2020 - Steffen A. Mork */

#ifndef ABSTRACTSTATEMACHINE_H_
#define ABSTRACTSTATEMACHINE_H_


#include "../src-lib/sc_types.h"
#include "../src-lib/StatemachineInterface.h"
#include "../src-lib/TimedStatemachineInterface.h"

/*! \file Header of the state machine 'Trigger'.
*/


/*! Define indices of states in the StateConfVector */
#define SCVI_MAIN_REGION_WAIT 0
#define SCVI_MAIN_REGION_LANES 0
#define SCVI_MAIN_REGION_LANES_R1_A 0
#define SCVI_MAIN_REGION_LANES_R1__FINAL_ 0
#define SCVI_MAIN_REGION_LANES_R2_B 1
#define SCVI_MAIN_REGION_LANES_R2__FINAL_ 1
#define SCVI_MAIN_REGION_LANES_R3_C 2
#define SCVI_MAIN_REGION_LANES_R3__FINAL_ 2
#define SCVI_MAIN_REGION_LANES_GUARD_WAIT 3


class AbstractStateMachine : public TimedStatemachineInterface, public StatemachineInterface
{
	public:
		AbstractStateMachine();
		
		~AbstractStateMachine();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			Trigger_last_state,
			main_region_Wait,
			main_region_Lanes,
			main_region_Lanes_r1_A,
			main_region_Lanes_r1__final_,
			main_region_Lanes_r2_B,
			main_region_Lanes_r2__final_,
			main_region_Lanes_r3_C,
			main_region_Lanes_r3__final_,
			main_region_Lanes_guard_wait
		} TriggerStates;
					
		static const sc_integer numStates = 9;
		
		//! Inner class for gui interface scope.
		class SCI_Gui
		{
			public:
				/*! Raises the in event 'pressed' that is defined in the interface scope 'gui'. */
				void raise_pressed();
				
				
				/*! Checks if the out event 'update' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_update() const;
				
				
				/*! Checks if the out event 'wait' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_wait() const;
				
				
				/*! Checks if the out event 'lanes' that is defined in the interface scope 'gui' has been raised. */
				sc_boolean isRaised_lanes() const;
				
				
				/*! Gets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				sc_integer get_counter() const;
				
				/*! Sets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				void set_counter(sc_integer value);
				
				
				
			protected:
				friend class AbstractStateMachine;
				sc_boolean pressed_raised;
				sc_boolean update_raised;
				sc_boolean wait_raised;
				sc_boolean lanes_raised;
				sc_integer counter;
				
				
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
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		virtual void setTimer(TimerInterface* timerInterface);
		
		virtual TimerInterface* getTimer();
		
		virtual void raiseTimeEvent(sc_eventid event);
		
		virtual sc_integer getNumberOfParallelTimeEvents();
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(TriggerStates state) const;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 3;
		
		//! number of time events that can be active at once.
		static const sc_integer parallelTimeEventsCount = 3;
		
		
	protected:
		AbstractStateMachine(const AbstractStateMachine &rhs);
		AbstractStateMachine& operator=(const AbstractStateMachine&);
		
		//! Inner class for internal interface scope.
		class InternalSCI
		{
			public:
				/*! Raises the in event 'trigger' that is defined in the internal scope. */
				void raise_trigger();
				
				/*! Checks if the out event 'trigger' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_trigger() const;
				
				
				
			protected:
				friend class AbstractStateMachine;
				sc_boolean trigger_raised;
				
				
		};
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 4;
		
		TimerInterface* timer;
		sc_boolean timeEvents[timeEventsCount];
		
		
		TriggerStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		SCI_Gui ifaceGui;
		InternalSCI ifaceInternalSCI;
		
		// prototypes of all internal functions
		
		void enact_main_region_Wait();
		void enact_main_region_Lanes();
		void enact_main_region_Lanes_r1_A();
		void enact_main_region_Lanes_r2_B();
		void enact_main_region_Lanes_r3_C();
		void exact_main_region_Lanes_r1_A();
		void exact_main_region_Lanes_r2_B();
		void exact_main_region_Lanes_r3_C();
		void enseq_main_region_Wait_default();
		void enseq_main_region_Lanes_default();
		void enseq_main_region_Lanes_r1_A_default();
		void enseq_main_region_Lanes_r1__final__default();
		void enseq_main_region_Lanes_r2_B_default();
		void enseq_main_region_Lanes_r2__final__default();
		void enseq_main_region_Lanes_r3_C_default();
		void enseq_main_region_Lanes_r3__final__default();
		void enseq_main_region_Lanes_guard_wait_default();
		void enseq_main_region_default();
		void enseq_main_region_Lanes_r1_default();
		void enseq_main_region_Lanes_r2_default();
		void enseq_main_region_Lanes_r3_default();
		void enseq_main_region_Lanes_guard_default();
		void exseq_main_region_Wait();
		void exseq_main_region_Lanes();
		void exseq_main_region_Lanes_r1_A();
		void exseq_main_region_Lanes_r1__final_();
		void exseq_main_region_Lanes_r2_B();
		void exseq_main_region_Lanes_r2__final_();
		void exseq_main_region_Lanes_r3_C();
		void exseq_main_region_Lanes_r3__final_();
		void exseq_main_region_Lanes_guard_wait();
		void exseq_main_region();
		void exseq_main_region_Lanes_r1();
		void exseq_main_region_Lanes_r2();
		void exseq_main_region_Lanes_r3();
		void exseq_main_region_Lanes_guard();
		void react_main_region__entry_Default();
		void react_main_region_Lanes_r1__entry_Default();
		void react_main_region_Lanes_r2__entry_Default();
		void react_main_region_Lanes_r3__entry_Default();
		void react_main_region_Lanes_guard__entry_Default();
		sc_boolean react();
		sc_boolean main_region_Wait_react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r1_A_react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r1__final__react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r2_B_react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r2__final__react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r3_C_react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_r3__final__react(const sc_boolean try_transition);
		sc_boolean main_region_Lanes_guard_wait_react(const sc_boolean try_transition);
		void clearInEvents();
		void clearOutEvents();
		
		
		
		
	private:
		
		
};




#endif /* ABSTRACTSTATEMACHINE_H_ */
