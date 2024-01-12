/* Copyright (C) 2024 - Steffen A. Mork */

#ifndef TRIGGERSTATEMACHINE_H_
#define TRIGGERSTATEMACHINE_H_

/*!
Forward declaration for the TriggerStatemachine state machine.
*/
class TriggerStatemachine;


#include <deque>
#include "../src-qt-lib/sc_types.h"
#include "../src-qt-lib/sc_statemachine.h"
#include "../src-qt-lib/sc_eventdriven.h"
#include "../src-qt-lib/sc_timer.h"
#include <memory>
#include <string.h>
#include <QObject>

/*! \file
Header of the state machine 'Trigger'.
*/


class TriggerStatemachine : public QObject, public sc::timer::TimedInterface, public std::enable_shared_from_this<sc::timer::TimedInterface>, public sc::EventDrivenInterface
{
	Q_OBJECT
	
	public:
		explicit TriggerStatemachine(QObject *parent) noexcept;
		
		virtual ~TriggerStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_Wait,
			main_region_Lanes,
			main_region_Lanes_r1_A,
			main_region_Lanes_r1__final_,
			main_region_Lanes_r2_B,
			main_region_Lanes_r2__final_,
			main_region_Lanes_r3_C,
			main_region_Lanes_r3__final_,
			main_region_Lanes_guard_wait
		};
		
		/*! The number of states. */
		static constexpr const sc::integer numStates {9};
		static constexpr const sc::integer scvi_main_region_Wait {0};
		static constexpr const sc::integer scvi_main_region_Lanes {0};
		static constexpr const sc::integer scvi_main_region_Lanes_r1_A {0};
		static constexpr const sc::integer scvi_main_region_Lanes_r1__final_ {0};
		static constexpr const sc::integer scvi_main_region_Lanes_r2_B {1};
		static constexpr const sc::integer scvi_main_region_Lanes_r2__final_ {1};
		static constexpr const sc::integer scvi_main_region_Lanes_r3_C {2};
		static constexpr const sc::integer scvi_main_region_Lanes_r3__final_ {2};
		static constexpr const sc::integer scvi_main_region_Lanes_guard_wait {3};
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			Gui_pressed,
			Internal_trigger,
			_te0_main_region_Lanes_r1_A_,
			_te1_main_region_Lanes_r2_B_,
			_te2_main_region_Lanes_r3_C_
		};
		
		class EventInstance
		{
			public:
				explicit  EventInstance(Event id) noexcept : eventId(id){}
				virtual ~EventInstance() = default;
				const Event eventId;
		};
		
		
		//! Inner class for gui interface scope.
		class Gui
		{
			public:
				explicit Gui(TriggerStatemachine* parent) noexcept;
				
				
				
				
				
				
				/*! Gets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				sc::integer getCounter() const noexcept;
				
				/*! Sets the value of the variable 'counter' that is defined in the interface scope 'gui'. */
				void setCounter(sc::integer counter) noexcept;
				
				
				
				
			protected:
				friend class TriggerStatemachine;
				
				sc::integer counter {0};
				
				/*! Indicates event 'pressed' of interface scope 'gui' is active. */
				bool pressed_raised {false};
				
				
			private:
				TriggerStatemachine* parent;
				
				
				
				
				
		};
		
		/*! Returns an instance of the interface class 'Gui'. */
		Gui& gui() noexcept;
		
		
		/*! Can be used by the client code to trigger a run to completion step without raising an event. */
		void triggerWithoutEvent() override;
		/*
		 * Functions inherited from StatemachineInterface
		 */
		 void enter() override;
		
		 void exit() override;
		
		/*!
		 * Checks if the state machine is active (until 2.4.1 this method was used for states).
		 * A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		 */
		 bool isActive() const noexcept override;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		 bool isFinal() const noexcept override;
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		bool check() const noexcept;
		
		/*
		 * Functions inherited from TimedStatemachineInterface
		 */
		void setTimerService(std::shared_ptr<sc::timer::TimerServiceInterface> timerService_) noexcept override;
		
		std::shared_ptr<sc::timer::TimerServiceInterface> getTimerService() noexcept override;
		
		void raiseTimeEvent(sc::eventid event) override;
		
		sc::integer getNumberOfParallelTimeEvents() noexcept override;
		
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const noexcept;
		
		//! number of time events used by the state machine.
		static const sc::integer timeEventsCount {3};
		
		//! number of time events that can be active at once.
		static const sc::integer parallelTimeEventsCount {3};
		
		
	public slots:
		/*! Slot for the in event 'pressed' that is defined in the interface scope 'gui'. */
		void gui_pressed();
		
		
	signals:
		/*! Signal representing the out event 'update' that is defined in the interface scope 'gui'. */
		void gui_update();
		
		/*! Signal representing the out event 'wait' that is defined in the interface scope 'gui'. */
		void gui_wait();
		
		/*! Signal representing the out event 'lanes' that is defined in the interface scope 'gui'. */
		void gui_lanes();
		
	
	protected:
		TriggerStatemachine(const TriggerStatemachine &rhs);
		TriggerStatemachine& operator=(const TriggerStatemachine&);
		
		
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates {4};
		
		std::shared_ptr<sc::timer::TimerServiceInterface> timerService;
		bool timeEvents[timeEventsCount];
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		Gui ifaceGui {Gui{nullptr}};
		
		
		bool isExecuting {false};
		sc::integer stateConfVectorPosition {0};
		
		
		
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
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_Wait_react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r1_A_react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r1__final__react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r2_B_react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r2__final__react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r3_C_react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_r3__final__react(const sc::integer transitioned_before);
		sc::integer main_region_Lanes_guard_wait_react(const sc::integer transitioned_before);
		void clearInEvents() noexcept;
		void clearInternalEvents() noexcept;
		void microStep();
		void runCycle();
		
		
		
		
		std::deque<std::unique_ptr<EventInstance>> incomingEventQueue;
		
		std::deque<std::unique_ptr<EventInstance>> internalEventQueue;
		
		std::unique_ptr<EventInstance> getNextEvent() noexcept;
		
		bool dispatchEvent(std::unique_ptr<EventInstance> event) noexcept;
		
		
		
	private:
		
		/*! Indicates event 'trigger' of internal scope is active. */
		bool trigger_raised {false};
		
		
		
};




#endif /* TRIGGERSTATEMACHINE_H_ */
