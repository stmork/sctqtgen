/* Copyright (C) 2022 - Steffen A. Mork */

#ifndef ORTHOGONALSTATEMACHINE_H_
#define ORTHOGONALSTATEMACHINE_H_

/*!
Forward declaration for the OrthogonalStatemachine state machine.
*/
class OrthogonalStatemachine;


#include <deque>
#include "../src-lib/sc_types.h"
#include "../src-lib/sc_statemachine.h"
#include <QObject>

/*! \file
Header of the state machine 'OrthogonalStatemachine'.
*/


class OrthogonalStatemachine : public QObject, public sc::StatemachineInterface
{
	Q_OBJECT
	
	public:
		OrthogonalStatemachine(QObject *parent);
		
		virtual ~OrthogonalStatemachine();
		
		
		
		/*! Enumeration of all states. */
		enum class State
		{
			NO_STATE,
			Left_State,
			Right_State
		};
		
		/*! The number of states. */
		static const sc::integer numStates = 2;
		static const sc::integer scvi_Left_State = 0;
		static const sc::integer scvi_Right_State = 1;
		
		/*! Enumeration of all events which are consumed. */
		enum class Event
		{
			NO_EVENT,
			trigger
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
		
		/*! Gets the value of the variable 'left' that is defined in the default interface scope. */
		sc::integer getLeft() const;
		
		/*! Sets the value of the variable 'left' that is defined in the default interface scope. */
		void setLeft(sc::integer value);
		
		/*! Gets the value of the variable 'right' that is defined in the default interface scope. */
		sc::integer getRight() const;
		
		/*! Sets the value of the variable 'right' that is defined in the default interface scope. */
		void setRight(sc::integer value);
		
		//! Inner class for default interface scope operation callbacks.
		class OperationCallback
		{
			public:
				virtual ~OperationCallback() = 0;
				
				virtual bool isLeft() = 0;
				
				virtual bool isRight() = 0;
				
				virtual void label() = 0;
				
				
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
		/*! Slot for the in event 'trigger' that is defined in the default interface scope. */
		void trigger();
		
		
	protected:
		
		
		std::deque<EventInstance*> incomingEventQueue;
		
		EventInstance* getNextEvent();
		
		void dispatchEvent(EventInstance* event);
		
		
		
	private:
		OrthogonalStatemachine(const OrthogonalStatemachine &rhs);
		OrthogonalStatemachine& operator=(const OrthogonalStatemachine&);
		
		sc::integer left;
		sc::integer right;
		
		
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc::ushort maxOrthogonalStates = 2;
		
		
		
		State stateConfVector[maxOrthogonalStates];
		
		
		OperationCallback* ifaceOperationCallback;
		
		
		bool isExecuting;
		sc::integer stateConfVectorPosition;
		
		
		// prototypes of all internal functions
		
		void enseq_Left_State_default();
		void enseq_Right_State_default();
		void enseq_Left_default();
		void enseq_Right_default();
		void exseq_Left_State();
		void exseq_Right_State();
		void exseq_Left();
		void exseq_Right();
		void react_Left__entry_Default();
		void react_Right__entry_Default();
		sc::integer react(const sc::integer transitioned_before);
		sc::integer Left_State_react(const sc::integer transitioned_before);
		sc::integer Right_State_react(const sc::integer transitioned_before);
		void clearInEvents();
		void microStep();
		void runCycle();
		
		
		
		
		/*! Indicates event 'trigger' of default interface scope is active. */
		bool trigger_raised;
		
		
		
};


inline OrthogonalStatemachine::OperationCallback::~OperationCallback() {}


#endif /* ORTHOGONALSTATEMACHINE_H_ */
