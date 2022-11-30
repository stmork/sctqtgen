/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef SYNCHRONIZATIONSTATEMACHINE_H_
#define SYNCHRONIZATIONSTATEMACHINE_H_

/*!
Forward declaration for the SynchronizationStatemachine state machine.
*/
class SynchronizationStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include <QObject>

/*! \file
Header of the state machine 'Synchronization'.
*/


class SynchronizationStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		SynchronizationStatemachine(QObject *parent);
		
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
		static const sc::integer numStates = 7;
		static const sc::integer scvi_main_region_Split = 0;
		static const sc::integer scvi_main_region_Split_left_Action = 0;
		static const sc::integer scvi_main_region_Split_left_Wait = 0;
		static const sc::integer scvi_main_region_Split_right_Action = 1;
		static const sc::integer scvi_main_region_Split_right_Wait = 1;
		static const sc::integer scvi_main_region_Wait = 0;
		static const sc::integer scvi_main_region_Completed = 0;
		
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
				explicit EventInstance(Event id) : eventId(id){}
				virtual ~EventInstance() = default;
				const Event eventId;
		};
		
		/*! Can be used by the client code to trigger a run to completion step without raising an event. */
		void triggerWithoutEvent();
		
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
		void setOperationCallback(OperationCallback* operationCallback);
		
		/*
		 * Functions inherited from StatemachineInterface
		 */
		void enter() override;
		
		void exit() override;
		
		/*!
		 * Checks if the state machine is active (until 2.4.1 this method was used for states).
		 * A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		 */
		bool isActive() const override;
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		bool isFinal() const override;
		
		/*! 
		 * Checks if member of the state machine must be set. For example an operation callback.
		 */
		bool check() const;
		
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		bool isStateActive(State state) const;
		
		
		
	public slots:
		/*! Slot for the in event 'start' that is defined in the default interface scope. */
		void start();
		
		/*! Slot for the in event 'triggerLeft' that is defined in the default interface scope. */
		void triggerLeft();
		
		/*! Slot for the in event 'triggerRight' that is defined in the default interface scope. */
		void triggerRight();
		
		
	protected:
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		SynchronizationStatemachine(const SynchronizationStatemachine &rhs);
		SynchronizationStatemachine& operator=(const SynchronizationStatemachine&);
		
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 2;
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		OperationCallback* ifaceOperationCallback;
		
		
		bool isExecuting;
		sc::integer stateConfVectorPosition;
		
		
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
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		/*! Indicates event 'start' of default interface scope is active. */
		bool start_raised;
		
		/*! Indicates event 'triggerLeft' of default interface scope is active. */
		bool triggerLeft_raised;
		
		/*! Indicates event 'triggerRight' of default interface scope is active. */
		bool triggerRight_raised;
		
		
		
};


inline SynchronizationStatemachine::OperationCallback::~OperationCallback() {}


#endif /* SYNCHRONIZATIONSTATEMACHINE_H_ */
