/* Copyright (C) 2021 - Steffen A. Mork */

#ifndef ABSTRACTSTATEMACHINE_H_
#define ABSTRACTSTATEMACHINE_H_

/*!
 * Forward declaration for the AbstractStateMachine state machine.
 */
 class AbstractStateMachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_rxcpp.h"
#include "../src-qt-lib/sc_statemachine.h"
#include "../src-qt-lib/sc_timer.h"
#include <QObject>

/*! \file Header of the state machine 'Trigger'.
*/


#ifndef SCT_EVENTS_TRIGGER_H
#define SCT_EVENTS_TRIGGER_H
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif

namespace trigger_events
{
typedef enum  {
	invalid_event = SC_INVALID_EVENT_VALUE,
	Gui_pressed,
	Internal_trigger,
	Trigger_main_region_Lanes_r1_A_time_event_0,
	Trigger_main_region_Lanes_r2_B_time_event_0,
	Trigger_main_region_Lanes_r3_C_time_event_0
} AbstractStateMachineEventName;

class SctEvent
{
	public:
		SctEvent(AbstractStateMachineEventName name) : name(name){}
		virtual ~SctEvent(){}
		const AbstractStateMachineEventName name;
		
};
		
template <typename T>
class TypedSctEvent : public SctEvent
{
	public:
		TypedSctEvent(AbstractStateMachineEventName name, T value) :
			SctEvent(name),
			value(value)
			{}
		virtual ~TypedSctEvent(){}
		const T value;
};

class SctEvent_Gui_pressed : public SctEvent
{
	public:
		SctEvent_Gui_pressed(AbstractStateMachineEventName name) : SctEvent(name){};
};
class SctEvent_Internal_trigger : public SctEvent
{
	public:
		SctEvent_Internal_trigger(AbstractStateMachineEventName name) : SctEvent(name){};
};
class TimedSctEvent : public SctEvent
{
	public:
		TimedSctEvent(AbstractStateMachineEventName name) : SctEvent(name){};
};

}
#endif /* SCT_EVENTS_TRIGGER_H */


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


class AbstractStateMachine : public QObject, public sc::timer::TimedInterface, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		AbstractStateMachine(QObject *parent);
		
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
		class Gui
		{
			public:
				Gui(AbstractStateMachine* parent);
				
				
				
				
				
				/*! Gets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				sc_integer getCounter() const;
				
				/*! Sets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				void setCounter(sc_integer value);
				
				
				
				
			protected:
				friend class AbstractStateMachine;
				
				/*! Raises the in event 'pressed' that is defined in the interface scope 'gui'. */
				void internal_gui_pressed();
				sc_boolean pressed_raised;
				sc_integer counter;
				void dispatch_event(trigger_events::SctEvent * event);
				
				
			private:
				AbstractStateMachine* parent;
				
				
				
				
				
		};
		
		/*! Returns an instance of the interface class 'Gui'. */
		Gui* gui();
		
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		virtual void enter();
		
		virtual void exit();
		
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
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		sc_boolean check();
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		virtual void setTimerService(sc::timer::TimerServiceInterface* timerService);
		
		virtual sc::timer::TimerServiceInterface* getTimerService();
		
		virtual void raiseTimeEvent(sc_eventid event);
		
		virtual sc_integer getNumberOfParallelTimeEvents();
		
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(TriggerStates state) const;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 3;
		
		//! number of time events that can be active at once.
		static const sc_integer parallelTimeEventsCount = 3;
		
		
	public slots:
		/*! slot for the in event 'pressed' that is defined in the interface scope 'gui'. */
		void gui_pressed();
		
		
	signals:
		/*! Signal representing the out event 'update' that is defined in the interface scope 'gui'. */
		void gui_update();
		
		/*! Signal representing the out event 'wait' that is defined in the interface scope 'gui'. */
		void gui_wait();
		
		/*! Signal representing the out event 'lanes' that is defined in the interface scope 'gui'. */
		void gui_lanes();
		
	
	protected:
		AbstractStateMachine(const AbstractStateMachine &rhs);
		AbstractStateMachine& operator=(const AbstractStateMachine&);
		
		/*! Raises the in event 'trigger' that is defined in the internal scope. */
		void internal_trigger();
		sc_boolean trigger_raised;
		void internal_dispatch_event(trigger_events::SctEvent * event);
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_ushort maxOrthogonalStates = 4;
		
		sc::timer::TimerServiceInterface* timerService;
		sc_boolean timeEvents[timeEventsCount];
		
		
		TriggerStates stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui;
		
		
		sc_boolean isExecuting;
		sc_integer stateConfVectorPosition;
		
		/*! Raises the in event 'trigger' that is defined in the internal scope. */
		void trigger();
		
		/*! Checks if the out event 'trigger' that is defined in the internal scope has been raised. */
		sc_boolean isRaisedTrigger() const;
		
		
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
		sc_integer react(const sc_integer transitioned_before);
		sc_integer main_region_Wait_react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r1_A_react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r1__final__react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r2_B_react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r2__final__react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r3_C_react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_r3__final__react(const sc_integer transitioned_before);
		sc_integer main_region_Lanes_guard_wait_react(const sc_integer transitioned_before);
		void clearInEvents();
		void clearInternalEvents();
		void microStep();
		void runCycle();
		
		
		
		
	private:
		std::deque<trigger_events::SctEvent*> internalEventQueue;
		trigger_events::SctEvent* getNextEvent();
		void dispatch_event(trigger_events::SctEvent * event);
		trigger_events::AbstractStateMachineEventName getTimedEventName(sc_eventid evid);
		std::deque<trigger_events::SctEvent*> inEventQueue;
		
		
};




#endif /* ABSTRACTSTATEMACHINE_H_ */
