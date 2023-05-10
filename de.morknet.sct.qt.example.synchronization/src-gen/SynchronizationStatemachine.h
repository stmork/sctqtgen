/* Copyright (C) 2023 - Steffen A. Mork */

#ifndef SYNCHRONIZATIONSTATEMACHINE_H_
#define SYNCHRONIZATIONSTATEMACHINE_H_

/*!
Forward declaration for the SynchronizationStatemachine state machine.
*/
class SynchronizationStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include "../src-lib/sc_eventdriven.h"
#include <memory>
#include <QObject>

/*! \file
Header of the state machine 'Synchronization'.
*/


class SynchronizationStatemachine : public QObject, public sc::EventDrivenInterface
{
	Q_OBJECT
	
	public:
		explicit SynchronizationStatemachine(QObject *parent) noexcept;
		
		virtual ~SynchronizationStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			main_region_Split,
			main_region_Split_left_Action,
			main_region_Split_left_Wait,
			main_region_Split_right_Action,
			main_region_Split_right_Wait,
			main_region_Wait,
			main_region_Completed
		};
		
		/*! The number of states. */
		static constexpr const sc::integer numStates {7};
		static constexpr const sc::integer scvi_main_region_Split {0};
		static constexpr const sc::integer scvi_main_region_Split_left_Action {0};
		static constexpr const sc::integer scvi_main_region_Split_left_Wait {0};
		static constexpr const sc::integer scvi_main_region_Split_right_Action {1};
		static constexpr const sc::integer scvi_main_region_Split_right_Wait {1};
		static constexpr const sc::integer scvi_main_region_Wait {0};
		static constexpr const sc::integer scvi_main_region_Completed {0};
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			start,
			triggerLeft,
			triggerRight
		};
		
		class EventInstance
		{
			public:
				explicit  EventInstance(Event id) noexcept : eventId(id){}
				virtual ~EventInstance() = default;
				const Event eventId;
		};
		
		
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual void waiting() = 0;
				
				virtual void started() = 0;
				
				virtual void left() = 0;
				
				virtual void right() = 0;
				
				virtual void leftClicked() = 0;
				
				virtual void rightClicked() = 0;
				
				virtual void completed() = 0;
				
				
		};
		
		/*! Set the working instance of the operation callback interface 'OperationCallback'. */
		void setOperationCallback(std::shared_ptr<OperationCallback> operationCallback) noexcept;
		
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
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const noexcept;
		
		
		
	public slots:
		/*! Slot for the in event 'start' that is defined in the default interface scope. */
		void start();
		
		/*! Slot for the in event 'triggerLeft' that is defined in the default interface scope. */
		void triggerLeft();
		
		/*! Slot for the in event 'triggerRight' that is defined in the default interface scope. */
		void triggerRight();
		
		
	protected:
		
		
		std::deque<std::unique_ptr<EventInstance>> incomingEventQueue;
		
		std::unique_ptr<EventInstance> getNextEvent() noexcept;
		
		bool dispatchEvent(std::unique_ptr<EventInstance> event) noexcept;
		
		
		
	private:
		SynchronizationStatemachine(const SynchronizationStatemachine &rhs);
		SynchronizationStatemachine& operator=(const SynchronizationStatemachine&);
		
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates {2};
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		
		std::shared_ptr<OperationCallback> ifaceOperationCallback {nullptr};
		
		bool isExecuting {false};
		sc::integer stateConfVectorPosition {0};
		bool stateConfVectorChanged {false};
		
		
		
		// prototypes of all internal functions
		
		void enact_main_region_Split();
		void enact_main_region_Split_left_Action();
		void enact_main_region_Split_left_Wait();
		void enact_main_region_Split_right_Action();
		void enact_main_region_Split_right_Wait();
		void enact_main_region_Wait();
		void enact_main_region_Completed();
		void enseq_main_region_Split_left_Action_default();
		void enseq_main_region_Split_left_Wait_default();
		void enseq_main_region_Split_right_Action_default();
		void enseq_main_region_Split_right_Wait_default();
		void enseq_main_region_Wait_default();
		void enseq_main_region_Completed_default();
		void enseq_main_region_default();
		void exseq_main_region_Split();
		void exseq_main_region_Split_left_Action();
		void exseq_main_region_Split_left_Wait();
		void exseq_main_region_Split_right_Action();
		void exseq_main_region_Split_right_Wait();
		void exseq_main_region_Wait();
		void exseq_main_region_Completed();
		void exseq_main_region();
		void exseq_main_region_Split_left();
		void exseq_main_region_Split_right();
		void react_main_region__entry_Default();
		void react_main_region__sync0();
		void react_main_region__sync1();
		sc::integer react(const sc::integer transitioned_before);
		sc::integer main_region_Split_react(const sc::integer transitioned_before);
		sc::integer main_region_Split_left_Action_react(const sc::integer transitioned_before);
		sc::integer main_region_Split_left_Wait_react(const sc::integer transitioned_before);
		sc::integer main_region_Split_right_Action_react(const sc::integer transitioned_before);
		sc::integer main_region_Split_right_Wait_react(const sc::integer transitioned_before);
		sc::integer main_region_Wait_react(const sc::integer transitioned_before);
		sc::integer main_region_Completed_react(const sc::integer transitioned_before);
		void clearInEvents() noexcept;
		void microStep();
		void runCycle();
		
		
		
		
		/*! Indicates event 'start' of default interface scope is active. */
		bool start_raised {false};
		
		/*! Indicates event 'triggerLeft' of default interface scope is active. */
		bool triggerLeft_raised {false};
		
		/*! Indicates event 'triggerRight' of default interface scope is active. */
		bool triggerRight_raised {false};
		
		
		
};


inline SynchronizationStatemachine::OperationCallback::~OperationCallback() {}


#endif /* SYNCHRONIZATIONSTATEMACHINE_H_ */
